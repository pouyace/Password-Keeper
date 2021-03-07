#ifndef POSTGRESQLVERIFIER_H
#define POSTGRESQLVERIFIER_H
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqldatabase.h>
#include <QObject>
#include "../Single/password.h"

class User;
class QHostAddress;
class Password;
class PasswordHandler;
class PostgreSqlVerifier:public QObject
{
    Q_OBJECT
public:
    enum Error{NoError,InsertinoError,LoginError,UsernameNotRegistered,WrongPassword,DatabaseNotOpen};
    PostgreSqlVerifier(QObject* parent);
    ~PostgreSqlVerifier();
public slots:
    void verifyUser(const QString& username,const QString& password);
    bool addNewItemToDatabase(QString username,QString password,QString site);
    void connectToDatabase(QString user="", QString pass="");
private:
    QSqlDatabase _DataBase;
    QSqlQuery    _Result;
    PasswordHandler *passwordHandler = nullptr;
    User *frontUser = nullptr;
    Error _error = NoError;
    bool isDatabaseConnected = false;

    //Methods
    bool setupConfig(const QHostAddress& ip, const qint16 &port, const QString& username, const QString& password, const QString& databaseName);
    int execute(const QString &query);
    QVariant getValue(const int& position)const;
    QVariant getValue(const QString& position)const;
    void retrieveUserPasswords(User *user);
    void setError(Error error);
    QString errorString();
signals:
    void passwordListRetreived(QList<Password*>);
    void databaseConnected(const bool&);
    void newItemInserted(const bool&);
    void userSignedIn(User*);
//    void itemDeleted(int id);
    void errorOccured(const QString&);
    void hintDisplayRequested(const QString&);
};

#endif // POSTGRESQLVERIFIER_H
