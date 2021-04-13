#include "usercontroller.h"
#include "password.h"
#include <QDebug>

UserController::UserController(User *user, QObject *parent)
{

}

int UserController::userPasswordsCount() const
{
    return _Passwords.count();
}

int UserController::userUniqueSitesCount()
{
    QListIterator<Password*> passIt(_Passwords);
    while(passIt.hasNext()){
        _uniqueSites.insert(passIt.next()->getSite());
    }
    return _uniqueSites.count();
}

void UserController::emptyPasswordList()
{
    qDeleteAll(_Passwords);
    _Passwords.clear();
}

void UserController::addNewPassword(Password *newPassword)
{
    _Passwords.append(newPassword);
    emit newItemAdded(newPassword);
}

void UserController::removePassword(int id)
{
    emit itemDeleted(id);
}
