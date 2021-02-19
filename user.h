#ifndef USER_H
#define USER_H

#include <QObject>

class Password;
class PostgreSqlVerifier;
class User : public QObject
{
    Q_OBJECT
public:
    explicit User(const QString& username,PostgreSqlVerifier *parent = nullptr);
    void setName(const QString& firstname,const QString& lastname);
    QString username()const;
    void insertPassword(Password* password);
private:
    QString             _firstName = "";
    QString             _lastName = "";
    QString             _username;
    QList<Password*>    _passwords;
    PostgreSqlVerifier* _verifier;
public:
    QString fullName()const;
    int passwordsCount()const;

signals:

};

#endif // USER_H
