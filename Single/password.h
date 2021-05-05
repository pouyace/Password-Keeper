#ifndef PASSWORD_H
#define PASSWORD_H

#include <QObject>
class User;
class Password:public QObject
{
    Q_OBJECT
public:
    Password(QString passId, QString username, QString password, QString site, QObject *parent);
    Password(QString username, QString password, QString site, QObject *parent = nullptr);
    ~Password();
    void setHashedPassword(QString hashedPassword);
    void setPasswordId(QString id);
    QString getSite()const;
    QString getPassword()const;
    QString getUsername()const;
    QString getPassId()const;
    QString getHashedPassword()const;
    int id()const;
private:
    QString passId;
    QString hashedPassword;
    QString username;
    QString password;
    QString site;
};

#endif // PASSWORD_H
