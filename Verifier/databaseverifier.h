#ifndef POSTGRESQLVERIFIER_H
#define POSTGRESQLVERIFIER_H
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqldatabase.h>
#include <QObject>
#include "../Single/password.h"
#include <QMap>
#include "config.h"


class User;
class QHostAddress;
class Password;
class PasswordHandler;
class DataBasePassewordSetter;
class DatabaseVerifier:public QObject
{
    Q_OBJECT
public:
    enum Error{NoError,InsertinoError,LoginError,UsernameNotRegistered,WrongPassword,DatabaseNotOpen, DeletionError};
    DatabaseVerifier(QObject* parent);
    ~DatabaseVerifier();
    void doConnect();
public slots:
    void onUserLoginRequested(const QString& username,const QString& password);
    bool onAddNewItem(Password* newPassword);
    void onRemoveItem(int id);
private:
    QSqlDatabase _DataBase;
    QSqlQuery    _Result;
    App_Config::Config config;
    PasswordHandler *passwordHandler = nullptr;
    User *frontUser = nullptr;
    Error _error = NoError;
    bool isDatabaseConnected = false;
    DataBasePassewordSetter *databasePasswordSetterDialog =  nullptr;

    //Methods
    void sync();
    bool setupConfig(const QHostAddress& ip, const qint16 &port, const QString& username, const QString& password, const QString& databaseName);
    int execute(const QString &query);
    QVariant getValue(const int& position)const;
    QVariant getValue(const QString& position)const;
    bool retrieveUserPasswords();
    void setError(Error error);
    QString errorString();
    void setupProperties();
signals:
    // Add item to table and userController
    void syncItemsRetreived(QMap<int,Password*>);
    void newItemInserted(bool);
    void itemRemoved(int id, bool);
    void databaseConnected(const bool&);
    void userSignedIn(User*);

    void errorOccured(const QString&);
    void hintDisplayRequested(const QString&);
    void onDialogClosed();
};

#endif // POSTGRESQLVERIFIER_H
