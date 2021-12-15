#include "databaseverifier.h"
#include <QHostAddress>
#include <QtSql/QSqlError>
#include "../Single/user.h"
#include "../Handlers/passwordgenerator.h"
#include "../Single/password.h"
#include <QMessageBox>
#include "GUI/dbconfigdialog.h"

DatabaseVerifier::DatabaseVerifier(QObject *parent):
    QObject(parent)
{
    _DataBase = QSqlDatabase::addDatabase("QODBC3");
    passwordHandler = new PasswordGenerator(this);
    qDebug() << "Available drivers: "<< _DataBase.drivers();
}

bool DatabaseVerifier::setupConfig(const QHostAddress &ip, const qint16 &port, const QString &username
                                     , const QString &password, const QString &databaseName)
{
    QString dbName = databaseName;
    QString connectString = "Driver={ODBC Driver 17 for SQL Server};Server=lpc:DESKTOP-5JKM6U6;Database=PasswordManager;UID=PouyaLogin;PWD=theonepouya;";
    _DataBase.setDatabaseName(connectString);
    _DataBase.setUserName("PouyaLogin");
    _DataBase.setPassword("theonepouya");
    qDebug()<<connectString;
    if(_DataBase.open()){
        this->setError(Error::NoError);
        return true;
    }
    else{
        qDebug()<<_DataBase.lastError().text();
        QMessageBox::warning(nullptr, "Error", _DataBase.lastError().text());
        return false;
    }
}

void DatabaseVerifier::onUserLoginRequested(const QString &username, const QString &password)
{
//    QString pass = passwordHandler->getHashedPassword(password);
    QString query = config.usersTable.getSelectQueryString(username, password);
    this->execute(query);
    int personID = getValue(config.usersTable.idField).toInt();
    if( personID == 0){
        QString queryHint = getValue(config.usersTable.hintField).toString().toStdString().data();
        setError(WrongPassword);
        emit errorOccured(errorString());
        emit hintDisplayRequested(queryHint);
        return;
    }else if(personID > 0){
        QString id = getValue(config.usersTable.idField).toString();
        User *user = new User(username, id,this);
        this->frontUser = user;
        QString querryFirstname = getValue(config.usersTable.fnameField).toString().toStdString().data();
        QString querryLastname = getValue(config.usersTable.lnameField).toString().toStdString().data();
        user->setName(querryFirstname,querryLastname);
        sync();
        emit userSignedIn(this->frontUser);
    }else{
        setError(UsernameNotRegistered);
        emit errorOccured(errorString());
        return;
    }
}

bool DatabaseVerifier::onAddNewItem(const Password& newPassword)
{
    QString query = config.passwordsTable.getInsertQueryString(newPassword, frontUser->id().toInt());
    int status = this->execute(query);
    if(status){
        this->setError(Error::NoError);
        emit newItemInserted(true);
        sync();
        return true;
    }
    else{
        this->setError(Error::InsertinoError);
        qDebug()<<_DataBase.lastError().text();
        QMessageBox::warning(nullptr, "Error", _DataBase.lastError().text());
        emit newItemInserted(false);
        return false;
    }
}

void DatabaseVerifier::doConnect()
{
    bool state = this->setupConfig(QHostAddress::LocalHost, config.port, config.serverUsername
                                   ,config.serverPassword, config.databaseName);
    emit databaseConnected(state);
    if(!state)
        emit errorOccured(errorString());
}

void DatabaseVerifier::onRemoveItem(int id)
{

    QString query = config.passwordsTable.getDeletionQueryString(id, frontUser->id().toInt());
    int state = this->execute(query);
    if(state){
        this->setError(Error::NoError);
        emit itemRemoved(id, true);
//        sync();
    }
    else{
        this->setError(Error::InsertinoError);
        qDebug()<<_DataBase.lastError().text();
        emit itemRemoved(id, false);
        QMessageBox::warning(nullptr, "Error", _DataBase.lastError().text());
    }
}

void DatabaseVerifier::sync()
{
    retrieveUserPasswords();
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
        QString idField = getValue(config.passwordsTable.idField).toString();
        QString validityField = getValue(config.passwordsTable.validityField).toString().toStdString().data();
        QString passwordField= getValue(config.passwordsTable.passwordField).toString().toStdString().data();
        QString websiteField = getValue(config.passwordsTable.websiteField).toString().toStdString().data();
        QString descriptionField  = getValue(config.passwordsTable.descriptionField).toString().toStdString().data();
        QString titleField  = getValue(config.passwordsTable.titleField).toString().toStdString().data();
        QString creationDateField  = getValue(config.passwordsTable.creationDateField).toString().toStdString().data();
        QString expirationDateField  = getValue(config.passwordsTable.expirationDateField).toString().toStdString().data();
        QString usernameField = getValue(config.passwordsTable.usernameField).toString().toStdString().data();
        retreivedPasswords.insert(idField.toInt(),new Password(idField, usernameField, passwordField, websiteField, titleField, expirationDateField, creationDateField,
                                                                descriptionField, this->frontUser));
    }while(_Result.next());
    emit syncItemsRetreived(retreivedPasswords);
    return true;
}

void DatabaseVerifier::setError(DatabaseVerifier::Error error)
{
    _error = error;
}


