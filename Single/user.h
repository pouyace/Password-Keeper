#ifndef USER_H
#define USER_H

#include <QObject>
#include "password.h"

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(const QString& username, const QString id, QObject *parent = nullptr);
    ~User();
    void setName(const QString& firstname,const QString& lastname);
    QString username()const;
    QString prettyName()const;
    QString id()const;
    void addPassword(const Password& pass);
    void removePassword(const int& id);
    void modifyPassword(int id, const Password& pass);
    void setId(const QString& id);

private:
    QList<Password> passwods;
    QString     _firstName = "";
    QString     _lastName = "";
    QString     _username;
    QString     _id;
};

#endif // USER_H
