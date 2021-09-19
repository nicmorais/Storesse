#include "salewidget.h"
#include "ui_salewidget.h"

SaleWidget::SaleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaleWidget)
{
    ui->setupUi(this);
}

SaleWidget::~SaleWidget()
{
    delete ui;
}
