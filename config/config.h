#ifndef CONFIG_H
#define CONFIG_H
#include <QString>

struct Config;
namespace App_Config {
struct UsersPasswordsTable;
struct UsersTable;
struct Config;
};

struct App_Config::UsersPasswordsTable{
    QString tableName            = "Data.UsersPasswords";
    QString selectFunctionName   = "Data.getAllPasswords";
    QString idField              = "ItemID";
    QString ownerField           = "Owner";
    QString validityField        = "Validity";
    QString titleField           = "Title";
    QString creationDateField    = "CreationDate";
    QString expirationDateField  = "ExpirationDate";
    QString usernameField        = "Username";
    QString websiteField         = "Website";
    QString passwordField        = "Password";
    QString descriptionField     = "Description";

    QString getSelectQueryString(const QString& cur_user){
        QString comma = " ,";
        QString query = "SELECT * from " + selectFunctionName + "('" + cur_user + "');";
        return query;
    }

    QString getInsertQueryString(const QString& usernameItem, const QString& passItem, const QString& siteItem, const QString& owner){
        QString query = "insert into " + tableName + " values(nextval('"+/*sequenceCounter+*/"'),'"
                + owner + "','" + usernameItem + "','"
                + siteItem +"','"
                + passItem + "');";

        return query;
    }

    QString getDeletionQueryString(const int& id){
        QString query = "delete from " + tableName + " where " + idField + " = " + QString::number(id)+";";
        return query;
    }

};

struct App_Config::UsersTable{
    QString tableName            = "Peron.Person";
    QString selectFunctionName   = "Person.getUserData";
    QString idField              = "PersonID";
    QString fnameField           = "FirstName";
    QString lnameField           = "LastName";
    QString usernameField        = "Username";
    QString titleField           = "title";
    QString bdateField           = "BirthDate";
    QString hintField            = "PasswordHint";
    QString passField            = "UserPassword";
    QString emailField           = "Email";

    QString getSelectQueryString(const QString& cur_user, const QString &password){
        QString comma = " ,";
        QString query = "SELECT * from " + selectFunctionName + "('" + cur_user+ "', '" + password + "');";
        return query;
    }

};

struct App_Config::Config{
    QString                 databaseName    = "PasswordManager";
    QString                 serverUsername  = "PouyaLogin";
    QString                 serverPassword  = "theonepouya";
    int                     port            = 1433;
    UsersPasswordsTable     passwordsTable;
    UsersTable              usersTable;
};



#endif // CONFIG_H
