#include "usercontroller.h"
#include "password.h"
#include <QDebug>

UserController::UserController(QObject *parent, User *user)
{

}

void UserController::userPasswordsCount()
{
    emit passwordsCountChanged(_Passwords.count());
}

void UserController::setUser(User *user)
{
    this->_user = user;
}

void UserController::userUniqueSitesCount()
{
    QListIterator<Password*> passIt(_Passwords);
    while(passIt.hasNext()){
        _uniqueSites.insert(passIt.next()->getSite());
    }
    emit uniqueSitesCountChanged(_uniqueSites.count());
}

void UserController::emptyPasswordList()
{
    qDeleteAll(_Passwords);
    _Passwords.clear();
}

void UserController::onNewItemGot(Password *newPassword)
{
    QList<Password*> pass;
    pass.append(newPassword);
    _Passwords.append(pass);
    emit showItems(pass);
    userUniqueSitesCount();
    userPasswordsCount();
}

void UserController::onItemsRetreived(QList<Password*> list)
{
    _Passwords.append(list);
    emit showItems(list);
    userUniqueSitesCount();
    userPasswordsCount();
}
