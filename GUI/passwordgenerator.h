#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H
#include <QWidget>
#include "Handlers/passwordhandler.h"

struct OptionFalgs{
    bool saveToDB   = 0;
    bool showHash   = 0;
    bool SPS        = 0;
    bool knownWords = 0;
    bool noDupChars = 0;
    bool noSeqChars = 0;
};
namespace Ui {
class PasswordGenerator;
}

class PasswordGenerator : public QWidget
{
    Q_OBJECT
public:
    typedef PasswordHandler::Options Options;
    explicit PasswordGenerator(QWidget *parent = nullptr);
    ~PasswordGenerator();
private:
    Ui::PasswordGenerator *ui;
    OptionFalgs optionFlags;
    // Methods
    void updateFlags();
signals:
    void passwordGeneratingRequested(Options passwordsType, int length, int count, OptionFalgs flags);
};

#endif // PASSWORDGENERATOR_H
