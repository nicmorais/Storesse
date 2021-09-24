#ifndef STORESSECITY_H
#define STORESSECITY_H

#include <QObject>
#include "storesseentity.h"

class StoresseCity : public StoresseEntity
{
    Q_OBJECT
public:
    explicit StoresseCity(QObject *parent = nullptr);

    QList<QVariant> getSummaryFields() override;

    int id;

    QString name;

    int stateId;

    int countryId;

    void getData();
Q_SIGNALS:

};

#endif // STORESSECITY_H
