#ifndef OBJECTTYPES_H
#define OBJECTTYPES_H
#include <QStringList>

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

#endif // OBJECTTYPES_H
