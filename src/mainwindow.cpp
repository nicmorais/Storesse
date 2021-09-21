#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "httprequest.h"
#include <QToolBar>
#include "storessecustomer.h"
#include <QModelIndex>
#include <QHeaderView>
#include <QStandardItemModel>
#include "noteditableitemdelegate.h"
#include "customerwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpTable(){
    int currentTab = ui->tabWidget->currentIndex();

    HttpRequest request;
    QStandardItemModel *model;

    switch (currentTab) {
    case 0:{
        model = request.getModel(StoresseEntity::Customer);


        break;
    }
    case 1:{
        model = request.getModel(StoresseEntity::Product);
        break;
    }
    case 2:{
        model = request.getModel(StoresseEntity::Sale);

        break;
    }
    }

    ui->tableView->setModel(model);

    if(model->rowCount() > 0){
        ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    }

    for (int i=0; i<model->columnCount(); i++ ) {
        NotEditableItemDelegate *itemDelegate = new NotEditableItemDelegate(ui->tableView);
        ui->tableView->setItemDelegateForColumn(i, itemDelegate);
    }

}

void MainWindow::newSale(){

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
