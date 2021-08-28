#include "generatortab.h"
#include "ui_generatortab.h"

GeneratorTab::GeneratorTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneratorTab)
{
    ui->setupUi(this);
//    PasswordHandler
}

GeneratorTab::~GeneratorTab()
{
    delete ui;
}

void GeneratorTab::updateTypes()
{/*
    Options op = 0;
    if(ui->uppercaseCheckBox->isChecked())
        op |= PasswordGenerator::UpperCases;
    if(ui->lowercaseCheckBox->isChecked())
        op |= PasswordGenerator::LowerCases;
    if(ui->symbolsCheckBox->isChecked())
        op |= PasswordGenerator::symbols;
    if(ui->ambiguousCharsCheckBox->isChecked())
        op |= PasswordGenerator::SpecialChars;
    if(ui->numbersCheckBox->isChecked())
        op |= PasswordGenerator::Numbers;
    options = op;*/
}

void GeneratorTab::updateFlags()
{
//    optionFlags.saveToDB   = ui->saveInDBCheckBox->isChecked();
//    optionFlags.showHash   = ui->showHashedCheckBox->isChecked();
//    optionFlags.SPS        = ui->SPSCheckBox->isChecked();
//    optionFlags.knownWords = ui->knownWordsCheckBox->isChecked();
//    optionFlags.noDupChars = ui->duplicateCheckBox->isChecked();
//    optionFlags.noSeqChars = ui->sequentialCheckBox->isChecked();
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
//    featureData.count = ui->passwordCountSpinBox->value();
//    featureData.length = ui->passwordLengthSpinBox->value();
//    featureData.includeList = ui->includeLineEdit->text().split("",QString::SkipEmptyParts);
//    featureData.excludeList = ui->excludeLineEdit->text().split("",QString::SkipEmptyParts);
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
