#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "httprequest.h"
#include <QToolBar>
#include "storessecustomer.h"
#include "storessetablemodel.h"
#include <QModelIndex>
#include <QHeaderView>

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
    ui->tableWidget->clear();

    HttpRequest request;
    switch (currentTab) {
    case 0:{
        request.getCostumers(ui->tableWidget);
        QHeaderView* header = ui->tableWidget->horizontalHeader();
        header->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->setHorizontalHeader(header);
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
