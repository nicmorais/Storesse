#include "storesseproduct.h"

StoresseProduct::StoresseProduct(QObject *parent) : StoresseEntity(parent)
{

}

QList<QVariant> StoresseProduct::getSummaryFields(){
    QList<QVariant> fields;

    fields.append("id");
    fields.append("name");
    fields.append("quantity");
    fields.append("price");
    fields.append("cost");
    fields.append("active");

    return fields;
}
