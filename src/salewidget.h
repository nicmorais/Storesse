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
    ~SaleWidget();

private:
    Ui::SaleWidget *ui;
};

#endif // SALEWIDGET_H
