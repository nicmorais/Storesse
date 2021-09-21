#ifndef STORESSESTATE_H
#define STORESSESTATE_H

#include "storesseentity.h"
#include <QObject>

class StoresseState : public StoresseEntity
{
    Q_OBJECT
public:
    explicit StoresseState(QObject *parent = nullptr);

    QList<QVariant> getSummaryFields() override;
};
#endif // STORESSESTATE_H
