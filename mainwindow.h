#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class PasswordHandler;
class LoginDialog;
class PostgreSqlVerifier;
class User;
class QButtonGroup;
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
    PasswordHandler *passwordHandler     =  nullptr;
    LoginDialog     *loginDialog         =  nullptr;
    PostgreSqlVerifier *databaseVerifier =  nullptr;
    User               *user             =  nullptr;
    QButtonGroup        *buttonGroup     =  nullptr;
    QTimer              *timer           =  nullptr;
    TableView     *tableView       =  nullptr;

    //Methods
    void setupConnections();
    void initializeObjects();
    void setupMainWindow();
private slots:
    void updateDateAndTime();
public slots:
    void onSetSignedUser(User* user);
};
#endif // MAINWINDOW_H
