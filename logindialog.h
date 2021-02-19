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
    void loginPressed();
public slots:
    void setDatabase1State(const bool& state);
    void setDatabase2State(const bool& state);
    void setError(const QString& error, const QString& hint);
signals:
    void loginRequested(QString,QString);
    void closeAppRequested();
};

#endif // LOGINDIALOG_H
