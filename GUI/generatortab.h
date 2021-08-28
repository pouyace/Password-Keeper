#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H
#include <QWidget>
#include "Handlers/passwordgenerator.h"

namespace Ui {
class GeneratorTab;
}

class GeneratorTab : public QWidget
{
    Q_OBJECT
public:
//    PasswordGenerator a;
//    typedef PasswordGenerator::PasswordType PasswordType;
//    typedef PasswordGenerator::Options Options;
    explicit GeneratorTab(QWidget *parent = nullptr);
    ~GeneratorTab();
private:
    Ui::GeneratorTab *ui;
//    OptionFalgs optionFlags;
//    FeaturesData featureData;
//    Options options;
    // Methods
    void updateTypes();
    void updateFlags();
    void restoreDefaults();
    void updateFeatures();
public slots:
    void onGenerateClicked();
    void onShowResult(const int &count, const int &length, const QStringList &passwords, const QStringList &hashes, const bool dbState);
signals:
//    void passwordGeneratingRequested(Options,FeaturesData,OptionFalgs);
};

#endif // PASSWORDGENERATOR_H
