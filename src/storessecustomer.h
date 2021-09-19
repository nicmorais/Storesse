#ifndef STORESSECUSTOMER_H
#define STORESSECUSTOMER_H

#include <QObject>
#include "storesseentity.h"
#include <QDate>
#include "storessecity.h"

class StoresseCustomer : public QObject
{
    Q_OBJECT
public:
    explicit StoresseCustomer(QObject *parent = nullptr);

    const StoresseEntity::Entity entity = StoresseEntity::Customer;

    void setName(QString name);

    QString getName();

signals:
    void idSet();

private:
    int id;
    QString name;
    QString addressLine1;
    QString addressLine2;
    QString document;
    QString zipCode;
    QDate birthdate;
    QString email;
    StoresseCity city;

public slots:
    void setId(int id);

    void getData();
private slots:

};

#endif // STORESSECUSTOMER_H
