#include "storessecustomer.h"

StoresseCustomer::StoresseCustomer(QObject *parent) : StoresseEntity(parent)
{

}

void StoresseCustomer::setId(int id){
    this->id = id;
}

void StoresseCustomer::getData(){

}

void StoresseCustomer::setName(QString name){
    this->name = name;
}

QString StoresseCustomer::getName(){
    return name;
}

QList<QVariant> StoresseCustomer::getFields(){
    QList<QVariant> fields;

    fields.append("id");
    fields.append("name");
    fields.append("document");
    fields.append("email");

    return fields;

}
