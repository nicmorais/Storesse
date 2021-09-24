#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "storesseentity.h"
#include <QTableWidget>
#include <QStandardItemModel>
#include "storessecustomer.h"
#include "storessecountry.h"
#include "storessestate.h"
#include "storessecity.h"

class HttpRequest : public QObject
{
    Q_OBJECT

public:
    HttpRequest(QObject* parent = nullptr);

    static QString s_token;

    static QNetworkRequest s_requestWithToken;

    static QUrl s_baseUrl;

    static int port;

    void setUseSsl(bool useSsl = true);

    QString getEmail();

    void login(QString email, QString password);

    void setHostname(QString hostname);

    QString getHostname();

    void setPort(int port);

    int getPort();

    QNetworkAccessManager *networkManager = new QNetworkAccessManager;

    StoresseCustomer *getCustomerData(int id);

    StoresseCountry *getCountryData(int id);

    StoresseState *getStateData(int id);

    StoresseCity *getCityData(int countryId, int stateId, int id);

    StoresseCity *getCityData(int id);

    void getCityData(StoresseCity *city);

    QStandardItemModel *getModel(StoresseEntity::entity entity);

    QStandardItemModel *getCustomersModel(QString name);

    QStandardItemModel *getProductsModel(QString name);

    QStandardItemModel *getSalesModel(QString name);

    QStandardItemModel *getSalesModel(QString name, QDate date);

    QStandardItemModel *getCountriesModel();

    QStandardItemModel *getStatesModel(int countryId);

    QStandardItemModel *getCitiesModel(int countryId, int stateId);

    void createCustomer(StoresseCustomer customer);

    void updateCustomer(StoresseCustomer *costumer);

private slots:
    void loginReplyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager accessManager;

    bool useSsl;

    QString email;

    QUrl hostname;

signals:
    void loggedIn();

    void loginFailed(int errorCode);
};

#endif // HTTPREQUEST_H
