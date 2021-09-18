#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QtNetwork>
#include <QMessageBox>
#include "mainwindow.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    ui->emailLineEdit->setText(settings.value("user/email").toString());
    ui->hostnameLineEdit->setText(settings.value("server/hostname").toString());
    ui->portSpinBox->setValue(settings.value("server/port", "4000").toInt());
    ui->sslCheckBox->setChecked(settings.value("server/ssl").toBool());
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::connect(){

    QObject::connect(request, SIGNAL(loggedIn()), this, SLOT(showMainWindow()));
    QObject::connect(request, SIGNAL(loggedIn()), this, SLOT(saveSettings()));
    QObject::connect(request, SIGNAL(loginFailed(int)), this, SLOT(loginFailed(int)));

    request->setHostname(ui->hostnameLineEdit->text());
    request->setPort(ui->portSpinBox->value());
    request->login(ui->emailLineEdit->text(), ui->passwordLineEdit->text());

}

void LoginWidget::loginFailed(int statusCode){
    QMessageBox errorMessage(this);
    errorMessage.setWindowTitle(tr("Login Failed"));
    errorMessage.setText(tr("Could not connect to server. Http Status Code: ") + QString::number(statusCode));
    errorMessage.exec();
}

void LoginWidget::saveSettings(){
    settings.setValue("user/email", ui->emailLineEdit->text());
    settings.setValue("server/hostname", ui->hostnameLineEdit->text());
    settings.setValue("server/port", ui->portSpinBox->value());
    settings.setValue("server/ssl", ui->sslCheckBox->isChecked());
}

void LoginWidget::showMainWindow(){
    MainWindow *mainWindow = new MainWindow;
    mainWindow->move(geometry().topLeft());

    mainWindow->show();
    close();
}
