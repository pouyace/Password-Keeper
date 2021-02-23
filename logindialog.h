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
    //Methods
    void setupConnection();

private slots:
    void onLoginButtonClicked();
public slots:
    void setDatabaseState(const bool& state);
    void setError(const QString& error, const QString& hint);
    void userSignedin(bool state);
signals:
    void loginRequested(QString,QString);
};

#endif // LOGINDIALOG_H
