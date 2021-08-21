#include "postgresqlverifier.h"
#include <QHostAddress>
#include <QtSql/QSqlError>
#include "../Single/user.h"
#include "../Handlers/passwordhandler.h"
#include "../Single/password.h"
#include <QMessageBox>
#include "GUI/databasepassewordsetter.h"

DatabaseVerifier::DatabaseVerifier(QObject *parent):
    QObject(parent)
{
    _DataBase = QSqlDatabase::addDatabase("QPSQL");
    passwordHandler = new PasswordHandler(this);
    connect(this,&DatabaseVerifier::syncRequested,this,&DatabaseVerifier::sync);
}

bool DatabaseVerifier::setupConfig(const QHostAddress &ip, const qint16 &port, const QString &username
                                     , const QString &password, const QString &databaseName)
{
    QString dbName = databaseName;
    _DataBase.setPort(port);
    _DataBase.setHostName(ip.toString());
    _DataBase.setPassword(password);
    _DataBase.setDatabaseName(dbName);
    _DataBase.setUserName(username);
    _DataBase.setConnectOptions("connect_timeout=10");
    if(_DataBase.open()){
        this->setError(Error::NoError);
        return true;
    }
    else{
        qDebug()<<_DataBase.lastError().text();
        return false;
    }
}

void DatabaseVerifier::onUserLoginRequested(const QString &username, const QString &password)
{
    QString pass = passwordHandler->getHashedPassword(password);
    QString query = config.usersTable.getSelectQueryString(username);
    qDebug()<<query;
    int state = this->execute(query);
    QString querryPassword = getValue(config.usersTable.password).toString().toStdString().data();
    if(!state){
        setError(UsernameNotRegistered);
        emit errorOccured(errorString());
        return;
    }
    else if(password != querryPassword){
        QString queryHint = getValue(config.usersTable.hint).toString().toStdString().data();
        setError(WrongPassword);
        emit errorOccured(errorString());
        emit hintDisplayRequested(queryHint);
        return;
    }
    else{
        User *user = new User(username,this);
        this->frontUser = user;
        QString querryFirstname = getValue("firstname").toString().toStdString().data();
        QString querryLastname = getValue("lastname").toString().toStdString().data();
        user->setName(querryFirstname,querryLastname);
        emit syncRequested();
        emit userSignedIn(this->frontUser);
    }
}

bool DatabaseVerifier::onAddNewItem(Password *newPassword)
{
    QString query = config.passwordsTable.getInsertQueryString(newPassword->getUsername()
                                                               , newPassword->getPassword(), newPassword->getSite(), frontUser->username());
    this->execute(query);
    if(!_DataBase.lastError().text().length()){
        this->setError(Error::NoError);
        emit newItemInserted(true);
        emit syncRequested();
        newPassword->deleteLater();
        return true;
    }
    else{
        this->setError(Error::InsertinoError);
        emit newItemInserted(false);
        newPassword->deleteLater();
        return false;
    }
}

void DatabaseVerifier::onConnectToDatabase()
{
    bool state = this->setupConfig(QHostAddress::LocalHost, config.port, config.serverUsername,config.serverPassword, config.databaseName);
    emit databaseConnected(state);
    if(!state)
        emit errorOccured(errorString());
}

void DatabaseVerifier::onRemoveItem(int id)
{
    QString query = "delete from passwords where pass_Id = " + QString::number(id)+";";
    int state = this->execute(query);
    if(!_DataBase.lastError().text().length()){
        this->setError(Error::NoError);
        emit itemRemoved();
        emit syncRequested();
    }
    else{
        this->setError(Error::InsertinoError);
    }
}

void DatabaseVerifier::sync()
{
    bool syncStatus = false;
    retrieveUserPasswords();
    emit tableSynced(syncStatus);
}

QString DatabaseVerifier::errorString()
{
    switch (_error) {
    case Error::NoError: return "No Error";
    case Error::InsertinoError: return "An Error occured during insertion";
    case Error::WrongPassword:   return "Wrong Password";
    case Error::UsernameNotRegistered: return "Username not registered";
    case Error::LoginError: return "Login Error";
    case Error::DatabaseNotOpen: return "Database not open";
    }
    return "NULL";
}

void DatabaseVerifier::setupProperties()
{
    databasePasswordSetterDialog = new DataBasePassewordSetter("",""); // Database Password

    connect(this,&DatabaseVerifier::databaseConnected,databasePasswordSetterDialog,&DataBasePassewordSetter::onDatabaseConnected);
    connect(databasePasswordSetterDialog,&DataBasePassewordSetter::databaseNewConfigSet,this,&DatabaseVerifier::onConnectToDatabase);
    connect(databasePasswordSetterDialog,&DataBasePassewordSetter::dialogClosed,this,&DatabaseVerifier::onDialogClosed);

}

DatabaseVerifier::~DatabaseVerifier()
{

}

int DatabaseVerifier::execute(const QString &query)
{
    _Result = _DataBase.exec(query);
    int size = _Result.size();
    if(size == -1)
        size = _Result.numRowsAffected();
    _Result.first();
    return size;
}

QVariant DatabaseVerifier::getValue(const int &position) const
{
    return _Result.value(position);
}

QVariant DatabaseVerifier::getValue(const QString &position) const
{
    return _Result.value(position);
}

bool DatabaseVerifier::retrieveUserPasswords()
{
    QString query = config.passwordsTable.getSelectQueryString(frontUser->username());
    int state = this->execute(query);
    if(!state)
        qDebug()<<"Nothing to extract";
    if(!this->frontUser){
       qDebug()<<"Null front User";
       return false;
     }

    QMap<int, Password*> retreivedPasswords;
    do{
        QString Qpass_id  = getValue(config.passwordsTable.idField).toString();
        QString Qusername = getValue(config.passwordsTable.usernameField).toString().toStdString().data();
        QString Qpassword = getValue(config.passwordsTable.passwordField).toString().toStdString().data();
        QString Qsite     = getValue(config.passwordsTable.websiteField).toString().toStdString().data();
        retreivedPasswords.insert(Qpass_id.toInt(),new Password(Qpass_id,Qusername,Qpassword,Qsite,this->frontUser));
    }while(_Result.next());
    emit syncItemsRetreived(retreivedPasswords);
    return true;
}

void DatabaseVerifier::setError(DatabaseVerifier::Error error)
{
    _error = error;
}


