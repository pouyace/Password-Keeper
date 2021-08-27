#ifndef PASSWORDTABLEWIDGET_H
#define PASSWORDTABLEWIDGET_H

#include <QWidget>


class TableView;
class Password;
class ItemInsertionDialog;
namespace Ui {
class PasswordTableWidget;
}

class TableTab : public QWidget
{
    Q_OBJECT

public:
    explicit TableTab(QWidget *parent = nullptr);
    ~TableTab();
    TableView* tableView()const;
    ItemInsertionDialog* insertionDialog()const;

private:
    Ui::PasswordTableWidget *ui;
    TableView               *_tableView           =  nullptr;
    ItemInsertionDialog     *itemInsertionDialog  =  nullptr;

    void setupProperties();
    void setupConnection();

private slots:
    void filterTableItems(QString text);

public slots:
    void updateTotPass(int count);
    void upadteTotSite(int count);

signals:
    void filterItems(const QRegExp&);
};

#endif // PASSWORDTABLEWIDGET_H
