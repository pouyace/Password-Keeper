#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
    bool databaseState = false;
    //Methods
    void setupConnection();

private slots:
    void onLoginButtonClicked();
public slots:
    void setDatabaseState(const bool& state);
    void setError(const QString& error);
    void onDatabaseDialogClosed();
    void onSetHint(QString hint);
signals:
    void loginRequested(QString,QString);
    void databaseIsNotConnected();
};

#endif // LOGINDIALOG_H
