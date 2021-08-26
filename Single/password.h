#ifndef PASSWORD_H
#define PASSWORD_H

#include <QObject>
#include <QModelIndex>

class Password:public QObject
{
    Q_OBJECT
public:
    Password(QString passId, QString username, QString password, QString site, QObject *parent);
    Password(QString username, QString password , QString website);
    Password();
    Password(const Password& obj);
    Password& operator=(const Password &obj);

    ~Password();

    void setPassId  (const QString &passId);
    void setWebsite (const QString &website);
    void setUsername(const QString &username);
    void setPassword(const QString &password);

    QString website()const;
    QString password()const;
    QString username()const;
    QString passId()const;

    void setModelIndex(QModelIndex modelIndex);
    QModelIndex modelIndex() const;

private:
    QString _passId     = "Invalid";
    QString _username   = "Invalid";
    QString _password   = "Invalid";
    QString _website    = "Invalid";

    QModelIndex _modelIndex;

};

#endif // PASSWORD_H
