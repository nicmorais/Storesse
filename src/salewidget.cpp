#include "salewidget.h"
#include "ui_salewidget.h"
#include "httprequest.h"
#include <QStandardItemModel>
#include "noteditableitemdelegate.h"

SaleWidget::SaleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaleWidget)
{
    ui->setupUi(this);
}

SaleWidget::SaleWidget(int saleId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaleWidget)
{
    ui->setupUi(this);
    this->saleId = saleId;


}

SaleWidget::~SaleWidget()
{
    delete ui;
}

void SaleWidget::searchCustomers(){
    HttpRequest request;

    QStandardItemModel *model = request.getCustomersModel(ui->searchCustomersLineEdit->text());

    ui->searchCustomersTableView->setModel(model);

    NotEditableItemDelegate *itemDelegate = new NotEditableItemDelegate;
    itemDelegate->setParent(this);
    for (int i = 0;i<model->columnCount();i++) {
        ui->saleProductsTableView->setItemDelegateForColumn(i, itemDelegate);
    }
}

void SaleWidget::searchProducts(){
    HttpRequest request;

    QStandardItemModel *model = request.getProductsModel(ui->searchProductsLineEdit->text());

    ui->searchProductsTableView->setModel(model);

}
