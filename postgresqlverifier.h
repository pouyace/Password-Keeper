#ifndef POSTGRESQLVERIFIER_H
#define POSTGRESQLVERIFIER_H
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqldatabase.h>
#include <QObject>

class QHostAddress;
class QFile;
class PostgreSqlVerifier:public QObject
{
    Q_OBJECT
public:
    PostgreSqlVerifier();
    void setupConfig(const QHostAddress& ip, const qint16 &port, const QString& username, const QString& password, const QString& dbName);
private:
    //QSqlDatabase _DataBase;
    //QSqlQuery    _Result;
    QFile*        _ErrorFile = nullptr;
};

#endif // POSTGRESQLVERIFIER_H
