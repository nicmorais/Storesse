#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "httprequest.h"
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<HttpRequest::s_token;
}

MainWindow::~MainWindow()
{
    delete ui;
}

