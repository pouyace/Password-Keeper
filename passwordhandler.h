#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H
#include <QCryptographicHash>
#include <QObject>
class PasswordHandler:public QObject
{
    Q_OBJECT
public:
    enum PasswordType{lowerCaseOnly=0X0001,UpperCaseOnly=0X0010,LettersOnly=0X0011,NumbersOnly=0X0100
                      ,SpecialCharsOnly=0X1000,NumbersAndLetters=0X0111,AllChars=0X1111};
    PasswordHandler(QObject *parent);
private:
    QCryptographicHash _Hash;
    QList <char> _Pallet;
    PasswordType _PasswordType = AllChars;
    int _PasswordLength = 10;
    QString _Password = "";
    QByteArray _ByteArrayPassword;
    //Methods
    void feedPallet();
    void setPasswordType(PasswordType type);
    void setPasswordLength(const int& length);
    void shufflePallet(int repeat = 40);
    void viewPallet();
    void clearPassword();
    void viewPassword();
    void makePassword();
    QString hashedPasswordString();
    QString passwordString();
    int palletSize();
    void feedPalletWithLowers();
    void feedPalletWithUppers();
    void feedPalletWithNumbers();
    void feedPalletWithSpecialChars();
    void feedPalletWithLetters();
    void feedPalletWithNumbersAndLetters();
    void feedPalletWithAlls();
public slots:
    QByteArray GeneratePassword(const int& length = 10,PasswordType = PasswordType::AllChars);
    QString decodePassword(QByteArray pass);

signals:
    void passwordTypeUpdated(PasswordType);

};

#endif // PASSWORDGENERATOR_H
