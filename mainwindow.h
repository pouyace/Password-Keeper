#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class PasswordHandler;
class LoadingDialog;
class LoginDialog;
class PostgreSqlVerifier;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    PasswordHandler *passwordGenerator = nullptr;
    LoadingDialog   *loadingDialog     = nullptr;
    LoginDialog     *loginDialog       = nullptr;
    PostgreSqlVerifier *databaseVerifier = nullptr;
    //Methods
    void setupConnections();
    void setupLoadingDialog();
    void setupLoginDialog();
    void setupSqlVerifier();
    void setupPasswordGenerator();

};
#endif // MAINWINDOW_H
