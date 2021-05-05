#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H
#include <QSet>
#include <QMap>
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
    QSet<QString>   _uniqueSites;
    QMap <int,Password*>_PasswordContainer;
    //Methods
    void userUniqueSitesCount();
public slots:
    void onItemsRetreived(QMap<int, Password *> list);
signals:
    void showItems(QList<Password*>);
    void removeItem();
    void passwordsCountUpdated(int);
    void uniqueSitesCountUpdated(int);
};

#endif // USERCONTROLLER_H
