#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "httprequest.h"
#include <QToolBar>
#include "storessecustomer.h"
#include <QModelIndex>
#include <QHeaderView>
#include <QStandardItemModel>
#include "noteditableitemdelegate.h"

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
    int columnCount;
    switch (currentTab) {
    case 0:{
        model = request.getModel(StoresseEntity::Customer);
        ui->tableView->setModel(model);
        ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        columnCount = 4;
        break;
    }
    case 1:{
        model = request.getModel(StoresseEntity::Product);
        columnCount = 6;

        break;
    }
    case 2:{
        break;
    }
    }

    for (int i=0; i<columnCount; i++ ) {
        NotEditableItemDelegate *itemDelegate = new NotEditableItemDelegate(ui->tableView);
        ui->tableView->setItemDelegateForColumn(i, itemDelegate);
    }

    ui->tableView->setModel(model);
}

void MainWindow::newSale(){

}

void MainWindow::editItem(QModelIndex index){

}
