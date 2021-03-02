#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define DEFAULTDATABASEUSERNAME "postgres"
#define DEFAULTDATABASEPASSWORD "newpouya"

class DataBasePassewordSetter;
class PasswordHandler;
class LoginDialog;
class PostgreSqlVerifier;
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
    bool isDataBaseConnected()const;
private:
    Ui::MainWindow *ui;
    bool isDatabaseConnected = false;
    PasswordHandler         *passwordHandler              =  nullptr;
    LoginDialog             *loginDialog                  =  nullptr;
    PostgreSqlVerifier      *databaseVerifier             =  nullptr;
    User                    *user                         =  nullptr;
    QButtonGroup            *buttonGroup                  =  nullptr;
    QTimer                  *timer                        =  nullptr;
    DataBasePassewordSetter *databasePasswordSetterDialog =  nullptr;
    TableView               *tableView                    =  nullptr;
    ItemInsertionDialog     *itemInsertionDialog          =  nullptr;

    //Methods
    void setupConnections();
    void initializeObjects();
    void setupMainWindow();
private slots:
    void updateDateAndTime();
    void onInsertNewPassword();
    void connectToDatabase();
public slots:
    void onSetSignedUser(User* user);
    void updateDatabaseUserAndPass(QString user,QString pass);
signals:
    void databaseConnected(bool);
    void databaseDialogClosed();
};
#endif // MAINWINDOW_H
