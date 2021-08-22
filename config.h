#ifndef CONFIG_H
#define CONFIG_H
#include <QString>

struct Config;
namespace App_Config {
struct ApplicationDataTable;
struct UsersTable;
struct Config;
};

struct App_Config::ApplicationDataTable{
    QString tableName       = "app_data";
    QString idField         = "item_id";
    QString ownerUser       = "item_owner_user";
    QString usernameField   = "item_username";
    QString websiteField    = "item_website";
    QString passwordField   = "item_pass";
    QString sequenceCounter = "item_id_seq";

    QString getSelectQueryString(const QString& cur_user){
        QString comma = " ,";
        QString query = "SELECT "+idField+comma+usernameField+comma+passwordField+comma
                +websiteField+" FROM " + tableName + " WHERE " + ownerUser + "='" + cur_user+"';";
        return query;
    }

    QString getInsertQueryString(const QString& usernameItem, const QString& passItem, const QString& siteItem, const QString& owner){
        QString query = "insert into " + tableName + " values(nextval('"+sequenceCounter+"'),'"
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
    QString tableName       = "app_users";
    QString username        = "username";
    QString password        = "user_pass";
    QString firstname       = "fName";
    QString lastname        = "lName";
    QString hint            = "pass_hint";

    QString getSelectQueryString(const QString& cur_user){
        QString comma = " ,";
        QString query = "SELECT "+password+comma+firstname+comma+lastname+comma+hint
                +" FROM " + tableName + " WHERE " + username + "='" + cur_user+"';";
        return query;
    }

};

struct App_Config::Config{
    QString                 databaseName    = "PKDB";
    QString                 serverUsername  = "PKDBU";
    QString                 serverPassword  = "theonepouya";
    int                     port            = 5432;
    ApplicationDataTable    passwordsTable;
    UsersTable              usersTable;
};



#endif // CONFIG_H
