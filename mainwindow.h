#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "keygrabaction.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class LoginDialog;
class PostgreSqlVerifier;
class UserController;
class User;
class QButtonGroup;
class QTimer;
class MainWindow : public QMainWindow, public KeyGrabAction
{
    Q_OBJECT
    KEYGRABACTION

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void raiseLoginPage();
private:
    Ui::MainWindow *ui;
    LoginDialog             *loginDialog                  =  nullptr;
    PostgreSqlVerifier      *databaseVerifier             =  nullptr;
    UserController          *userController               =  nullptr;

    QButtonGroup            *buttonGroup                  =  nullptr;
    QTimer                  *timer                        =  nullptr;

    //Methods
    void setupConnections();
    void initializeObjects();
    void initializeModules();
    void setupProperties();
private slots:
    void updateDateAndTime();
public slots:
    void setupMainWindow(User *user);
signals:
    void databaseDialogClosed();
    void connectToDatabaseRequested(QString,QString);
};
#endif // MAINWINDOW_H
