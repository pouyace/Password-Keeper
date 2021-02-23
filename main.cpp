#include "mainwindow.h"

#include <QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile cssfile(":/style.css");
    cssfile.open(QIODevice::ReadOnly);
    MainWindow w;
    a.setStyleSheet(cssfile.readAll());
    cssfile.close();
//    w.show();
    w.raiseLoginPage();
    return a.exec();
}
