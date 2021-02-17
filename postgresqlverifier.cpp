#include "postgresqlverifier.h"
#include <QHostAddress>
#include <QtSql/QSqlError>
#include <user.h>

PostgreSqlVerifier::PostgreSqlVerifier()
{
    _DataBase = QSqlDatabase::addDatabase("QPSQL");
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

User *PostgreSqlVerifier::verifyUser(const QString &username, const QString &password)
{

}
