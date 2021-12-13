#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H
#include <QCryptographicHash>
#include <QObject>
#include "../Single/ObjectTypes.h"
class Password;
class PasswordGenerator:public QObject
{
    Q_OBJECT
public: 
    Q_DECLARE_FLAGS(Options, PasswordType);
    Q_FLAG(Options)
    PasswordGenerator(QObject *parent);
    QString getHashedPassword(QString pass);
private:
    struct orderInfo{
    int orderedPasswordCount = 0;
    Options orderedPasswordType;
    int orderedPasswordLength = 0;
    }info;
    QCryptographicHash _Hash;
    QList <char> _Pallet;
    struct PasswordObject{
        QByteArray byteArray;
        QString string = "";
        PasswordObject(){
            byteArray = 0;
            string = "";
        }
        PasswordObject(QString passString,QByteArray passHash){
            byteArray = passHash;
            string = passString;
        }
        PasswordObject(const PasswordObject& obj){
            string      =  obj.string;
            byteArray   =  obj.byteArray;
        }
    }passwordObject;
    QList <PasswordObject*> passwordList;

    //Methods
    void feedPallet();
    void buildPasswords();
    void setPasswordType(PasswordGenerator::Options type);
    void setPasswordLength(const int& length);
    void setPasswordCount(const int& count);
    void shufflePallet(int repeat = 50);
    void viewPallet();
    void viewPassword();
    void makePassword(int index);
    int palletSize();
    void feedPalletWithLowers(bool set);
    void feedPalletWithUppers(bool set);
    void feedPalletWithNumbers(bool set);
    void feedPalletWithSpecialChars(bool set);
    void feedPalletWithSymbols(bool set);
public slots:
    void GeneratePassword(const Options &options, const FeaturesData &features, const OptionFalgs &optionFlags);
    QString decodePassword(QByteArray pass);

signals:
    void passwordTypeUpdated(Options);
    void passwordLengthUpdated(int);
    void passwordCountUpdated(int);
    void passwordGenerated(QList<PasswordObject*>);

};
Q_DECLARE_OPERATORS_FOR_FLAGS(PasswordGenerator::Options)
#endif // PASSWORDGENERATOR_H
