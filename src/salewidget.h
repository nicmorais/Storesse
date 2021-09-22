#ifndef SALEWIDGET_H
#define SALEWIDGET_H

#include <QWidget>

namespace Ui {
class SaleWidget;
}

class SaleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SaleWidget(QWidget *parent = nullptr);

    SaleWidget(int saleId, QWidget *parent = nullptr);

    ~SaleWidget();

private:
    Ui::SaleWidget *ui;

    int saleId;

private slots:
    void searchProducts();

    void searchCustomers();
};

#endif // SALEWIDGET_H
