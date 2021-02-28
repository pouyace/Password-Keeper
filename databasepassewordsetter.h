#ifndef DATABASEPASSEWORDSETTER_H
#define DATABASEPASSEWORDSETTER_H

#include <QDialog>

namespace Ui {
class DataBasePassewordSetter;
}

class DataBasePassewordSetter : public QDialog
{
    Q_OBJECT

public:
    explicit DataBasePassewordSetter(QString defaultUsername, QString defaultPassword, QWidget *parent = nullptr);
    ~DataBasePassewordSetter();

private:
    Ui::DataBasePassewordSetter *ui;
private slots:
    void onApplyButton();
    void databaseConfirmed(bool state);
signals:
    void databaseNewConfigSet(QString,QString);
    void bikhialState();

};

#endif // DATABASEPASSEWORDSETTER_H
