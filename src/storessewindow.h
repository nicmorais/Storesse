#ifndef STORESSEWINDOW_H
#define STORESSEWINDOW_H

#include <QWidget>

class StoresseWindow : public QWidget
{
    Q_OBJECT
public:
    explicit StoresseWindow(QWidget *parent = nullptr);

    enum windowMode{
        New,
        Edit,
    };

signals:

};

#endif // STORESSEWINDOW_H
