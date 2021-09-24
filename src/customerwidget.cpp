#include "customerwidget.h"
#include "ui_customerwidget.h"
#include "storesseentity.h"

CustomerWidget::CustomerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerWidget)
{
    ui->setupUi(this);

    mode = StoresseWindow::New;

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::Window);

    setUpCountriesModel();
    setUpCitiesModel();
    setUpStatesModel();
}

CustomerWidget::CustomerWidget(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerWidget)
{
    ui->setupUi(this);

    mode = StoresseWindow::Edit;

    int customerId = id;

    customer = request.getCustomerData(customerId);
    ui->nameLineEdit->setText(customer->name);
    ui->addressLine1LineEdit->setText(customer->addressLine1);
    ui->addressLine2LineEdit->setText(customer->addressLine2);
    ui->zipCodeLineEdit->setText(customer->zipCode);
    ui->documentLineEdit->setText(customer->document);
    ui->emailLineEdit->setText(customer->email);
    ui->birthdateDateEdit->setDate(customer->birthdate);

    setUpCountriesModel();

}

CustomerWidget::~CustomerWidget()
{
    delete ui;
}

void CustomerWidget::setUpCountriesModel(){
    QStandardItemModel *countriesModel;
    countriesModel = request.getCountriesModel();
    countriesModel->setParent(ui->countryComboBox);

    ui->countryComboBox->setModel(countriesModel);

    if(mode == StoresseWindow::Edit){
        StoresseCity *customerCity;
        customerCity = request.getCityData(customer->cityId);

        StoresseState *customerState;
        customerState = request.getStateData(customerCity->stateId);

        StoresseCountry *customerCountry;
        customerCountry = request.getCountryData(customerState->countryId);

        QList<QStandardItem*> modelItem = countriesModel->findItems(customerCountry->name);

        modelItem = countriesModel->findItems(customerCountry->name);

        ui->countryComboBox->setCurrentIndex(modelItem[0]->row());

        modelItem = countriesModel->findItems(customerCountry->name);

        setUpStatesModel(customerCity->name, customerState->name);
    }
}

void CustomerWidget::setUpStatesModel(QString cityName, QString stateName){
    QStandardItemModel *statesModel = (QStandardItemModel*) ui->stateComboBox->model();

    QList<QStandardItem*> modelItem = statesModel->findItems(stateName);

    ui->stateComboBox->setCurrentIndex(modelItem[0]->row());

    setUpCitiesModel(cityName);
}

void CustomerWidget::setUpStatesModel(){
    QStandardItemModel * statesModel;
    statesModel = request.getStatesModel(ui->countryComboBox->model()->index(ui->countryComboBox->currentIndex(), 1).data(2).toInt());
    ui->stateComboBox->setModel(statesModel);
    ui->stateComboBox->setEnabled(true);
}

void CustomerWidget::setUpCitiesModel(QString cityName){
    QStandardItemModel *citiesModel = (QStandardItemModel*) ui->cityComboBox->model();
    QList<QStandardItem*> modelItem = citiesModel->findItems(cityName);
    ui->cityComboBox->setModel(citiesModel);
    ui->cityComboBox->setCurrentIndex(modelItem[0]->row());
}

void CustomerWidget::setUpCitiesModel(){
    QStandardItemModel * citiesModel;
    int countryId = ui->countryComboBox->model()->index(ui->countryComboBox->currentIndex(), 1).data(2).toInt();
    int stateId = ui->stateComboBox->model()->index(ui->stateComboBox->currentIndex(), 1).data(2).toInt();

    citiesModel = request.getCitiesModel(countryId, stateId);
    ui->cityComboBox->setModel(citiesModel);
    ui->cityComboBox->setEnabled(true);
}

void CustomerWidget::save(){
    StoresseCustomer *customer = new StoresseCustomer(this);

    customer->name = ui->nameLineEdit->text();
    customer->email = ui->emailLineEdit->text();
    customer->addressLine1 = ui->addressLine1LineEdit->text();
    customer->addressLine2 = ui->addressLine2LineEdit->text();
    customer->cityId = ui->cityComboBox->model()->index(ui->cityComboBox->currentIndex(), 1).data(2).toInt();
    customer->zipCode = ui->zipCodeLineEdit->text();
    customer->birthdate = ui->birthdateDateEdit->date();
    customer->document = ui->documentLineEdit->text();
    request.updateCustomer(customer);

    close();
}
