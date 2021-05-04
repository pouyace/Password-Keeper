#ifndef POSTGRESQLVERIFIER_H
#define POSTGRESQLVERIFIER_H
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqldatabase.h>
#include <QObject>
#include "../Single/password.h"

#define DEFAULTDATABASEUSERNAME "postgres"
#define DEFAULTDATABASEPASSWORD "newpouya"

class User;
class QHostAddress;
class Password;
class PasswordHandler;
class DataBasePassewordSetter;
class PostgreSqlVerifier:public QObject
{
    Q_OBJECT
public:
    enum Error{NoError,InsertinoError,LoginError,UsernameNotRegistered,WrongPassword,DatabaseNotOpen};
    PostgreSqlVerifier(QObject* parent);
    ~PostgreSqlVerifier();
public slots:
    void onUserLoginRequested(const QString& username,const QString& password);
    bool onAddNewItem(Password* newPassword);
    void onConnectToDatabase(QString user="", QString pass="");
    void onRemoveItem(int id);
    void sync();
private:
    QSqlDatabase _DataBase;
    QSqlQuery    _Result;
    PasswordHandler *passwordHandler = nullptr;
    User *frontUser = nullptr;
    Error _error = NoError;
    bool isDatabaseConnected = false;
    DataBasePassewordSetter *databasePasswordSetterDialog =  nullptr;

    //Methods
    bool setupConfig(const QHostAddress& ip, const qint16 &port, const QString& username, const QString& password, const QString& databaseName);
    int execute(const QString &query);
    QVariant getValue(const int& position)const;
    QVariant getValue(const QString& position)const;
    bool retrieveUserPasswords();
    void setError(Error error);
    QString errorString();
    void setupProperties();
signals:
    void syncRequested();
    void tableSynced(bool);
    void syncItemsRetreived(QList<Password*>);
    void databaseConnected(const bool&);
    void newItemInserted(const bool&);
    void userSignedIn(User*);
    void itemRemoved();
    void errorOccured(const QString&);
    void hintDisplayRequested(const QString&);
    void onDialogClosed();
};

#endif // POSTGRESQLVERIFIER_H
