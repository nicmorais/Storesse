#ifndef STORESSEPRODUCT_H
#define STORESSEPRODUCT_H

#include <QObject>
#include "storesseentity.h"
class StoresseProduct : public StoresseEntity
{
    Q_OBJECT
public:
    explicit StoresseProduct(QObject *parent = nullptr);

    QList<QVariant> getFields() override;
signals:

};

#endif // STORESSEPRODUCT_H
