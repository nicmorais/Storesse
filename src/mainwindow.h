#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setUpTable();

    void editItem(QModelIndex index);
private:
    Ui::MainWindow *ui;

    QRect getSubWindowRect(float width, float height);

    QStandardItemModel *tableModel;

private slots:
    void newSale();

    void newCustomer();
};
#endif // MAINWINDOW_H
