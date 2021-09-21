#include "storessesale.h"

StoresseSale::StoresseSale(QObject *parent) : StoresseEntity(parent)
{

}

QList<QVariant> StoresseSale::getSummaryFields(){
    QList<QVariant> fields;

    fields.append("id");
    fields.append("customer_name");
    fields.append("customer_id");
    fields.append("amount");
    fields.append("discount");

    return fields;
}
