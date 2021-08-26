#include "password.h"
Password::Password(QString passId, QString username, QString password, QString site, QObject *parent):
    QObject(parent),_passId(passId),_username(username),
    _password(password),_website(site)
{

}

Password::Password(QString username, QString password, QString website)
{
    _username = username;
    _password = password;
    _website  = website;
}

Password::Password()
{

}

Password::Password(const Password &obj)
{
    _passId   = obj.passId  ();
    _username = obj.username();
    _password = obj.password();
    _website  = obj.website ();
}

Password &Password::operator=(const Password &obj)
{
    this->_passId     = obj.passId();
    this->_password   = obj.password();
    this->_username   = obj.username();
    this->_website    = obj.website();
    this->_modelIndex = obj.modelIndex();

}

Password::~Password()
{

}

void Password::setPassId(const QString &passId)
{
    _passId = passId;
}

void Password::setWebsite(const QString &website)
{
    _website = website;
}

void Password::setUsername(const QString &username)
{
    _username = username;
}

void Password::setPassword(const QString &password)
{
    _password = password;
}

QString Password::website() const
{
    return _website;
}

QString Password::password() const
{
    return _password;
}

QString Password::username() const
{
    return _username;
}

QString Password::passId() const
{
    return _passId;
}

void Password::setModelIndex(QModelIndex modelIndex)
{
    _modelIndex = modelIndex;
}

QModelIndex Password::modelIndex() const
{
    return _modelIndex;
}

