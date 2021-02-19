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
class User;
class QButtonGroup;
class QTimer;
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
    User               *user            = nullptr;
    QButtonGroup        *buttonGroup    = nullptr;
    QTimer              *timer          = nullptr;
    //Methods
    void setupConnections();
    void setupLoginDialog();
    void setupButtonGroup();
    void setupTime();

private slots:
    void updateDateAndTime();
public slots:
    void setupMainWondow(User* user);
};
#endif // MAINWINDOW_H
