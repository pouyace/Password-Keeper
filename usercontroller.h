#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H
#include <QSet>
#include <QObject>
class User;
class Password;
class UserController : public QObject
{
    Q_OBJECT
public:
    explicit UserController(QObject *parent,User* user = nullptr);
    void setUser(User* user);
private:
    User* _user = nullptr;
    QList<Password*> _Passwords;
    QSet<QString>   _uniqueSites;
    //Methods
    void emptyPasswordList();
    void userUniqueSitesCount();
    void userPasswordsCount();
public slots:
    void onNewItemGot(Password* newPassword);
    void onItemsRetreived(QList<Password *> list);
//    void removePassword(int id);
signals:
    void showItems(QList<Password*>);
    void passwordsCountChanged(int);
    void uniqueSitesCountChanged(int);
//    void itemDeleted(int id);
};

#endif // USERCONTROLLER_H
