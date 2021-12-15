#include "user.h"
User::User(const QString& username, const QString id, QObject *parent) :
    QObject(parent),
    _username(username),
    _id(id)
{

}

User::~User()
{

}

void User::setName(const QString &firstname, const QString &lastname)
{
    _firstName = firstname;
    _lastName = lastname;
}

QString User::username() const
{
    return _username;
}

QString User::prettyName() const
{
    if(_firstName.length() + _lastName.length()){
        return _firstName + _lastName;
    }
    else{
        return _username;
    }
}

QString User::id() const
{
    return _id;
}

void User::addPassword(const Password &pass)
{
    passwods.append(pass);
}

void User::setId(const QString &id)
{
    _id = id;
}

