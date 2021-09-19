#include "httprequest.h"

#include <QDebug>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>
#include <QEventLoop>
#include <QJsonArray>

HttpRequest::HttpRequest(QObject* parent) :
    QObject(parent)
{
    s_requestWithToken.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

}

QString HttpRequest::s_token;

QNetworkRequest HttpRequest::s_requestWithToken;

QUrl HttpRequest::s_baseUrl;

void HttpRequest::setUseSsl(bool ssl){
    this->useSsl = ssl;
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

    qDebug()<<signInUrl.toString();

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

void HttpRequest::getEntityData(StoresseEntity::Entity entity, int id){
    switch (entity) {
    case StoresseEntity::Customer:{
        break;
    }
    case StoresseEntity::Product:{
        break;

    }
    case StoresseEntity::Sale:{
        break;

    }
    case StoresseEntity::SaleProduct:{
        break;

    }
    case StoresseEntity::Country:{
        break;

    }
    case StoresseEntity::State:{
        break;

    }
    case StoresseEntity::City:{
        break;

    }
    case StoresseEntity::User:{
        break;
    }
    }
}

StoresseCustomer* HttpRequest::getCostumerData(int id){
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

    return customer;
}

QStandardItemModel* HttpRequest::getCostumersModel(){
    QStandardItemModel *model = new QStandardItemModel;

    QNetworkAccessManager localManager;
    QEventLoop eventLoop;
    QObject::connect(&localManager, &QNetworkAccessManager::finished,
                     &eventLoop, &QEventLoop::quit);

    s_requestWithToken.setUrl(QUrl(QString(s_baseUrl.toString() + "customers")));

    QNetworkReply* reply = localManager.get(s_requestWithToken);
    eventLoop.exec();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());

    int row = 0;
    for (QVariant customer : jsonDoc.toVariant().toMap()["data"].toList()){
        model->insertRow(row);

        model->setItem(row, 0, new QStandardItem(customer.toMap()["id"].toString()));
        model->setItem(row, 1, new QStandardItem(customer.toMap()["name"].toString()));
        model->setItem(row, 2, new QStandardItem(customer.toMap()["email"].toString()));

        row++;
    }

    return model;
}
