#include "storessecustomer.h"

StoresseCustomer::StoresseCustomer(QObject *parent) : QObject(parent)
{

}

void StoresseCustomer::setId(int id){
    this->id = id;
    emit idSet();
}

void StoresseCustomer::getData(){

}

void StoresseCustomer::setName(QString name){
    this->name = name;
}

QString StoresseCustomer::getName(){
    return name;
}
