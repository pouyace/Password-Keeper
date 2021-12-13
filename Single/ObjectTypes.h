#ifndef OBJECTTYPES_H
#define OBJECTTYPES_H
#include <QStringList>

enum PasswordType{LowerCases=1,UpperCases=2,symbols=4,Numbers=8,SpecialChars=16};

struct OptionFalgs{
    bool saveToDB   = 0;
    bool showHash   = 0;
    bool SPS        = 0;
    bool knownWords = 0;
    bool noDupChars = 0;
    bool noSeqChars = 0;
};

struct FeaturesData{
    QStringList includeList;
    QStringList excludeList;
    int length = 0;
    int count = 0;
};

struct PasswordDetails{
    OptionFalgs  flags;
    FeaturesData features;
    PasswordType type;
};

#endif // OBJECTTYPES_H
