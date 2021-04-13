#include "password.h"
#include "user.h"
Password::Password(QString passId, QString username, QString password, QString site, QObject *parent):
    QObject(parent),passId(passId),username(username),
    password(password),site(site)
{

}

Password::~Password()
{

}

QString Password::getSite() const
{
    return site;
}

QString Password::getPassword() const
{
    return password;
}

QString Password::getUsername() const
{
    return username;
}

QString Password::getPassId() const
{
    return passId;
}

