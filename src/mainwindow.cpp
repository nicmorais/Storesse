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
    QStandardItemModel *model;
    model = request.getModel(StoresseEntity::Customer);

    switch (currentTab) {
    case 0:{

//        model->setHeaderData(0, Qt::Horizontal, "ID");
//        model->setHeaderData(1, Qt::Horizontal, tr("Name"));
//        model->setHeaderData(2, Qt::Horizontal, "E-mail");

//       ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

        break;
    }
    case 1:{
        model = request.getModel(StoresseEntity::Product);
        break;
    }
    case 2:{
        break;
    }
    }
    ui->tableView->setModel(model);
}

void MainWindow::newSale(){

}

void MainWindow::editItem(QModelIndex index){

}
