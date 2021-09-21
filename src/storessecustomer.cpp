#include "storessecustomer.h"

StoresseCustomer::StoresseCustomer(QObject *parent) : StoresseEntity(parent)
{

}

void StoresseCustomer::setId(int id){
    this->id = id;
}

void StoresseCustomer::getData(){

}


QList<QVariant> StoresseCustomer::getSummaryFields(){
    QList<QVariant> fields;

    fields.append("id");
    fields.append("name");
    fields.append("document");
    fields.append("email");

    return fields;
}
