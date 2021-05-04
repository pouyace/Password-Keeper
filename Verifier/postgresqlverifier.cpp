#include "postgresqlverifier.h"
#include <QHostAddress>
#include <QtSql/QSqlError>
#include "../Single/user.h"
#include "../Handlers/passwordhandler.h"
#include "../Single/password.h"
#include <QMessageBox>
#include "GUI/databasepassewordsetter.h"


PostgreSqlVerifier::PostgreSqlVerifier(QObject *parent):
    QObject(parent)
{
    _DataBase = QSqlDatabase::addDatabase("QPSQL");
    passwordHandler = new PasswordHandler(this);
    connect(this,&PostgreSqlVerifier::syncRequested,this,&PostgreSqlVerifier::sync);
}

bool PostgreSqlVerifier::setupConfig(const QHostAddress &ip, const qint16 &port, const QString &username
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
        _DataBase.setDatabaseName("");
        if (_DataBase.open()){
            _DataBase.exec("CREATE DATABASE "+dbName);
            if(_DataBase.lastError().type() == QSqlError::NoError){
                _DataBase.close();
                _DataBase.setDatabaseName(dbName);
                if(_DataBase.open()){
                    this->setError(Error::NoError);
                    return true;
                }
                this->setError(Error::DatabaseNotOpen);
                return false;
            }
            this->setError(Error::DatabaseNotOpen);
            return false;
        }
        this->setError(Error::DatabaseNotOpen);
        return false;
    }
}

void PostgreSqlVerifier::onUserLoginRequested(const QString &username, const QString &password)
{
    QString pass = passwordHandler->getHashedPassword(password);
    QString query = "SELECT password,firstname,lastname,hint FROM users WHERE username = '" + username+"';";

    int state = this->execute(query);
    QString querryPassword = getValue("password").toString().toStdString().data();
    if(!state){
        setError(UsernameNotRegistered);
        emit errorOccured(errorString());
        return;
    }
    else if(password != querryPassword){
        QString queryHint = getValue("hint").toString().toStdString().data();
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

bool PostgreSqlVerifier::onAddNewItem(Password *newPassword)
{
    QString query = "insert into passwords values(nextval('order_item_id'),'"
            + newPassword->getUsername() + "','" + newPassword->getPassword() + "','"
            + newPassword->getSite() +"','"+
            frontUser->username() + "');";
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

void PostgreSqlVerifier::onConnectToDatabase(QString user, QString pass)
{
    bool state = this->setupConfig(QHostAddress::LocalHost,5432,user,pass,"PasswordKeeper");
    emit databaseConnected(state);
    if(!state)
        emit errorOccured(errorString());
}

void PostgreSqlVerifier::onRemoveItem(int id)
{

}

void PostgreSqlVerifier::sync()
{
    bool syncStatus = false;
    retrieveUserPasswords();
    emit tableSynced(syncStatus);
}

QString PostgreSqlVerifier::errorString()
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

void PostgreSqlVerifier::setupProperties()
{
    databasePasswordSetterDialog = new DataBasePassewordSetter(DEFAULTDATABASEUSERNAME,DEFAULTDATABASEPASSWORD); // Database Password

    connect(this,&PostgreSqlVerifier::databaseConnected,databasePasswordSetterDialog,&DataBasePassewordSetter::onDatabaseConnected);
    connect(databasePasswordSetterDialog,&DataBasePassewordSetter::databaseNewConfigSet,this,&PostgreSqlVerifier::onConnectToDatabase);
    connect(databasePasswordSetterDialog,&DataBasePassewordSetter::dialogClosed,this,&PostgreSqlVerifier::onDialogClosed);

}

PostgreSqlVerifier::~PostgreSqlVerifier()
{

}

int PostgreSqlVerifier::execute(const QString &query)
{
    _Result = _DataBase.exec(query);
    int size = _Result.size();
    if(size == -1)
        size = _Result.numRowsAffected();
    _Result.first();
    return size;
}

QVariant PostgreSqlVerifier::getValue(const int &position) const
{
    return _Result.value(position);
}

QVariant PostgreSqlVerifier::getValue(const QString &position) const
{
    return _Result.value(position);
}

bool PostgreSqlVerifier::retrieveUserPasswords()
{
    QString query = "SELECT pass_id,username,password,site FROM passwords WHERE app_user = '" + frontUser->username()+"';";
    int state = this->execute(query);
    if(!state)
        qDebug()<<"Nothing to extract";
    if(!this->frontUser){
       qDebug()<<"Null front User";
       return false;
     }

    QList<Password*> retreivedPasswords;
    do{
        QString Qpass_id  = getValue("pass_id").toString();
        QString Qusername = getValue("username").toString().toStdString().data();
        QString Qpassword = getValue("password").toString().toStdString().data();
        QString Qsite     = getValue("site").toString().toStdString().data();
        retreivedPasswords.append(new Password(Qpass_id,Qusername,Qpassword,Qsite,this->frontUser));
    }while(_Result.next());
    emit syncItemsRetreived(retreivedPasswords);
    return true;
}

void PostgreSqlVerifier::setError(PostgreSqlVerifier::Error error)
{
    _error = error;
}


