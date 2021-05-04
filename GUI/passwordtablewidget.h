#ifndef PASSWORDTABLEWIDGET_H
#define PASSWORDTABLEWIDGET_H

#include <QWidget>


class TableView;
class Password;
class ItemInsertionDialog;
namespace Ui {
class PasswordTableWidget;
}

class PasswordTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PasswordTableWidget(QWidget *parent = nullptr);
    ~PasswordTableWidget();
    void syncTableSize();

private:
    Ui::PasswordTableWidget *ui;
    TableView               *tableView           =  nullptr;
    ItemInsertionDialog     *itemInsertionDialog =  nullptr;

    void setupProperties();
    void setupConnection();

public slots:
    void updateTotPass(int count);
    void upadteTotSite(int count);

signals:
    void removeItemRequested();
    void addItemRequested(QList<Password*>);
    void itemInsertionRequested(Password*);
    void insertionResult(bool);
};

#endif // PASSWORDTABLEWIDGET_H
