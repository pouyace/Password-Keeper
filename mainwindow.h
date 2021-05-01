#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "keygrabaction.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define DEFAULTDATABASEUSERNAME "postgres"
#define DEFAULTDATABASEPASSWORD "newpouya"
// 12345
//newpouya

class DataBasePassewordSetter;
class PasswordHandler;
class LoginDialog;
class PostgreSqlVerifier;
class UserController;
class User;
class QButtonGroup;
class ItemInsertionDialog;
class QTimer;
class TableView;
class PasswordGenerator;
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
    PasswordHandler         *passwordHandler              =  nullptr;
    LoginDialog             *loginDialog                  =  nullptr;
    PostgreSqlVerifier      *databaseVerifier             =  nullptr;
    QButtonGroup            *buttonGroup                  =  nullptr;
    QTimer                  *timer                        =  nullptr;
    DataBasePassewordSetter *databasePasswordSetterDialog =  nullptr;
    UserController          *userController               =  nullptr;
    TableView               *tableView                    =  nullptr;
    ItemInsertionDialog     *itemInsertionDialog          =  nullptr;
    PasswordGenerator       *generatorWidget              =  nullptr;

    //Methods
    void setupConnections();
    void initializeObjects();
    void setKeyGrabber();
    void setupProperties();
private slots:
    void updateDateAndTime();
    void onInsertNewPassword();
public slots:
    void setupMainWindow(User *user);
signals:
    void databaseDialogClosed();
    void connectToDatabaseRequested(QString,QString);
};
#endif // MAINWINDOW_H
