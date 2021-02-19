#ifndef PASSWORD_H
#define PASSWORD_H

#include <QObject>
class User;
class Password:public QObject
{
    Q_OBJECT
public:
    Password(int passId,QString username,QString password,QString site,User* owner);
    QString getSite()const;
    QString getPassWord()const;
    QString getUsername()const;
    int     getPassId()const;
    User*   getOwner()const;
private:
    int passId;
    QString username;
    QString password;
    QString site;
    User*   owner;
};

#endif // PASSWORD_H
