#include "httprequest.h"

#include <QDebug>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>
#include <QEventLoop>
#include <QJsonArray>
#include "storesseproduct.h"
#include "storessesale.h"
#include "storessecustomer.h"

HttpRequest::HttpRequest(QObject* parent) :
    QObject(parent)
{
    s_requestWithToken.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
}

QString HttpRequest::s_token;

QNetworkRequest HttpRequest::s_requestWithToken;

QUrl HttpRequest::s_baseUrl;

int HttpRequest::port;

void HttpRequest::setUseSsl(bool useSsl){
    this->useSsl = useSsl;
}

void HttpRequest::login(QString email, QString password){
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginReplyFinished(QNetworkReply*)));

    this->email = email;

    QUrl signInUrl;

    if(useSsl){
        s_baseUrl = QString("https://%1:%2/api/").arg(hostname.toString()).arg(port);
    }else{
        s_baseUrl = QString("http://%1:%2/api/").arg(hostname.toString()).arg(port);
    }
    signInUrl.setUrl(s_baseUrl.toString() + "users/signin");

    QNetworkRequest request(signInUrl);

    QJsonObject credentialsJson;
    credentialsJson.insert("email", email);
    credentialsJson.insert("password", password);

    QJsonDocument jsonDoc(credentialsJson);
    QByteArray jsonData = jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(jsonData.size()));


    request.setAttribute(QNetworkRequest::Http2AllowedAttribute, false);
    networkManager->post(request, jsonData);
}

void HttpRequest::loginReplyFinished(QNetworkReply* reply){
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if(statusCode != 201){
        qDebug()<< tr("Could not connect to server. HTTP Status code: ") + QString::number(statusCode);
        emit loginFailed(statusCode);
    }else{

        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        QString token = jsonDoc.toVariant().toJsonObject()["token"].toString();

        HttpRequest::s_token = token;
        QString bearer = "Bearer: " +  s_token;
        s_requestWithToken.setRawHeader("Authorization: ", bearer.toLocal8Bit());
        s_requestWithToken.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

        emit loggedIn();
    }

    reply->deleteLater();

    QObject::disconnect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginReplyFinished(QNetworkReply*)));
}

QString HttpRequest::getEmail(){
    return this->email;
}

void HttpRequest::setHostname(QString hostname){
    this->hostname = hostname;
}

void HttpRequest::setPort(int port){
    this->port = port;
}

StoresseCustomer* HttpRequest::getCustomerData(int id){
    QNetworkAccessManager localManager;
    QEventLoop eventLoop;
    QObject::connect(&localManager, &QNetworkAccessManager::finished,
                     &eventLoop, &QEventLoop::quit);

    s_requestWithToken.setUrl(QUrl(QString(s_baseUrl.toString() + "customers/%1").arg(id)));

    QNetworkReply* reply = localManager.get(s_requestWithToken);
    eventLoop.exec();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());

    reply->deleteLater();

    StoresseCustomer *customer = new StoresseCustomer;
    customer->name = jsonDoc.toVariant().toMap()["data"].toMap()["name"].toString();
    customer->addressLine1 = jsonDoc.toVariant().toMap()["data"].toMap()["address_line1"].toString();
    customer->addressLine2 = jsonDoc.toVariant().toMap()["data"].toMap()["address_line2"].toString();
    customer->zipCode = jsonDoc.toVariant().toMap()["data"].toMap()["zip_code"].toString();
    customer->document = jsonDoc.toVariant().toMap()["data"].toMap()["document"].toString();
    customer->birthdate = jsonDoc.toVariant().toMap()["data"].toMap()["birthdate"].toDate();
    customer->email = jsonDoc.toVariant().toMap()["data"].toMap()["email"].toString();

    return customer;
}

QStandardItemModel* HttpRequest::getModel(StoresseEntity::entity entity){

    QStandardItemModel *model = new QStandardItemModel;

    QNetworkAccessManager localManager;
    QEventLoop eventLoop;
    QObject::connect(&localManager, &QNetworkAccessManager::finished,
                     &eventLoop, &QEventLoop::quit);
    QUrl url;

    StoresseEntity *entityObj;
    switch (entity) {
    case StoresseEntity::Customer:{
        entityObj = new StoresseCustomer();
        url.setUrl(QString(s_baseUrl.toString() + "customers"));
        break;
    }
    case StoresseEntity::Product:{
        entityObj = new StoresseProduct();
        url.setUrl(QString(s_baseUrl.toString() + "products"));
        break;
    }
    case StoresseEntity::Sale:{
        entityObj = new StoresseSale();
        url.setUrl(QString(s_baseUrl.toString() + "sales"));
        break;
    }
    }

    s_requestWithToken.setUrl(url);

    QNetworkReply* reply = localManager.get(s_requestWithToken);
    eventLoop.exec();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
    int row = 0;
    int column = 0;
    for (QVariant item : jsonDoc.toVariant().toMap()["data"].toList()){
        column = 0;

        for(QVariant &field : entityObj->getSummaryFields()){
            model->setItem(row, column, new QStandardItem(item.toMap()[field.toString()].toString()));
            column++;
        }
        row++;
    }

    int section = 0;
    for(QVariant &field : entityObj->getSummaryFields()){

        model->setHeaderData(section, Qt::Horizontal, field.toString().left(1).toUpper() + field.toString().mid(1));
        section++;

    }

    delete entityObj;
    return model;
}

