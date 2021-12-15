#ifndef PASSWORD_H
#define PASSWORD_H

#include <QObject>
#include <QModelIndex>

class Password:public QObject
{
    Q_OBJECT
public:
    Password(QString passId, QString username, QString password, QString site, QString title, QString expDate, QString creDate, QString descrip, QObject *parent);
    Password(QString username, QString password , QString website, QString title, QString expDate, QString Description);
    Password();
    Password(const Password& obj);
    Password& operator=(const Password &obj);

    ~Password();

    void setPassId  (const QString &passId);
    void setWebsite (const QString &website);
    void setUsername(const QString &username);
    void setPassword(const QString &password);
    void setValidity(const QString &validity);
    void setTitle(const QString &title);
    void setDescription(const QString &description);
    void setExpirationDate(const QString &expiration);
    void setCreationDate(const QString &creation);

    QString website()const;
    QString password()const;
    QString username()const;
    QString passId()const;
    QString validity()const;
    QString title()const;
    QString description()const;
    QString expiration()const;
    QString creation()const;

    void setModelIndex(QModelIndex modelIndex);
    QModelIndex modelIndex() const;

private:
    QString _itemId     = "Invalid";
    QString _validityField;
    QString _titleField;
    QString _creationDateField;
    QString _expirationDateField;
    QString _usernameField;
    QString _websiteField;
    QString _passwordField;
    QString _descriptionField;

    QModelIndex _modelIndex;

};

#endif // PASSWORD_H
