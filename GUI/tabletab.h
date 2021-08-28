#ifndef TABLETAB_H
#define TABLETAB_H

#include <QWidget>


class TableView;
class Password;
class ItemInsertionDialog;
namespace Ui {
class TableTab;
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
    Ui::TableTab *ui;
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
    void onSyncClicked();
};

#endif // PASSWORDTABLEWIDGET_H
