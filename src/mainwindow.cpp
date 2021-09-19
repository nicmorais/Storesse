#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "httprequest.h"
#include <QToolBar>
#include "storessecustomer.h"
#include <QModelIndex>
#include <QHeaderView>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setUpTable();
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
//        request.getCostumers(ui->tableWidget);
//        QHeaderView* header = ui->tableWidget->horizontalHeader();
//        header->setSectionResizeMode(QHeaderView::Stretch);
//        ui->tableWidget->setHorizontalHeader(header);

        QStandardItemModel *customersModel = request.getCostumersModel();
        customersModel->setHeaderData(0, Qt::Horizontal, "ID");
        customersModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
        customersModel->setHeaderData(2, Qt::Horizontal, "E-mail");

        ui->tableView->setModel(customersModel);
        ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        break;
    }
    case 1:{
        break;
    }
    case 2:{
        break;
    }
    }
}

void MainWindow::newSale(){

}

void MainWindow::editItem(QModelIndex index){

}
