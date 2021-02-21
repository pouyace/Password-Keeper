#include "password.h"
#include "user.h"
Password::Password(int passId, QString username, QString password, QString site, User *owner):
    QObject(owner),owner(owner),passId(passId),username(username),
    password(password),site(site)
{

}

QString Password::getSite() const
{
    return site;
}

QString Password::getPassWord() const
{
    return password;
}

QString Password::getUsername() const
{
    return username;
}

int Password::getPassId() const
{
    return passId;
}

User *Password::getOwner() const
{
    return owner;
}
