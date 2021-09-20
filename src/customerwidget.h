#ifndef CUSTOMERWIDGET_H
#define CUSTOMERWIDGET_H

#include <QWidget>
#include "storessewindow.h"

namespace Ui {
class CustomerWidget;
}

class CustomerWidget : public StoresseWindow
{
    Q_OBJECT

public:
    CustomerWidget(QWidget *parent = nullptr);

    CustomerWidget(int id, QWidget *parent = nullptr);

    ~CustomerWidget();

private:
    Ui::CustomerWidget *ui;

    windowMode mode;

    int costumerId;
};

#endif // CUSTOMERWIDGET_H
