#include "storessecity.h"
#include "httprequest.h"

StoresseCity::StoresseCity(QObject *parent) : StoresseEntity(parent)
{

}

QList<QVariant> StoresseCity::getSummaryFields(){
    QList<QVariant> fields;

    fields.append("name");
    fields.append("id");

    return fields;
}
