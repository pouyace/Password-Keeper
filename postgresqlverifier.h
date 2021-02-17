#ifndef POSTGRESQLVERIFIER_H
#define POSTGRESQLVERIFIER_H
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqldatabase.h>
#include <QObject>

class User;
class QHostAddress;
class QFile;
class PostgreSqlVerifier:public QObject
{
    Q_OBJECT
public:
    PostgreSqlVerifier();
    bool setupConfig(const QHostAddress& ip, const qint16 &port, const QString& username, const QString& password, const QString& databaseName);
    User* verifyUser(const QString& username,const QString& password);

private:
    QSqlDatabase _DataBase;
    QSqlQuery    _Result;
    QFile*        _ErrorFile = nullptr;
signals:
    void databaseConnected(bool);
};

#endif // POSTGRESQLVERIFIER_H
