#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "storesseentity.h"
#include "storessecustomer.h"
#include <QTableWidget>
#include <QStandardItemModel>

class HttpRequest : public QObject
{
    Q_OBJECT

public:
    HttpRequest(QObject* parent = nullptr);

    static QString s_token;

    static QNetworkRequest s_requestWithToken;

    static QUrl s_baseUrl;

    void setUseSsl(bool ssl = true);

    QString getEmail();

    void login(QString email, QString password);

    void setHostname(QString hostname);

    QString getHostname();

    void setPort(int port);

    int getPort();

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);

    void getEntityData(StoresseEntity::Entity entity, int id);

    StoresseCustomer *getCostumerData(int id);

    QStandardItemModel *getCostumersModel();

private slots:
    void loginReplyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager accessManager;

    bool useSsl;

    QString email;

    QUrl hostname;

    int port;

signals:
    void loggedIn();

    void loginFailed(int errorCode);
};

#endif // HTTPREQUEST_H
