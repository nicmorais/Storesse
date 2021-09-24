#include "storessestate.h"
#include "httprequest.h"
StoresseState::StoresseState(QObject *parent) : StoresseEntity(parent)
{

}

void StoresseState::setId(int id){
    this->id = id;
}

void StoresseState::getData(){
    HttpRequest request;

    StoresseState *stateWithData = request.getStateData(id);

    name = stateWithData->name;

    countryId = stateWithData->countryId;
}

QList<QVariant> StoresseState::getSummaryFields(){
    QList<QVariant> fields;

    fields.append("name");
    fields.append("id");

    return fields;
}
