#include "mainwindow.h"

#include <QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFile cssfile(":/style.css");
    cssfile.open(QIODevice::ReadOnly);
    a.setStyleSheet(cssfile.readAll());
    cssfile.close();
    w.show();
    return a.exec();
}
