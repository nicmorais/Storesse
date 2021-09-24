#ifndef CUSTOMERWIDGET_H
#define CUSTOMERWIDGET_H

#include <QWidget>
#include "storessewindow.h"
#include "httprequest.h"

namespace Ui {
class CustomerWidget;
}

class CustomerWidget : public QWidget
{
    Q_OBJECT

public:
    CustomerWidget(QWidget *parent = nullptr);

    CustomerWidget(int id, QWidget *parent = nullptr);

    ~CustomerWidget();

private:
    Ui::CustomerWidget *ui;

    StoresseWindow::windowMode mode;

    int costumerId;

    int countryId;

    HttpRequest request;

    StoresseCustomer *customer;

private slots:
    void setUpCountriesModel();

    void setUpStatesModel();

    void setUpStatesModel(QString cityName, QString stateName);

    void setUpCitiesModel();

    void setUpCitiesModel(QString cityName);

    void save();
};

#endif // CUSTOMERWIDGET_H
