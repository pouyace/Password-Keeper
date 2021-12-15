#ifndef CONFIG_H
#define CONFIG_H
#include <QString>
#include "../Single/password.h"
struct Config;
namespace App_Config {
struct UsersPasswordsTable;
struct UsersTable;
struct Config;
};

struct App_Config::UsersPasswordsTable{
    QString tableName               = "Data.UsersPasswords";
    QString selectFunctionName      = "Data.getAllPasswords";
    QString insertProcedureName     = "addPasswordItem";
    QString deletionProcedureName   = "deletePasswordItem";
    QString idField                 = "ItemID";
    QString ownerField              = "Owner";
    QString validityField           = "Validity";
    QString titleField              = "Title";
    QString creationDateField       = "CreationDate";
    QString expirationDateField     = "ExpirationDate";
    QString usernameField           = "Username";
    QString websiteField            = "Website";
    QString passwordField           = "Password";
    QString descriptionField        = "Description";

    QString getSelectQueryString(const QString& cur_user){
        QString comma = " ,";
        QString query = "SELECT * from " + selectFunctionName + "('" + cur_user + "');";
        return query;
    }

    QString getInsertQueryString(const Password& password, const int& owner){
        QString query = "exec " + insertProcedureName + " @title='" + password.title() + "',@expDate='" + password.expiration() + "',@username='" + password.username() +
                "',@password='" + password.password() + "',@website='" + password.website() + "',@description='" + password.description() +
                "',@owner=" + QString::number(owner)+";";
        return query;
    }

    QString getDeletionQueryString(const int& id, const int& owner){
        QString query = "exec " + deletionProcedureName + " @itemID=" + QString::number(id) + ", @owner=" + QString::number(owner)+";";
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
