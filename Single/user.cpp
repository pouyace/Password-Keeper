#include "user.h"
User::User(const QString& username,QObject *parent) :
    QObject(parent),
    _username(username)
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

void User::addPassword(const Password &pass)
{
    passwods.append(pass);
}

