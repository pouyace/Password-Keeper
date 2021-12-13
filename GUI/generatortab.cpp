#include "generatortab.h"
#include "ui_generatortab.h"

GeneratorTab::GeneratorTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneratorTab)
{
    ui->setupUi(this);
}

GeneratorTab::~GeneratorTab()
{
    delete ui;
}

void GeneratorTab::setupConnections()
{

}

void GeneratorTab::updateTypes()
{
//    Options op = 0;
//    if(ui->uppercaseCheckBox->isChecked())
//        op |= PasswordGenerator::UpperCases;
//    if(ui->lowercaseCheckBox->isChecked())
//        op |= PasswordGenerator::LowerCases;
//    if(ui->symbolsCheckBox->isChecked())
//        op |= PasswordGenerator::symbols;
//    if(ui->ambiguousCharsCheckBox->isChecked())
//        op |= PasswordGenerator::SpecialChars;
//    if(ui->numbersCheckBox->isChecked())
//        op |= PasswordGenerator::Numbers;
//    options = op;
}

void GeneratorTab::updateFlags()
{
//    optionFlags.saveToDB   = ui->saveInDBCheckBox->isChecked();
//    optionFlags.showHash   = ui->showHashedCheckBox->isChecked();
    data.flags.SPS        = ui->SPSCheckBox->isChecked();
    data.flags.knownWords = ui->knownWordsCheckBox->isChecked();
    data.flags.noDupChars = ui->duplicateCheckBox->isChecked();
    data.flags.noSeqChars = ui->sequentialCheckBox->isChecked();
}

void GeneratorTab::restoreDefaults()
{
    ui->tableWidget->clear();
    ui->SPSCheckBox->setChecked(false);
    ui->duplicateCheckBox->setChecked(false);
    ui->sequentialCheckBox->setChecked(false);
    ui->knownWordsCheckBox->setChecked(false);
    ui->includeLineEdit->clear();
    ui->excludeLineEdit->clear();
    ui->passwordLengthSpinBox->setValue(1);
    ui->passwordLengthSpinBox->setValue(1);
    ui->ambiguousCharsCheckBox->setChecked(false);

}

void GeneratorTab::updateFeatures()
{
    data.features.count        = ui->passwordCountSpinBox->value();
    data.features.length       = ui->passwordLengthSpinBox->value();
    data.features.includeList  = ui->includeLineEdit->text().split("",QString::SkipEmptyParts);
    data.features.excludeList  = ui->excludeLineEdit->text().split("",QString::SkipEmptyParts);
}

void GeneratorTab::onGenerateClicked()
{
    updateFlags();
    updateFeatures();
    updateTypes();
//    emit passwordGeneratingRequested(options,featureData,optionFlags);
}

void GeneratorTab::onShowResult(const int &count, const int &length, const QStringList &passwords, const QStringList &hashes, const bool dbState)
{

}
