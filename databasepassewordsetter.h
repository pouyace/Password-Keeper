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
protected:
    void closeEvent(QCloseEvent *) override;
private:
    Ui::DataBasePassewordSetter *ui;
public slots:
    void onApplyButton();
    void onDatabaseConnected(bool state);
signals:
    void databaseNewConfigSet(QString,QString);
    void bikhialState();
    void dialodClosed();
};

#endif // DATABASEPASSEWORDSETTER_H
