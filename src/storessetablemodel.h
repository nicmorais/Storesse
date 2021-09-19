#ifndef STORESSETABLEMODEL_H
#define STORESSETABLEMODEL_H

#include <QAbstractItemModel>
#include <QObject>

class StoresseTableModel : public QAbstractItemModel
{
public:
    explicit StoresseTableModel(QObject *parent = nullptr);
};

#endif // STORESSETABLEMODEL_H
