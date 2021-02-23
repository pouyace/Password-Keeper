#ifndef POSTGRESQLVERIFIER_H
#define POSTGRESQLVERIFIER_H
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqldatabase.h>
#include <QObject>

class User;
class QHostAddress;
class QFile;
class PasswordHandler;
class PostgreSqlVerifier:public QObject
{
    Q_OBJECT
public:
    PostgreSqlVerifier(QObject* parent);
    bool setupConfig(const QHostAddress& ip, const qint16 &port, const QString& username, const QString& password, const QString& databaseName);
    void verifyUser(const QString& username,const QString& password);
    ~PostgreSqlVerifier();
    void unregisterUser(User *user);
private:
    QSqlDatabase _DataBase;
    QSqlQuery    _Result;
    QFile*        _ErrorFile = nullptr;
    PasswordHandler *passwordHandler = nullptr;
    User *frontUser = nullptr;
    //Methods
    int execute(const QString &query);
    QVariant getValue(const int& position)const;
    QVariant getValue(const QString& position)const;
    void retrieveUserPasswords(User *user);
signals:
    void databaseConnected(const bool&);
    void errorOccured(const QString&,const QString&);
    void userSignedIn(User*);
};

#endif // POSTGRESQLVERIFIER_H
