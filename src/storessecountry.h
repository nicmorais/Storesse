#ifndef STORESSECOUNTRY_H
#define STORESSECOUNTRY_H

#include "storesseentity.h"
#include <QObject>

class StoresseCountry : public StoresseEntity
{
    Q_OBJECT
public:
    explicit StoresseCountry(QObject *parent = nullptr);

    QList<QVariant> getSummaryFields() override;

    int id;
    QString name;

};

#endif // STORESSECOUNTRY_H
