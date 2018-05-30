#include "editproduct.h"
#include "ui_editproduct.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

EditProduct::EditProduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditProduct)
{
    ui->setupUi(this);
}

EditProduct::~EditProduct()
{
    delete ui;
}

void EditProduct::on_buttonBox_accepted()
{
    QSqlDatabase::database().transaction();
    QString product_name, articul, description;
    int count;
    float price;

    product_name = ui->EditProductName->text();
    articul = ui->EditArticul->text();
    description = ui->EditDescription->toPlainText();
    price = ui->EditBoxPrice->value();
    count = ui->EditCount->text().toInt();

    QSqlQuery qry;
    qry.prepare("UPDATE Товары SET Наименование=?, Артикул=?, Цена=?, Описание=?, Наличие_на_складе=? WHERE idТовара=?");
    qry.addBindValue(product_name);
    qry.addBindValue(articul);
    qry.addBindValue(price);
    qry.addBindValue(description);
    qry.addBindValue(count);
    qry.addBindValue(product_id);

    if(qry.exec()){
        QSqlDatabase::database().commit();
        accept();
    }
    else
    {
        QMessageBox::critical(this,tr("Ошибка редактирования записи"), tr("Запись не была отредактирована"));
    }
}

void EditProduct::setDataProduct(const int &row_num_product)
{
    QString product_name, articul, description;
    int count;
    float price;

    if (row_num_product >=0 ){
        QSqlQuery qry;
        qry.prepare("SELECT idТовара, Наименование, Артикул, Цена, Описание, Наличие_на_складе FROM Товары LIMIT ?, 1");
        qry.addBindValue(row_num_product);
        if(qry.exec()){
            qry.next();
            product_id = qry.value(0).toInt();
            product_name = qry.value(1).toString();
            articul = qry.value(2).toString();
            price = qry.value(3).toFloat();
            description = qry.value(4).toString();
            count = qry.value(5).toInt();
        }

        ui->EditProductName->setText(product_name);
        ui->EditArticul->setText(articul);
        ui->EditBoxPrice->setValue(price);
        ui->EditDescription->setPlainText(description);
        ui->EditCount->setValue(count);
    }
}


void EditProduct::on_buttonBox_rejected()
{
    reject();
}
