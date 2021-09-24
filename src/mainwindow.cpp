#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "httprequest.h"
#include <QToolBar>
#include "storessecustomer.h"
#include <QModelIndex>
#include <QHeaderView>
#include "noteditableitemdelegate.h"
#include "customerwidget.h"
#include "salewidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->salesDateEdit->setDate(QDate::currentDate());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpTable(){
    int currentTab = ui->tabWidget->currentIndex();

    HttpRequest request;
    switch (currentTab) {
    case 0:{
        tableModel = request.getCustomersModel(ui->searchCustomersLineEdit->text());
        break;
    }
    case 1:{
        tableModel = request.getProductsModel(ui->searchProductsLineEdit->text());
        break;
    }
    case 2:{
        if(ui->salesAnyDateCheckBox->isChecked()){
            tableModel = request.getSalesModel(ui->searchSalesLineEdit->text());
        }else{
            tableModel = request.getSalesModel(ui->searchSalesLineEdit->text(), ui->salesDateEdit->date());
        }

        break;
    }
    }

    ui->tableView->setModel(tableModel);

    if(tableModel->rowCount() > 0){
        ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    }

    for (int i=0; i<tableModel->columnCount(); i++ ) {
        NotEditableItemDelegate *itemDelegate = new NotEditableItemDelegate(ui->tableView);
        ui->tableView->setItemDelegateForColumn(i, itemDelegate);
    }

}

void MainWindow::newSale(){
    SaleWidget *saleWidget = new SaleWidget;
    saleWidget->setGeometry(getSubWindowRect(0.9, 0.9));
    saleWidget->show();
}

void MainWindow::newCustomer(){
    CustomerWidget *customerWidget = new CustomerWidget;
    customerWidget->setGeometry(getSubWindowRect(0.5, 0.9));
    customerWidget->show();
}

void MainWindow::editItem(QModelIndex index){
    int currentTab = ui->tabWidget->currentIndex();

    switch (currentTab) {
    case 0:{
        CustomerWidget *customerWidget = new CustomerWidget(index.siblingAtColumn(0).data(Qt::EditRole).toInt());
        customerWidget->setGeometry(getSubWindowRect(0.5, 0.9));
        customerWidget->show();
    }
    case 1:{

    }
    case 2:{

    }
    }
}

QRect MainWindow::getSubWindowRect(float width, float height){
    QRect rect = geometry();
    rect.setWidth(geometry().width() * width);
    rect.setHeight(geometry().height() * height);
    rect.moveCenter(geometry().center());

    return rect;
}
