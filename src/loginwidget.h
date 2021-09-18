#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QtNetwork/QNetworkReply>
#include <QSettings>
#include "httprequest.h"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private:
    Ui::LoginWidget *ui;

    QSettings settings;

    HttpRequest *request = new HttpRequest(this);


private slots:
    void connect();

    void showMainWindow();

    void saveSettings();

    void loginFailed(int statusCode);
};

#endif // LOGINWIDGET_H
