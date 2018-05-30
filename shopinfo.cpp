#include "shopinfo.h"
#include "ui_shopinfo.h"
#include "global.h"
#include "addeditshop.h"
#include "addbuy.h"
#include "addpersonal.h"
#include "addproduct.h"
#include "editbuy.h"
#include "editpersonal.h"
#include "editproduct.h"
#include "editshop.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

ShopInfo::ShopInfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopInfo)
{
    ui->setupUi(this);

    ::sCurrentDatabaseType = "MySQL";
    if(!connectDatabase()){
        QMessageBox::critical(this,tr("Database"), tr("Failed to connect database!"));
        ui->mainToolBar->setEnabled(false);
        ui->centralWidget->setEnabled(false);
    }
    else{
        on_actionShop_triggered();
    }
}

ShopInfo::~ShopInfo()
{
    delete ui;
}

// Триггеры на действия - Done
void ShopInfo::on_actionShop_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("SELECT Название, Адрес, Телефон FROM Магазин");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableViewShop->setModel(modal);
}

void ShopInfo::on_actionProducts_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("SELECT Наименование, Артикул, Цена, Описание, Наличие_на_складе FROM Товары");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableViewProduct->setModel(modal);
}

void ShopInfo::on_actionPersons_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("SELECT ФИО, Должность, Пол FROM "
                 "((Персонал INNER JOIN Должности ON "
                 "Персонал.idДолжности=Должности.idДолжности) "
                 "INNER JOIN Пол ON Персонал.idПол=Пол.idПола)");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableViewPerson->setModel(modal);

}

void ShopInfo::on_actionBuy_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("SELECT Покупки.idПокупки, Структура_покупки.Количество_товара, Дата_продажи, Наименование, Название, Адрес, ФИО FROM "
                 "Покупки INNER JOIN Магазин ON Покупки.idМагазина=Магазин.idМагазина INNER JOIN Персонал ON "
                 "Покупки.idПерсонала=Персонал.idПерсонала INNER JOIN Структура_покупки ON "
                 "Покупки.idПокупки=Структура_покупки.idПокупки INNER JOIN Товары ON "
                 "Товары.idТовара=Структура_покупки.idТовара");
    if(qry->exec()){
        modal->setQuery(*qry);
        ui->tableViewBuy->setModel(modal);
    }
    else
        QMessageBox::critical(this,tr("Ошибка"), tr("Неудачно выполнился запрос"));
}


// Страница Магазин - Done
void ShopInfo::on_AddShop_clicked()
{
    AddEditShop * dlg = new AddEditShop(this);
    dlg->exec();

    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery qry;
    qry.prepare("SELECT Название, Адрес, Телефон FROM Магазин");
    qry.exec();
    modal->setQuery(qry);
    ui->tableViewShop->setModel(modal);

    delete dlg;
}

void ShopInfo::on_EditShop_clicked()
{
    QItemSelectionModel *select = ui->tableViewShop->selectionModel();
    int row_num;
    QModelIndex i = select->currentIndex();
    row_num = i.row();

    if(row_num>=0){
        EditShop * dlg = new EditShop(this);
        dlg->setData(row_num);
        dlg->exec();
        delete dlg;
    }

    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery qry;
    qry.prepare("SELECT Название, Адрес, Телефон FROM Магазин");
    qry.exec();
    modal->setQuery(qry);
    ui->tableViewShop->setModel(modal);

    row_num = -1;
}

void ShopInfo::on_RemoveShop_clicked()
{
    QSqlQueryModel * modal=new QSqlQueryModel;
    QItemSelectionModel *select = ui->tableViewShop->selectionModel();

    int  shop_id;
    QModelIndex i = select->currentIndex();
    int row_number = i.row();

    if (row_number >=0){
        QSqlQuery qry;
        qry.prepare("SELECT idМагазина FROM Магазин LIMIT ?, 1");
        qry.addBindValue(row_number);
        if(qry.exec()){
            qry.next();
            shop_id = qry.value(0).toInt();
        }

        qry.prepare("DELETE FROM Магазин WHERE idМагазина=?");
        qry.addBindValue(shop_id);
        if(qry.exec()){
            qry.prepare("SELECT Название, Адрес, Телефон FROM Магазин");
            qry.exec();
            modal->setQuery(qry);
            ui->tableViewShop->setModel(modal);
        }
        else
        {
            QMessageBox::critical(this,tr("Ошибка удаления записи"), tr("Запись не была удалена"));
        }
    }
}

void ShopInfo::on_UpdateShop_clicked()
{
    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("SELECT Название, Адрес, Телефон FROM Магазин");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableViewShop->setModel(modal);
}


