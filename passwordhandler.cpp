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

void PasswordHandler::setPasswordType(PasswordHandler::PasswordType type)
{
    if(_PasswordType != type){
        _PasswordType = type;
        emit passwordTypeUpdated(_PasswordType);
    }
}

void PasswordHandler::setPasswordLength(const int &length)
{
    if(_PasswordLength != length){
        _PasswordLength = length;
    }
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

void PasswordHandler::clearPassword()
{
    _Password = "";
    _ByteArrayPassword = 0;
    _Hash.reset();
}

void PasswordHandler::viewPassword()
{
    qDebug()<<"--------------------------------- View Password ---------------------------------";
    qDebug()<<"Password:"<<_Password;
}

QString PasswordHandler::hashedPasswordString()
{
    return _Hash.result();
}

void PasswordHandler::makePassword()
{
    srand(time(NULL));
    while(_Password.length() != _PasswordLength){
        int index = rand()%palletSize();
        _Password.append(_Pallet.value(index));
    }
    qDebug()<<_Password;
    _Hash.addData(_Password.toStdString().c_str(),_PasswordLength);
    _ByteArrayPassword = _Hash.result().toHex();
}

QString PasswordHandler::passwordString()
{
    return _Password;
}

void PasswordHandler::feedPalletWithLowers()
{
    for(int i = 97; i <= 122; i++){
        _Pallet << char(i);
    }
}

int PasswordHandler::palletSize()
{
    return _Pallet.size();
}

void PasswordHandler::feedPalletWithUppers()
{
    for(int i = 65; i <= 90; i++){
        _Pallet << char(i);
    }
}

void PasswordHandler::feedPalletWithNumbers()
{
    for(int i = 48; i <= 57; i++){
        _Pallet << char(i);
    }
}

void PasswordHandler::feedPalletWithSpecialChars()
{
    _Pallet << char(33) << char(42) << char(43);
    for(int i = 35; i <= 38; i++){
        _Pallet << char(i);
    }
    for(int i = 58; i <= 64; i++){
        _Pallet << char(i);
    }
}

void PasswordHandler::feedPalletWithLetters()
{
    feedPalletWithLowers();
    feedPalletWithUppers();
}

void PasswordHandler::feedPalletWithNumbersAndLetters()
{
    feedPalletWithLetters();
    feedPalletWithNumbers();
}

void PasswordHandler::feedPalletWithAlls()
{
    feedPalletWithLowers();
    feedPalletWithUppers();
    feedPalletWithNumbers();
    feedPalletWithSpecialChars();
}

QByteArray PasswordHandler::GeneratePassword(const int &length, PasswordHandler::PasswordType type)
{
    setPasswordType(type);
    setPasswordLength(length);
    feedPallet();
    clearPassword();
    makePassword();
    viewPassword();
    return _ByteArrayPassword;
}

QString PasswordHandler::decodePassword(QByteArray pass)
{

}

void PasswordHandler::feedPallet()
{
    _Pallet.clear();
    _Pallet.reserve(_PasswordLength);
    switch (_PasswordType) {
    case lowerCaseOnly:     feedPalletWithLowers();break;
    case UpperCaseOnly:     feedPalletWithUppers();break;
    case NumbersOnly:       feedPalletWithNumbers();break;
    case LettersOnly:       feedPalletWithLetters();break;
    case SpecialCharsOnly:  feedPalletWithSpecialChars();break;
    case NumbersAndLetters: feedPalletWithNumbersAndLetters();break;
    case AllChars:          feedPalletWithAlls();break;

    }
    qDebug()<<"Before Shuffle:";
    viewPallet();
    shufflePallet();
    qDebug()<<"After Shuffle:";
    viewPallet();
}
