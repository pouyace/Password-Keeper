#include "passwordhandler.h"

#include <time.h>
#include <stdlib.h>
#include <QDebug>

PasswordHandler::PasswordHandler(QObject *parent):
    QObject(parent),
    _Hash(QCryptographicHash::Algorithm::Sha1)
{

}

QString PasswordHandler::getHashedPassword(QString pass)
{
   _Hash.addData(pass.toStdString().c_str(),pass.size());
   return QString(_Hash.result().toHex());
}

void PasswordHandler::setPasswordType(Options type)
{
    if(orderedPasswordType != type){
        orderedPasswordType = type;
        emit passwordTypeUpdated(orderedPasswordType);
    }
}

void PasswordHandler::setPasswordLength(const int &length)
{
    if(orderedPasswordLength != length){
        orderedPasswordLength = length;
    }
    emit passwordLengthUpdated(orderedPasswordLength);
}

void PasswordHandler::setPasswordCount(const int &count)
{
    if(orderedPasswordCount != count){
        orderedPasswordCount= count;
    }
    emit passwordCountUpdated(orderedPasswordCount);
}

void PasswordHandler::shufflePallet(int repeat)
{
    int j,k,i=0;
    int range = palletSize() - 1;
    srand(time(NULL));
    while(i<repeat){
        j = rand() % range;
        k = rand() % range;
        if(_Pallet.size() > j && _Pallet.size() > k){
            i++;
            _Pallet.swapItemsAt(j,k);
        }
    }
}

void PasswordHandler::viewPallet()
{
    QString palletString = "";
    qDebug()<<"--------------------------------- View Pallet ---------------------------------";
    for(int i=0;i<_Pallet.size();i++){
        palletString.append(_Pallet.value(i));

    }
    qDebug()<<"Pallet = " << palletString;
    qDebug()<<"--------------------------------- View Pallet ---------------------------------";
}

void PasswordHandler::viewPassword()
{
    qDebug()<<"--------------------------------- View Password ---------------------------------";
        for(int i=0;i<orderedPasswordCount;i++){
            qDebug()<<"Password:"<<passwordList[i]->string<<'\t'<<passwordList[i]->byteArray;
        }
}
void PasswordHandler::makePassword(int index)
{
    srand(time(NULL));
    while(passwordObject.string.length() != orderedPasswordLength){
        int index = rand()%palletSize();
        passwordObject.string.append(_Pallet.value(index));
    }
    qDebug()<<passwordObject.string;
    _Hash.addData(passwordObject.string.toStdString().c_str(),orderedPasswordLength);
    passwordObject.byteArray = _Hash.result().toHex();
}

void PasswordHandler::feedPalletWithLowers(bool set)
{
    if(!set)
        return;
    for(int i = 97; i <= 122; i++){
        _Pallet << char(i);
    }
}

int PasswordHandler::palletSize()
{
    return _Pallet.size();
}

void PasswordHandler::feedPalletWithUppers(bool set)
{
    if(!set)
        return;
    for(int i = 65; i <= 90; i++){
        _Pallet << char(i);
    }
}

void PasswordHandler::feedPalletWithNumbers(bool set)
{
    if(!set)
        return;
    for(int i = 48; i <= 57; i++){
        _Pallet << char(i);
    }
}

void PasswordHandler::feedPalletWithSpecialChars(bool set)
{
    if(!set)
        return;
    for(int i = 40; i <= 41; i++){
        _Pallet << char(i);
    }
    for(int i = 58; i <= 62; i++){
        _Pallet << char(i);
    }
    for(int i = 123; i <= 125; i++){
        _Pallet << char(i);
    }
    for(int i = 91; i <= 96; i++){
        _Pallet << char(i);
    }
    for(int i = 44; i <= 47; i++){
        _Pallet << char(i);
    }
}

void PasswordHandler::feedPalletWithSymbols(bool set)
{
    if(!set)
        return;
    _Pallet << char(33) << char(42) << char(43) << char(126) << char(94) << char(61);
    for(int i = 35; i <= 38; i++){
        _Pallet << char(i);
    }
    for(int i = 63; i <= 64; i++){
        _Pallet << char(i);
    }

}

void PasswordHandler::GeneratePassword(const int &length, Options type, int count)
{
    setPasswordType(type);
    setPasswordLength(length);
    setPasswordCount(count);
    buildPasswords();
    viewPassword();
}

QString PasswordHandler::decodePassword(QByteArray pass)
{

}

void PasswordHandler::feedPallet()
{
    bool a = (LowerCases & orderedPasswordType);
    _Pallet.clear();
    _Pallet.reserve(orderedPasswordLength);

    feedPalletWithLowers(orderedPasswordType.testFlag(LowerCases));
    feedPalletWithUppers(orderedPasswordType.testFlag(UpperCases));
    feedPalletWithNumbers(orderedPasswordType.testFlag(Numbers));
    feedPalletWithSymbols(orderedPasswordType.testFlag(symbols));
    feedPalletWithSpecialChars(orderedPasswordType.testFlag(SpecialChars));

}

void PasswordHandler::buildPasswords()
{
    feedPallet();
    qDeleteAll(passwordList);
    passwordList.clear();
    int counter = 0;
    while(orderedPasswordCount != counter){
        passwordObject.string = "";
        passwordObject.byteArray = 0;
        shufflePallet();
        makePassword(counter);
        passwordList.append(new PasswordObject(passwordObject));
        counter++;
    }
    emit passwordGenerated(passwordList);
}
