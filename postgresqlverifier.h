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
    enum Error{NoError,InsertinoError,LoginError};
    PostgreSqlVerifier(QObject* parent);
    bool setupConfig(const QHostAddress& ip, const qint16 &port, const QString& username, const QString& password, const QString& databaseName);
    void verifyUser(const QString& username,const QString& password);
    QString errorString();
    ~PostgreSqlVerifier();
public slots:
    bool insertNewItem(QString username,QString password,QString site);
    void unregisterUser(User *user);
private:
    QSqlDatabase _DataBase;
    QSqlQuery    _Result;
    QFile*        _ErrorFile = nullptr;
    PasswordHandler *passwordHandler = nullptr;
    User *frontUser = nullptr;
    Error _error;
    //Methods
    int execute(const QString &query);
    QVariant getValue(const int& position)const;
    QVariant getValue(const QString& position)const;
    void retrieveUserPasswords(User *user);
    void setError(Error error);
signals:
    void databaseConnected(const bool&);
    void newItemInserted(bool);
    void errorOccured(const QString&,const QString&);
    void userSignedIn(User*);
};

#endif // POSTGRESQLVERIFIER_H
