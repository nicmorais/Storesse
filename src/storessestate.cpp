#include "storessestate.h"

StoresseState::StoresseState(QObject *parent) : StoresseEntity(parent)
{

}

QList<QVariant> StoresseState::getSummaryFields(){
    QList<QVariant> fields;

    fields.append("id");
    fields.append("name");

    return fields;
}
