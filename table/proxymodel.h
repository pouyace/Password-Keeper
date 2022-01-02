#ifndef PROXYMODEL_H
#define PROXYMODEL_H
#include <QSortFilterProxyModel>

class ProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    ProxyModel(QObject *parent);
    bool validsOnly = false;
protected:
      bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
};

#endif // PROXYMODEL_H
