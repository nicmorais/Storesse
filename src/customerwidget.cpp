#include "customerwidget.h"
#include "ui_customerwidget.h"

CustomerWidget::CustomerWidget(QWidget *parent) :
    StoresseWindow(parent),
    ui(new Ui::CustomerWidget)
{
    ui->setupUi(this);

    mode = New;
}

CustomerWidget::CustomerWidget(int id, QWidget *parent) :
    StoresseWindow(parent),
    ui(new Ui::CustomerWidget)
{
    ui->setupUi(this);

    mode = Edit;

    costumerId = id;
}

CustomerWidget::~CustomerWidget()
{
    delete ui;
}
