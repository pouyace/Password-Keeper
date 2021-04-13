#ifndef POSTGRESQLVERIFIER_H
#define POSTGRESQLVERIFIER_H
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqldatabase.h>
#include <QObject>

#define DEFAULTDATABASEUSERNAME "postgres"
#define DEFAULTDATABASEPASSWORD "newpouya"

class User;
class QHostAddress;
class Password;
class PasswordHandler;
class PostgreSqlVerifier:public QObject
{
    Q_OBJECT
public:
    enum Error{NoError,InsertinoError,LoginError};
    PostgreSqlVerifier(QObject* parent);
    bool setupConfig(const QHostAddress& ip, const qint16 &port, const QString& username, const QString& password, const QString& databaseName);
    QString errorString();
    ~PostgreSqlVerifier();
public slots:
    void verifyUser(const QString& username,const QString& password);
    bool addNewItemToDatabase(QString username,QString password,QString site);
    void updateDatabaseUserAndPass(QString user,QString pass);
    void connectToDatabase();
private:
    QSqlDatabase _DataBase;
    QSqlQuery    _Result;
    PasswordHandler *passwordHandler = nullptr;
    User *frontUser = nullptr;
    Error _error;
    bool isDatabaseConnected = false;

    //Methods
    int execute(const QString &query);
    QVariant getValue(const int& position)const;
    QVariant getValue(const QString& position)const;
    void retrieveUserPasswords(User *user);
    void setError(Error error);
signals:
    void passwordItemRetreived(Password*);
    void passwordListRetreived(QList<Password*>);
    void databaseConnected(const bool&);
    void newItemInserted(bool);
    void itemDeleted(int id);
    void errorOccured(const QString&);
    void hintDisplayRequested(const QString&);
    void userSignedIn(User*);
};

#endif // POSTGRESQLVERIFIER_H
