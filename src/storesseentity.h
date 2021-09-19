#ifndef STORESSEENTITY_H
#define STORESSEENTITY_H

#include <QObject>

class StoresseEntity : public QObject
{
    Q_OBJECT
public:
    explicit StoresseEntity(QObject *parent = nullptr);

    enum Entity{
        Customer,
        Product,
        Sale,
        SaleProduct,
        Country,
        State,
        City,
        User,
    };

signals:

};

#endif // STORESSEENTITY_H
