#include "storessecountry.h"

StoresseCountry::StoresseCountry(QObject *parent) : StoresseEntity(parent)
{

}

QList<QVariant> StoresseCountry::getSummaryFields(){
    QList<QVariant> fields;

    fields.append("id");
    fields.append("name");
    fields.append("code");
    return fields;
}
