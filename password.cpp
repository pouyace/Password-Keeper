#include "password.h"
#include "user.h"
Password::Password(int passId, QString username, QString password, QString site, User *owner):
    QObject(owner),owner(owner),passId(passId),username(username),
    password(password),site(site)
{

}
