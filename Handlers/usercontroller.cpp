#include "usercontroller.h"
#include "../Single/password.h"
#include <QDebug>

UserController::UserController(QObject *parent, User *user)
{

}

void UserController::setUser(User *user)
{
    this->_user = user;
}

void UserController::userUniqueSitesCount()
{
    QMapIterator<int,Password*> passIt(_PasswordContainer);
    _uniqueSites.clear();
    while(passIt.hasNext()){
        passIt.next();
        _uniqueSites.insert(passIt.value()->website());
    }
    emit uniqueSitesCountUpdated(_uniqueSites.count());
}

void UserController::onItemsRetreived(QMap<int,Password*> list)
{
    qDeleteAll(_PasswordContainer.values());
    _PasswordContainer.clear();
    _PasswordContainer = list;
    emit showItems(_PasswordContainer.values());
    userUniqueSitesCount();
    emit passwordsCountUpdated(_PasswordContainer.count());
}
