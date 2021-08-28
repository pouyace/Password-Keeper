#include "passwordgenerator.h"

#include <time.h>
#include <stdlib.h>
#include <QDebug>

PasswordGenerator::PasswordGenerator(QObject *parent):
    QObject(parent),
    _Hash(QCryptographicHash::Algorithm::Sha1)
{

}

QString PasswordGenerator::getHashedPassword(QString pass)
{
   _Hash.addData(pass.toStdString().c_str(),pass.size());
   return QString(_Hash.result().toHex());
}

void PasswordGenerator::setPasswordType(Options type)
{
    if(info.orderedPasswordType != type){
        info.orderedPasswordType = type;
        emit passwordTypeUpdated(info.orderedPasswordType);
    }
}

void PasswordGenerator::setPasswordLength(const int &length)
{
    if(info.orderedPasswordLength != length){
        info.orderedPasswordLength = length;
    }
    emit passwordLengthUpdated(info.orderedPasswordLength);
}

void PasswordGenerator::setPasswordCount(const int &count)
{
    if(info.orderedPasswordCount != count){
        info.orderedPasswordCount= count;
    }
    emit passwordCountUpdated(info.orderedPasswordCount);
}

void PasswordGenerator::shufflePallet(int repeat)
{
    int j,k,i=0;
    int range = palletSize() - 1;
    srand(time(NULL));
    while(i<repeat){
        j = rand() % range;
        k = rand() % range;
        if(_Pallet.size() > j && _Pallet.size() > k){
            i++;
//            _Pallet.swapItemsAt(j,k);
        }
    }
}

void PasswordGenerator::viewPallet()
{
    QString palletString = "";
    qDebug()<<"--------------------------------- View Pallet ---------------------------------";
    for(int i=0;i<_Pallet.size();i++){
        palletString.append(_Pallet.value(i));

    }
    qDebug()<<"Pallet = " << palletString;
    qDebug()<<"--------------------------------- View Pallet ---------------------------------";
}

void PasswordGenerator::viewPassword()
{
    qDebug()<<"--------------------------------- View Password ---------------------------------";
        for(int i=0;i<info.orderedPasswordCount;i++){
            qDebug()<<"Password:"<<passwordList[i]->string<<'\t'<<passwordList[i]->byteArray;
        }
}
void PasswordGenerator::makePassword(int index)
{
    Q_UNUSED(index)
    srand(time(NULL));
    while(passwordObject.string.length() != info.orderedPasswordLength){
        int index = rand()%palletSize();
        passwordObject.string.append(_Pallet.value(index));
    }
    qDebug()<<passwordObject.string;
    _Hash.addData(passwordObject.string.toStdString().c_str(),info.orderedPasswordLength);
    passwordObject.byteArray = _Hash.result().toHex();
}

void PasswordGenerator::feedPalletWithLowers(bool set)
{
    if(!set)
        return;
    for(int i = 97; i <= 122; i++){
        _Pallet << char(i);
    }
}

int PasswordGenerator::palletSize()
{
    return _Pallet.size();
}

void PasswordGenerator::feedPalletWithUppers(bool set)
{
    if(!set)
        return;
    for(int i = 65; i <= 90; i++){
        _Pallet << char(i);
    }
}

void PasswordGenerator::feedPalletWithNumbers(bool set)
{
    if(!set)
        return;
    for(int i = 48; i <= 57; i++){
        _Pallet << char(i);
    }
}

void PasswordGenerator::feedPalletWithSpecialChars(bool set)
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

void PasswordGenerator::feedPalletWithSymbols(bool set)
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

void PasswordGenerator::GeneratePassword(const Options &options,const FeaturesData &features,const OptionFalgs &optionFlags)
{
    Q_UNUSED(optionFlags)
    setPasswordType(options);
    setPasswordLength(features.length);
    setPasswordCount(features.count);
    buildPasswords();
    viewPassword();
}

QString PasswordGenerator::decodePassword(QByteArray pass)
{
    Q_UNUSED(pass)
    return "";
}

void PasswordGenerator::feedPallet()
{
    bool a = (LowerCases & info.orderedPasswordType);
    Q_UNUSED(a)
    _Pallet.clear();
    _Pallet.reserve(info.orderedPasswordLength);

    feedPalletWithLowers(info.orderedPasswordType.testFlag(LowerCases));
    feedPalletWithUppers(info.orderedPasswordType.testFlag(UpperCases));
    feedPalletWithNumbers(info.orderedPasswordType.testFlag(Numbers));
    feedPalletWithSymbols(info.orderedPasswordType.testFlag(symbols));
    feedPalletWithSpecialChars(info.orderedPasswordType.testFlag(SpecialChars));

}

void PasswordGenerator::buildPasswords()
{
    feedPallet();
    qDeleteAll(passwordList);
    passwordList.clear();
    int counter = 0;
    while(info.orderedPasswordCount != counter){
        passwordObject.string = "";
        passwordObject.byteArray = 0;
        shufflePallet();
        makePassword(counter);
        passwordList.append(new PasswordObject(passwordObject));
        counter++;
    }
    emit passwordGenerated(passwordList);
}
