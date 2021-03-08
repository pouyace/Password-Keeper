#include "passwordgenerator.h"
#include "ui_passwordgenerator.h"

PasswordGenerator::PasswordGenerator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PasswordGenerator)
{
    ui->setupUi(this);
//    PasswordHandler
}

PasswordGenerator::~PasswordGenerator()
{
    delete ui;
}

void PasswordGenerator::updateTypes()
{
    Options op = 0;
    if(ui->uppercaseCheckBox->isChecked())
        op |= PasswordHandler::UpperCases;
    if(ui->lowercaseCheckBox->isChecked())
        op |= PasswordHandler::LowerCases;
    if(ui->symbolsCheckBox->isChecked())
        op |= PasswordHandler::symbols;
    if(ui->ambiguousCharsCheckBox->isChecked())
        op |= PasswordHandler::SpecialChars;
    if(ui->numbersCheckBox->isChecked())
        op |= PasswordHandler::Numbers;
    options = op;
}

void PasswordGenerator::updateFlags()
{
    optionFlags.saveToDB   = ui->saveInDBCheckBox->isChecked();
    optionFlags.showHash   = ui->showHashedCheckBox->isChecked();
    optionFlags.SPS        = ui->SPSCheckBox->isChecked();
    optionFlags.knownWords = ui->knownWordsCheckBox->isChecked();
    optionFlags.noDupChars = ui->duplicateCheckBox->isChecked();
    optionFlags.noSeqChars = ui->sequentialCheckBox->isChecked();
}

void PasswordGenerator::updateFeatures()
{
    featureData.count = ui->passwordCountSpinBox->value();
    featureData.length = ui->passwordLengthSpinBox->value();
    featureData.includeList = ui->includeLineEdit->text().split("",QString::SkipEmptyParts);
    featureData.excludeList = ui->excludeLineEdit->text().split("",QString::SkipEmptyParts);
}

void PasswordGenerator::onGenerateClicked()
{
    updateFlags();
    updateFeatures();
    updateTypes();
    ui->ouputTextEdit->clear();
    emit passwordGeneratingRequested(options,featureData,optionFlags);
}

void PasswordGenerator::onShowResult(const int &count, const int &length, const QStringList &passwords, const QStringList &hashes, const bool dbState)
{

}
