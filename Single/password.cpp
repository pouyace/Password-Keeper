#include "password.h"
Password::Password(QString passId, QString username, QString password, QString site, QString title, QString expDate, QString creDate, QString descrip, QString validity,  QObject *parent):
    QObject(parent),_itemId(passId),_usernameField(username),
    _passwordField(password),_expirationDateField(expDate),_websiteField(site),_titleField(title),
    _creationDateField(creDate),_descriptionField(descrip),_validityField(validity)
{

}

Password::Password(QString username, QString password, QString website, QString title, QString expDate, QString description)
{
    _usernameField = username;
    _passwordField = password;
    _websiteField  = website;
    _titleField  = title;
    _descriptionField = description;
    _expirationDateField = expDate;
}

Password::Password()
{

}

Password::Password(const Password &obj)
{
    _itemId   = obj.passId  ();
    _usernameField = obj.username();
    _passwordField = obj.password();
    _websiteField  = obj.website ();
}

Password &Password::operator=(const Password &obj)
{
    this->_itemId               = obj.passId();
    this->_passwordField        = obj.password();
    this->_usernameField        = obj.username();
    this->_websiteField         = obj.website();
    this->_modelIndex           = obj.modelIndex();
    this->_titleField           = obj.title();
    this->_descriptionField     = obj.description();
    this->_validityField        = obj.validity();
    this->_expirationDateField  = obj.expiration();
    this->_creationDateField    = obj.creation();
    return *this;
}

Password::~Password()
{

}

void Password::setPassId(const QString &passId)
{
    _itemId = passId;
}

void Password::setWebsite(const QString &website)
{
    _websiteField = website;
}

void Password::setUsername(const QString &username)
{
    _usernameField = username;
}

void Password::setPassword(const QString &password)
{
    _passwordField = password;
}

void Password::setValidity(const QString &validity)
{
    _validityField = validity;
}

void Password::setTitle(const QString &title)
{
    _titleField = title;
}

void Password::setDescription(const QString &description)
{
    _descriptionField = description;
}

void Password::setExpirationDate(const QString &expiration)
{
    _expirationDateField = expiration;
}

void Password::setCreationDate(const QString &creation)
{
    _creationDateField = creation;
}

QString Password::website() const
{
    return _websiteField;
}

QString Password::password() const
{
    return _passwordField;
}

QString Password::username() const
{
    return _usernameField;
}

QString Password::passId() const
{
    return _itemId;
}

QString Password::validity() const
{
    return _validityField;
}

QString Password::title() const
{
    return _titleField;
}

QString Password::description() const
{
    return _descriptionField;
}

QString Password::expiration() const
{
    return _expirationDateField;
}

QString Password::creation() const
{
    return _creationDateField;
}

void Password::setModelIndex(QModelIndex modelIndex)
{
    _modelIndex = modelIndex;
}

QModelIndex Password::modelIndex() const
{
    return _modelIndex;
}