// Страница Товаров - Done
void ShopInfo::on_AddProduct_clicked()
{
    AddProduct * dlg = new AddProduct(this);
    dlg->exec();

    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("SELECT Наименование, Артикул, Цена, Описание, Наличие_на_складе FROM Товары");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableViewProduct->setModel(modal);

    delete dlg;
}

void ShopInfo::on_EditProduct_clicked()
{
    QItemSelectionModel *select = ui->tableViewProduct->selectionModel();
    int row_num;
    QModelIndex i = select->currentIndex();
    row_num = i.row();

    if(row_num>=0){
        EditProduct * dlg = new EditProduct(this);
        dlg->setDataProduct(row_num);
        dlg->exec();
        delete dlg;
    }

    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery qry;
    qry.prepare("SELECT Наименование, Артикул, Цена, Описание, Наличие_на_складе FROM Товары");
    qry.exec();
    modal->setQuery(qry);
    ui->tableViewProduct->setModel(modal);

    row_num = -1;
}

void ShopInfo::on_RemoveProduct_clicked()
{
    QSqlQueryModel * modal=new QSqlQueryModel;
    QItemSelectionModel *select = ui->tableViewProduct->selectionModel();

    int product_id;
    QModelIndex i = select->currentIndex();
    int row_number = i.row();

    if (row_number >=0){
        QSqlQuery qry;
        qry.prepare("SELECT idТовара FROM Товары LIMIT ?, 1");
        qry.addBindValue(row_number);
        if(qry.exec()){
            qry.next();
            product_id = qry.value(0).toInt();
        }

        qry.prepare("DELETE FROM Товары WHERE idТовара=?");
        qry.addBindValue(product_id);
        if(qry.exec()){
            qry.prepare("SELECT Наименование, Артикул, Цена, Описание, Наличие_на_складе FROM Товары");
            qry.exec();
            modal->setQuery(qry);
            ui->tableViewProduct->setModel(modal);
        }
        else
        {
            QMessageBox::critical(this,tr("Ошибка удаления записи"), tr("Запись не была удалена"));
        }
    }
}

void ShopInfo::on_UpdateProduct_clicked()
{
    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("SELECT Наименование, Артикул, Цена, Описание, Наличие_на_складе FROM Товары");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableViewProduct->setModel(modal);
}


// Страница Персонала - Done
void ShopInfo::on_AddPerson_clicked()
{
    AddPersonal * dlg = new AddPersonal(this);
    dlg->exec();

    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("SELECT ФИО, Должность, Пол FROM Персонал INNER JOIN Должности ON "
                 "Персонал.idДолжности=Должности.idДолжности INNER JOIN Пол ON "
                 "Персонал.idПол=Пол.idПола");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableViewPerson->setModel(modal);
}

void ShopInfo::on_EditPerson_clicked()
{
    QItemSelectionModel *select = ui->tableViewPerson->selectionModel();
    int row_num_person;
    QModelIndex i = select->currentIndex();
    row_num_person = i.row();

    if(row_num_person >=0 ){
        EditPersonal * dlg = new EditPersonal(this);
        dlg->setDataPerson(row_num_person);
        dlg->exec();
        delete dlg;
    }

    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery qry;
    qry.prepare("SELECT ФИО, Должность, Пол FROM ((Персонал INNER JOIN Должности ON "
                "Персонал.idДолжности=Должности.idДолжности) INNER JOIN Пол ON "
                "Персонал.idПол=Пол.idПола)");
    qry.exec();
    modal->setQuery(qry);
    ui->tableViewPerson->setModel(modal);

    row_num_person = -1;
}

void ShopInfo::on_RemovePerson_clicked()
{
    QSqlQueryModel * modal=new QSqlQueryModel;
    QItemSelectionModel *select = ui->tableViewPerson->selectionModel();

    int  person_id;
    QModelIndex indexx = select->currentIndex();
    int row_number_person = indexx.row();

    if (row_number_person >= 0){
        QSqlQuery qry;
        qry.prepare("SELECT idПерсонала FROM Персонал LIMIT ?, 1");
        qry.addBindValue(row_number_person);
        if(qry.exec()){
            qry.next();
            person_id = qry.value(0).toInt();
        }

        qry.prepare("DELETE FROM Персонал WHERE idПерсонала=?");
        qry.addBindValue(person_id);
        if(qry.exec()){
            qry.prepare("SELECT ФИО, Должность, Пол FROM ((Персонал INNER JOIN Должности ON "
                        "Персонал.idДолжности=Должности.idДолжности) INNER JOIN Пол ON "
                        "Персонал.idПол=Пол.idПола)");
            qry.exec();
            modal->setQuery(qry);
            ui->tableViewPerson->setModel(modal);
        }
        else
        {
            QMessageBox::critical(this,tr("Ошибка удаления записи"), tr("Запись не была удалена"));
        }
    }
}