QStandardItemModel* HttpRequest::getCustomersModel(QString name){
    QStandardItemModel *model = new QStandardItemModel;

    QNetworkAccessManager localManager;
    QEventLoop eventLoop;
    QObject::connect(&localManager, &QNetworkAccessManager::finished,
                     &eventLoop, &QEventLoop::quit);
    QUrl url;
    url.setUrl(QString(s_baseUrl.toString() + "customers?name=" + name));
    s_requestWithToken.setUrl(url);

    QNetworkReply* reply = localManager.get(s_requestWithToken);
    eventLoop.exec();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
    StoresseCustomer customer;

    int row = 0;
    int column = 0;
    for (QVariant item : jsonDoc.toVariant().toMap()["data"].toList()){
        column = 0;

        for(QVariant &field : customer.getSummaryFields()){
            model->setItem(row, column, new QStandardItem(item.toMap()[field.toString()].toString()));
            column++;
        }
        row++;
    }

    int section = 0;
    for(QVariant &field : customer.getSummaryFields()){

        model->setHeaderData(section, Qt::Horizontal, field.toString().left(1).toUpper() + field.toString().mid(1));
        section++;

    }
    return model;
}

QStandardItemModel* HttpRequest::getProductsModel(QString name){
    QStandardItemModel *model = new QStandardItemModel;

    QNetworkAccessManager localManager;
    QEventLoop eventLoop;
    QObject::connect(&localManager, &QNetworkAccessManager::finished,
                     &eventLoop, &QEventLoop::quit);
    QUrl url;
    url.setUrl(QString(s_baseUrl.toString() + "products?name=" + name));
    s_requestWithToken.setUrl(url);

    QNetworkReply* reply = localManager.get(s_requestWithToken);
    eventLoop.exec();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
    StoresseProduct product;

    int row = 0;
    int column = 0;
    for (QVariant item : jsonDoc.toVariant().toMap()["data"].toList()){
        column = 0;

        for(QVariant &field : product.getSummaryFields()){
            model->setItem(row, column, new QStandardItem(item.toMap()[field.toString()].toString()));
            column++;
        }
        row++;
    }

    int section = 0;
    for(QVariant &field : product.getSummaryFields()){

        model->setHeaderData(section, Qt::Horizontal, field.toString().left(1).toUpper() + field.toString().mid(1));
        section++;

    }
    return model;
}

QStandardItemModel* HttpRequest::getSalesModel(QString customerName, QDate date){
    QStandardItemModel *model = new QStandardItemModel;

    QNetworkAccessManager localManager;
    QEventLoop eventLoop;
    QObject::connect(&localManager, &QNetworkAccessManager::finished,
                     &eventLoop, &QEventLoop::quit);
    QUrl url;
    url.setUrl(QString(s_baseUrl.toString() + "sales?customer_name=" + customerName + "&date=" + date.toString(Qt::ISODate)));
    s_requestWithToken.setUrl(url);

    QNetworkReply* reply = localManager.get(s_requestWithToken);
    eventLoop.exec();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
    StoresseSale sale;

    int row = 0;
    int column = 0;
    for (QVariant item : jsonDoc.toVariant().toMap()["data"].toList()){
        column = 0;

        for(QVariant &field : sale.getSummaryFields()){
            model->setItem(row, column, new QStandardItem(item.toMap()[field.toString()].toString()));
            column++;
        }
        row++;
    }

    int section = 0;
    for(QVariant &field : sale.getSummaryFields()){

        model->setHeaderData(section, Qt::Horizontal, field.toString().left(1).toUpper() + field.toString().mid(1));
        section++;

    }
    return model;
}

QStandardItemModel* HttpRequest::getSalesModel(QString customerName){
    QStandardItemModel *model = new QStandardItemModel;

    QNetworkAccessManager localManager;
    QEventLoop eventLoop;
    QObject::connect(&localManager, &QNetworkAccessManager::finished,
                     &eventLoop, &QEventLoop::quit);
    QUrl url;
    url.setUrl(QString(s_baseUrl.toString() + "sales?customer_name=" + customerName));
    s_requestWithToken.setUrl(url);

    QNetworkReply* reply = localManager.get(s_requestWithToken);
    eventLoop.exec();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
    StoresseSale sale;

    int row = 0;
    int column = 0;
    for (QVariant item : jsonDoc.toVariant().toMap()["data"].toList()){
        column = 0;

        for(QVariant &field : sale.getSummaryFields()){
            model->setItem(row, column, new QStandardItem(item.toMap()[field.toString()].toString()));
            column++;
        }
        row++;
    }

    int section = 0;
    for(QVariant &field : sale.getSummaryFields()){

        model->setHeaderData(section, Qt::Horizontal, field.toString().left(1).toUpper() + field.toString().mid(1));
        section++;

    }
    return model;
}
