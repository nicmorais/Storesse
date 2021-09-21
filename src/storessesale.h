#ifndef STORESSESALE_H
#define STORESSESALE_H

#include "storesseentity.h"

class StoresseSale : public StoresseEntity
{

public:
    StoresseSale(QObject *parent = nullptr);

    QList<QVariant> getSummaryFields();
};

#endif // STORESSESALE_H
