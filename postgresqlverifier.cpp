#include "postgresqlverifier.h"
#include <QHostAddress>
#include <QtSql/QSqlError>
#include <user.h>
#include <passwordhandler.h>
#include "password.h"

PostgreSqlVerifier::PostgreSqlVerifier(QObject *parent):
    QObject(parent)
{
    _DataBase = QSqlDatabase::addDatabase("QPSQL");
    passwordHandler = new PasswordHandler(this);
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
    emit databaseConnected(false);
    if(_DataBase.open()){
        emit databaseConnected(true);
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
                    emit databaseConnected(true);
                    return true;
                }
                return false;
            }
            return false;
        }
        return false;
    }
}

void PostgreSqlVerifier::verifyUser(const QString &username, const QString &password)
{
    QString pass = passwordHandler->getHashedPassword(password);
    QString query = "SELECT password,firstname,lastname,hint FROM users WHERE username = '" + username+"';";

    int state = this->execute(query);
    QString querryPassword = getValue("password").toString().toStdString().data();
    if(!state){
        emit errorOccured("Username not registered","");
        return;
    }
    else if(password != querryPassword){
        QString queryHint = getValue("hint").toString().toStdString().data();
        emit errorOccured("Wrong Password",queryHint);
        return;
    }
    User *user = new User(username,this);
    QString querryFirstname = getValue("firstname").toString().toStdString().data();
    QString querryLastname = getValue("lastname").toString().toStdString().data();
    user->setName(querryFirstname,querryLastname);
    retrieveUserPasswords(user);
    emit userSignedIn(user);
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

void PostgreSqlVerifier::retrieveUserPasswords(User* user)
{
    QString query = "SELECT pass_id,username,password,site FROM passwords WHERE app_user = '" + user->username()+"';";
    int state = this->execute(query);
    do{
        int Qpass_id = getValue("pass_id").toInt();
        QString Qusername = getValue("username").toString().toStdString().data();
        QString Qpassword = getValue("password").toString().toStdString().data();
        QString Qsite     = getValue("site").toString().toStdString().data();
        user->insertPassword(new Password(Qpass_id,Qusername,Qpassword,Qsite,user));
    }while(_Result.next());

}

