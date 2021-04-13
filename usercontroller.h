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
    explicit UserController(User* user,QObject *parent);
    int userPasswordsCount()const;
    int userUniqueSitesCount();
private:
    User* _user = nullptr;
    QList<Password*> _Passwords;
    QSet<QString>   _uniqueSites;
    //Methods
    void emptyPasswordList();
public slots:
    void addNewPassword(Password* newPassword);
    void removePassword(int id);
signals:
    void passwordsCountChanged(int);
    void uniqueSitesCountChanged(int);
    void newItemAdded(Password*);
    void itemDeleted(int id);
};

#endif // USERCONTROLLER_H
