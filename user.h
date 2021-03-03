#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(const QString& username, QObject *parent = nullptr);
    ~User();
    void setName(const QString& firstname,const QString& lastname);
    QString username()const;
    QString prettyName()const;
private:
    QString     _firstName = "";
    QString     _lastName = "";
    QString     _username;
};

#endif // USER_H
