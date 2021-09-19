#include "customerwidget.h"
#include "ui_customerwidget.h"

CustomerWidget::CustomerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerWidget)
{
    ui->setupUi(this);
}

CustomerWidget::~CustomerWidget()
{
    delete ui;
}
