#include "editshop.h"
#include "ui_editshop.h"
#include "shopinfo.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>

EditShop::EditShop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditShop)
{
    ui->setupUi(this);
}

EditShop::~EditShop()
{
    delete ui;
}

void EditShop::on_buttonBox_accepted()
{
    QSqlDatabase::database().transaction();
    QString Name, Address, Number;

    Name = ui->EditShopName->text();
    Address = ui->EditShopAddress->text();
    Number = ui->EditShopNumber->text();

    QSqlQuery qry;
    qry.prepare("UPDATE Магазин SET Название=?, Адрес=?, Телефон=? WHERE idМагазина=?");
    qry.addBindValue(Name);
    qry.addBindValue(Address);
    qry.addBindValue(Number);
    qry.addBindValue(shop_id);

    if(qry.exec()){
        QSqlDatabase::database().commit();
        accept();
    }
    else
    {
        QMessageBox::critical(this,tr("Ошибка редактирования записи"), tr("Запись не была отредактирована"));
    }

}

void EditShop::setData(const int &row_num){

    QString shop_name, address, number;

    if (row_num >=0){
        QSqlQuery qry;
        qry.prepare("SELECT * FROM Магазин LIMIT ?, 1");
        qry.addBindValue(row_num);
        if(qry.exec()){
            qry.next();
            shop_id = qry.value(0).toInt();
            shop_name = qry.value(1).toString();
            address = qry.value(2).toString();
            number = qry.value(3).toString();
        }
        ui->EditShopName->setText(shop_name);
        ui->EditShopAddress->setText(address);
        ui->EditShopNumber->setText(number);
    }
}

void EditShop::on_buttonBox_rejected()
{
    reject();
}