void ShopInfo::on_UpdatePerson_clicked()
{
    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("SELECT ФИО, Должность, Пол FROM "
                 "((Персонал INNER JOIN Должности ON "
                 "Персонал.idДолжности=Должности.idДолжности) "
                 "INNER JOIN Пол ON Персонал.idПол=Пол.idПола)");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableViewPerson->setModel(modal);
}


// Страница Корзины
void ShopInfo::on_AddBuy_clicked()
{
    AddBuy * dlg = new AddBuy(this);
    dlg->exec();

    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("SELECT Покупки.idПокупки, Структура_покупки.Количество_товара, Дата_продажи, Наименование, Название, Адрес, ФИО FROM "
                 "Покупки INNER JOIN Магазин ON Покупки.idМагазина=Магазин.idМагазина INNER JOIN Персонал ON "
                 "Покупки.idПерсонала=Персонал.idПерсонала INNER JOIN Структура_покупки ON "
                 "Покупки.idПокупки=Структура_покупки.idПокупки INNER JOIN Товары ON "
                 "Товары.idТовара=Структура_покупки.idТовара");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableViewBuy->setModel(modal);
}

void ShopInfo::on_EditBuy_clicked()
{
    QItemSelectionModel *select = ui->tableViewBuy->selectionModel();
    int row_num_buy;
    QModelIndex i = select->currentIndex();
    row_num_buy = i.row();

    if(row_num_buy >=0 ){
        EditBuy * dlg = new EditBuy(this);
        dlg->setDataBuy(row_num_buy);
        dlg->exec();
        delete dlg;
    }

    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery qry;
    qry.prepare("SELECT Покупки.idПокупки, Структура_покупки.Количество_товара, Дата_продажи, Наименование, Название, Адрес, ФИО FROM "
                "Покупки INNER JOIN Магазин ON Покупки.idМагазина=Магазин.idМагазина INNER JOIN Персонал ON "
                "Покупки.idПерсонала=Персонал.idПерсонала INNER JOIN Структура_покупки ON "
                "Покупки.idПокупки=Структура_покупки.idПокупки INNER JOIN Товары ON "
                "Товары.idТовара=Структура_покупки.idТовара");
    qry.exec();
    modal->setQuery(qry);
    ui->tableViewBuy->setModel(modal);

    row_num_buy = -1;
}

void ShopInfo::on_RemoveBuy_clicked()
{
    QSqlQueryModel * modal=new QSqlQueryModel;
    QItemSelectionModel *select = ui->tableViewBuy->selectionModel();

    int  struct_id;
    QModelIndex indexx = select->currentIndex();
    int row_number_buy = indexx.row();

    if (row_number_buy >= 0){
        QSqlQuery qry;
        qry.prepare("SELECT idСтруктура_покупки FROM Структура_покупки LIMIT ?, 1");
        qry.addBindValue(row_number_buy);
        if(qry.exec()){
            qry.next();
            struct_id = qry.value(0).toInt();
        }

        qry.prepare("DELETE FROM Структура_покупки WHERE idСтруктура_покупки=?");
        qry.addBindValue(struct_id);
        if(qry.exec()){
            qry.prepare("SELECT Покупки.idПокупки, Структура_покупки.Количество_товара, Дата_продажи, Наименование, Адрес, Название, ФИО FROM "
                        "Покупки INNER JOIN Магазин ON Покупки.idМагазина=Магазин.idМагазина INNER JOIN Персонал ON "
                        "Покупки.idПерсонала=Персонал.idПерсонала INNER JOIN Структура_покупки ON "
                        "Покупки.idПокупки=Структура_покупки.idПокупки INNER JOIN Товары ON "
                        "Товары.idТовара=Структура_покупки.idТовара");
            qry.exec();
            modal->setQuery(qry);
            ui->tableViewBuy->setModel(modal);
        }
        else
        {
            QMessageBox::critical(this,tr("Ошибка удаления записи"), tr("Запись не была удалена"));
        }
    }
}

void ShopInfo::on_UpdateBuy_clicked()
{
    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("SELECT Покупки.idПокупки, Структура_покупки.Количество_товара, Дата_продажи, Наименование, Название, Адрес, ФИО FROM "
                 "Покупки INNER JOIN Магазин ON Покупки.idМагазина=Магазин.idМагазина INNER JOIN Персонал ON "
                 "Покупки.idПерсонала=Персонал.idПерсонала INNER JOIN Структура_покупки ON "
                 "Покупки.idПокупки=Структура_покупки.idПокупки INNER JOIN Товары ON "
                 "Товары.idТовара=Структура_покупки.idТовара");
    if(qry->exec()){
        modal->setQuery(*qry);
        ui->tableViewBuy->setModel(modal);
    }
    else
        QMessageBox::critical(this,tr("Ошибка"), tr("Неудачно выполнился запрос"));
}
