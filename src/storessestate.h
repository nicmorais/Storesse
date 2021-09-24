#ifndef STORESSESTATE_H
#define STORESSESTATE_H

#include "storesseentity.h"
#include <QObject>

class StoresseState : public StoresseEntity
{

public:
    StoresseState(QObject *parent = nullptr);

    QList<QVariant> getSummaryFields() override;

    int id;

    int countryId;

    QString name;

    QString code;

//    StoresseCountry country;

    void setId(int id);

    void getData();

};
#endif // STORESSESTATE_H
