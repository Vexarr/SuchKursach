#include "addproduct.h"
#include "ui_addproduct.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>

AddProduct::AddProduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddProduct)
{
    ui->setupUi(this);
}

AddProduct::~AddProduct()
{
    delete ui;
}

void AddProduct::on_buttonBox_accepted()
{
    QSqlDatabase::database().transaction();
    QString product_name, articul, description;
    int count;
    float price;

    product_name = ui->ProductName->text();
    articul = ui->Articul->text();
    description = ui->Description->toPlainText();
    price = ui->BoxPrice->value();
    count = ui->Count->text().toInt();

    QSqlQuery qry;
    qry.prepare("INSERT INTO Товары(Наименование, Артикул, Цена, Описание, Наличие_на_складе) VALUES(?, ?, ?, ?, ?)");
    qry.addBindValue(product_name);
    qry.addBindValue(articul);
    qry.addBindValue(price);
    qry.addBindValue(description);
    qry.addBindValue(count);

    if(qry.exec()){
        QSqlDatabase::database().commit();
        accept();
    }
    else
    {
        QMessageBox::critical(this,tr("Ошибка добавления записи"), tr("Запись не была добавлена"));
    }

}

void AddProduct::on_buttonBox_rejected()
{
    reject();
}
