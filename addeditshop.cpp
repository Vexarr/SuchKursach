#include "addeditshop.h"
#include "ui_addeditshop.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

AddEditShop::AddEditShop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditShop)
{
    ui->setupUi(this);
}

AddEditShop::~AddEditShop()
{
    delete ui;
}

// Добавление записи
void AddEditShop::on_buttonBox_accepted()
{
    QSqlDatabase::database().transaction();
    QString Name, Address, Number;

    Name = ui->lineEditShopName->text();
    Address = ui->lineEditShopAddress->text();
    Number = ui->lineEditShopNumber->text();

    QSqlQuery qry;
    qry.prepare("INSERT INTO Магазин(Название, Адрес, Телефон) VALUES(?, ?, ?)");
    qry.addBindValue(Name);
    qry.addBindValue(Address);
    qry.addBindValue(Number);

    if(qry.exec()){
        QSqlDatabase::database().commit();
        accept();
    }
    else
    {
        QMessageBox::critical(this,tr("Ошибка добавления записи"), tr("Запись не была добавлена"));
    }
}

void AddEditShop::on_buttonBox_rejected()
{
    reject();
}
