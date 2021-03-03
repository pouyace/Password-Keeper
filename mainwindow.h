#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define DEFAULTDATABASEUSERNAME "postgres"
#define DEFAULTDATABASEPASSWORD "12345"

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
class MainWindow : public QMainWindow
{
    Q_OBJECT

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

    //Methods
    void setupConnections();
    void initializeObjects();
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
