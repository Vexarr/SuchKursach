#include "editbuy.h"
#include "ui_editbuy.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

EditBuy::EditBuy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditBuy)
{
    ui->setupUi(this);

    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("SELECT Наименование FROM Товары");
    qry->exec();
    modal->setQuery(*qry);
    ui->EditProductBox->setModel(modal);

    QSqlQueryModel * modal2=new QSqlQueryModel;
    QSqlQuery* qry2=new QSqlQuery();
    qry2->prepare("SELECT ФИО FROM Персонал INNER JOIN Должности ON "
                  "Персонал.idДолжности=Должности.idДолжности WHERE Должность='Продавец'");
    qry2->exec();
    modal2->setQuery(*qry2);
    ui->EditPersonBox->setModel(modal2);

    QSqlQueryModel * modal3=new QSqlQueryModel;
    QSqlQuery* qry3=new QSqlQuery();
    qry3->prepare("SELECT Адрес FROM Магазин");
    qry3->exec();
    modal3->setQuery(*qry3);
    ui->EditShopBox->setModel(modal3);
}

EditBuy::~EditBuy()
{
    delete ui;
}

void EditBuy::setDataBuy(const int &row_num_buy)
{
    QString product_name, Fio, shop, date;
    int count;

    if (row_num_buy >=0 ){
        QSqlQuery qry;
        qry.prepare("SELECT idСтруктура_покупки, Структура_покупки.Количество_товара, Дата_продажи, Наименование, Адрес, ФИО FROM "
                    "Покупки INNER JOIN Магазин ON Покупки.idМагазина=Магазин.idМагазина INNER JOIN Персонал ON "
                    "Покупки.idПерсонала=Персонал.idПерсонала INNER JOIN Структура_покупки ON "
                    "Покупки.idПокупки=Структура_покупки.idПокупки INNER JOIN Товары ON "
                    "Товары.idТовара=Структура_покупки.idТовара LIMIT ?, 1");
        qry.addBindValue(row_num_buy);
        if(qry.exec()){
            qry.next();
            buy_id = qry.value(0).toInt();
            count = qry.value(1).toInt();
            date = qry.value(2).toString();
            product_name= qry.value(3).toString();
            shop = qry.value(4).toString();
            Fio = qry.value(5).toString();
        }

        ui->EditProductBox->setCurrentText(product_name);
        ui->EditCount->setValue(count);
        ui->EditDate->setText(date);
        ui->EditShopBox->setCurrentText(shop);
        ui->EditPersonBox->setCurrentText(Fio);
    }
}

void EditBuy::on_buttonBox_accepted()
{
    QSqlDatabase::database().transaction();
    QString Product, Address, Person, Date;
    int ch, ishop, iperson, iproduct, pokup_id;

    Product = ui->EditProductBox->currentText();
    Address = ui->EditShopBox->currentText();
    Person = ui->EditPersonBox->currentText();
    ch = ui->EditCount->value();
    Date = ui->EditDate->text();

    QSqlQuery qry;
    qry.prepare("SELECT idМагазина FROM Магазин WHERE Адрес=?");
    qry.addBindValue(Address);
    if(qry.exec())
    {
        qry.next();
        ishop = qry.value(0).toInt();
    }

    qry.prepare("SELECT idПерсонала FROM Персонал WHERE ФИО=?");
    qry.addBindValue(Person);
    if(qry.exec())
    {
        qry.next();
        iperson = qry.value(0).toInt();
    }

    qry.prepare("SELECT idТовара FROM Товары WHERE Наименование=?");
    qry.addBindValue(Product);
    if(qry.exec())
    {
        qry.next();
        iproduct = qry.value(0).toInt();
    }

    qry.prepare("SELECT idПокупки FROM Структура_покупки WHERE idСтруктура_покупки=?");
    qry.addBindValue(buy_id);
    if(qry.exec())
    {
        qry.next();
        pokup_id = qry.value(0).toInt();
    }

    qry.prepare("UPDATE Структура_покупки SET idТовара=?, Количество_товара=? WHERE idСтруктура_покупки=?");
    qry.addBindValue(iproduct);
    qry.addBindValue(ch);
    qry.addBindValue(buy_id);
    if(!qry.exec())
        {
            qDebug() << iproduct << ch << buy_id;
            QMessageBox::critical(this,tr("Ошибка редактирования записи"), tr("Запись не была отредактирована"));
        }

    qry.prepare("UPDATE Покупки SET idМагазина=?, idПерсонала=?, Дата_продажи=? WHERE idПокупки=?");
    qry.addBindValue(ishop);
    qry.addBindValue(iperson);
    qry.addBindValue(Date);
    qry.addBindValue(pokup_id);
    if(!qry.exec()){
            qDebug() << ishop << iperson << Date << pokup_id;
            QMessageBox::critical(this,tr("Ошибка редактирования записи"), tr("Запись не была отредактирована"));
    }
    else{
        QSqlDatabase::database().commit();
        accept();
    }
}

void EditBuy::on_buttonBox_rejected()
{
    reject();
}
