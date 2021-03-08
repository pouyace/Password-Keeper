#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H
#include <QWidget>
#include "Handlers/passwordhandler.h"

namespace Ui {
class PasswordGenerator;
}

class PasswordGenerator : public QWidget
{
    Q_OBJECT
public:
    typedef PasswordHandler::PasswordType PasswordType;
    typedef PasswordHandler::Options Options;
    explicit PasswordGenerator(QWidget *parent = nullptr);
    ~PasswordGenerator();
private:
    Ui::PasswordGenerator *ui;
    OptionFalgs optionFlags;
    FeaturesData featureData;
    Options options;
    // Methods
    void updateTypes();
    void updateFlags();
    void updateFeatures();
public slots:
    void onGenerateClicked();
    void onShowResult(const int &count, const int &length, const QStringList &passwords, const QStringList &hashes, const bool dbState);
signals:
    void passwordGeneratingRequested(Options,FeaturesData,OptionFalgs);
};

#endif // PASSWORDGENERATOR_H
