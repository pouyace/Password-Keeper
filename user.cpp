#include "user.h"
#include "postgresqlverifier.h"
#include "password.h"
#include <QSet>
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

int User::userPasswordsCount() const
{
    return _passwords.count();
}

int User::userSitesCount() const
{
    QSet<QString>sites;
    QListIterator<Password*> passIt(_passwords);
    while(passIt.hasNext()){
        sites.insert(passIt.next()->getSite());
    }
    return sites.count();
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

QList<Password *> User::passwords() const
{
    return _passwords;
}

