#include "httprequest.h"

#include <QDebug>
#include <QUrlQuery>
#include <QEventLoop>
#include <QJsonObject>
#include <QJsonDocument>

HttpRequest::HttpRequest(QObject* parent) :
    QObject(parent)
{
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

}

QString HttpRequest::s_token;

void HttpRequest::setUseSsl(bool ssl){
    this->useSsl = ssl;
}

void HttpRequest::login(QString email, QString password){
    this->email = email;

    QUrl signInUrl;

    if(useSsl){
        signInUrl.setUrl(QString("https://%1:%2/api/users/signin").arg(hostname.toString()).arg(port));
    }else{
        signInUrl.setUrl(QString("http://%1:%2/api/users/signin").arg(hostname.toString()).arg(port));
    }

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

    qDebug()<<credentialsJson;
}

void HttpRequest::replyFinished(QNetworkReply* reply){
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    qDebug()<<reply->readAll();

    if(statusCode != 201){
        qDebug()<< tr("Could not connect to server. HTTP Status code: ") + QString::number(statusCode);
        emit loginFailed(statusCode);
    }else{

        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        QString token = jsonDoc.toVariant().toJsonObject()["token"].toString();

        HttpRequest::s_token = token;
        qDebug()<<token;
        emit loggedIn();
        reply->deleteLater();
    }
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
