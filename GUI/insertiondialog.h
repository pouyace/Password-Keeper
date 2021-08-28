#ifndef INSERTIONDIALOG_H
#define INSERTIONDIALOG_H

#include <QDialog>
#include "Single/password.h"
namespace Ui {
class ItemInsertionDialog;
}
class ItemInsertionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ItemInsertionDialog(QWidget *parent = nullptr);
    ~ItemInsertionDialog();
protected:
    virtual void closeEvent(QCloseEvent *) override;
private slots:
    void onInsertNewPassword();
private:
    Ui::ItemInsertionDialog *ui;
public slots:
    void onInsertionResult(bool state);
signals:
    void newInsertionRequested(Password*);

};

#endif // ITEMINSERTIONDIALOG_H
