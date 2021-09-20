#ifndef STORESSEENTITY_H
#define STORESSEENTITY_H

#include <QObject>
#include <QVariant>

class StoresseEntity : public QObject
{
    Q_OBJECT
public:
    explicit StoresseEntity(QObject *parent = nullptr);

    enum entity{
        Customer,
        Product,
        Sale,
        SaleProduct,
        Country,
        State,
        City,
        User,
    };

    virtual QList<QVariant> getFields();
signals:


};

#endif // STORESSEENTITY_H
