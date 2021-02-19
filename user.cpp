#include "user.h"
#include "postgresqlverifier.h"
#include "password.h"
User::User(const QString& username,PostgreSqlVerifier *parent) :
    QObject(parent),
    _verifier(parent),
    _username(username)
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

void User::insertPassword(Password *password)
{
    _passwords.append(password);
}

QString User::fullName() const
{
    if(!(_firstName.length() + _lastName.length())){
        return _username;
    }
    else{
        return _firstName + _lastName;
    }
}

int User::passwordsCount() const
{
    return _passwords.count();
}
