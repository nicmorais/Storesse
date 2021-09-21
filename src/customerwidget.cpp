#include "customerwidget.h"
#include "ui_customerwidget.h"
#include "httprequest.h"
#include "storesseentity.h"

CustomerWidget::CustomerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerWidget)
{
    ui->setupUi(this);

    mode = StoresseWindow::New;

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::Window);
}

CustomerWidget::CustomerWidget(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerWidget)
{
    ui->setupUi(this);

    mode = StoresseWindow::Edit;

    int customerId = id;

    HttpRequest request;

    StoresseCustomer *customer = request.getCustomerData(customerId);

    ui->nameLineEdit->setText(customer->name);
    ui->addressLine1LineEdit->setText(customer->addressLine1);
    ui->addressLine2LineEdit->setText(customer->addressLine2);
    ui->zipCodeLineEdit->setText(customer->zipCode);
    ui->documentLineEdit->setText(customer->document);
    ui->emailLineEdit->setText(customer->email);
    ui->birthdateDateEdit->setDate(customer->birthdate);
}

CustomerWidget::~CustomerWidget()
{
    delete ui;
}
