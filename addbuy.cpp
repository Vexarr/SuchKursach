#include "addbuy.h"
#include "ui_addbuy.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

AddBuy::AddBuy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBuy)
{
    ui->setupUi(this);

    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("SELECT Наименование FROM Товары");
    qry->exec();
    modal->setQuery(*qry);
    ui->AddProductBox->setModel(modal);

    QSqlQueryModel * modal2=new QSqlQueryModel;
    QSqlQuery* qry2=new QSqlQuery();
    qry2->prepare("SELECT ФИО FROM Персонал INNER JOIN Должности ON "
                  "Персонал.idДолжности=Должности.idДолжности WHERE Должность='Продавец'");
    qry2->exec();
    modal2->setQuery(*qry2);
    ui->AddPersonBox->setModel(modal2);

    QSqlQueryModel * modal3=new QSqlQueryModel;
    QSqlQuery* qry3=new QSqlQuery();
    qry3->prepare("SELECT Адрес FROM Магазин");
    qry3->exec();
    modal3->setQuery(*qry3);
    ui->AddShopBox->setModel(modal3);

    QStringList titles;
    titles << "Товар" << "Количество";
    ui->AddtableWidget->setColumnCount(2);
    ui->AddtableWidget->setHorizontalHeaderLabels(titles);
}

AddBuy::~AddBuy()
{
    delete ui;
}

void AddBuy::on_DialogButtonBox_accepted()
{
    QSqlDatabase::database().transaction();
    QString Address, Date, Person, product;
    int idPerson, idShop, ch, idBuy, count, idProduct;

    Address = ui->AddShopBox->currentText();
    Date = ui->AddDate->text();
    Person = ui->AddPersonBox->currentText();

    ch = ui->AddtableWidget->rowCount();

    QSqlQuery qry;
    qry.prepare("SELECT idМагазина FROM Магазин WHERE Адрес=?");
    qry.addBindValue(Address);
    if(qry.exec())
    {
        qry.next();
        idShop = qry.value(0).toInt();
    }

    qry.prepare("SELECT idПерсонала FROM Персонал WHERE ФИО=?");
    qry.addBindValue(Person);
    if(qry.exec())
    {
        qry.next();
        idPerson = qry.value(0).toInt();
    }

    qry.prepare("INSERT IGNORE INTO Покупки(Количество, idМагазина, idПерсонала, Дата_продажи) "
                "VALUES(?, ?, ?, ?)");
    qry.addBindValue(ch);
    qry.addBindValue(idShop);
    qry.addBindValue(idPerson);
    qry.addBindValue(Date);
    if(qry.exec())
    {
        qry.prepare("SELECT idПокупки FROM Покупки WHERE Количество=? AND idМагазина=? "
                    "AND idПерсонала=? AND Дата_продажи=?");
        qry.addBindValue(ch);
        qry.addBindValue(idShop);
        qry.addBindValue(idPerson);
        qry.addBindValue(Date);
        if(qry.exec())
        {
            qry.next();
            idBuy = qry.value(0).toInt();
        }
    }

    for(int i=0; i<ch; ++i)
    {
        product = ui->AddtableWidget->item(i, 0)->text();
        count = ui->AddtableWidget->item(i, 1)->text().toInt();
        qry.prepare("SELECT idТовара FROM Товары WHERE Наименование=?");
        qry.addBindValue(product);
        if(qry.exec())
        {
            qry.next();
            idProduct = qry.value(0).toInt();
        }

        qry.prepare("INSERT INTO Структура_покупки(idПокупки, idТовара, Количество_товара) "
                    "VALUES(?, ?, ?)");
        qry.addBindValue(idBuy);
        qry.addBindValue(idProduct);
        qry.addBindValue(count);
        if(!qry.exec())
        {
            QMessageBox::critical(this,tr("Ошибка добавления записи"), tr("Запись не была добавлена"));
        }
    }
    QSqlDatabase::database().commit();
    accept();
}


void AddBuy::on_AddInBuy_clicked() // Добавление товаров в корзину
{
    QSqlDatabase::database().transaction();
    QString ProductName;
    int Count, num;

    ProductName = ui->AddProductBox->currentText();
    Count = ui->AddCount->text().toInt();

    ui->AddtableWidget->insertRow(ui->AddtableWidget->rowCount());
    num = ui->AddtableWidget->rowCount()-1;

    ui->AddtableWidget->setItem(num, 0,  new QTableWidgetItem(ProductName));
    ui->AddtableWidget->setItem(num, 1, new QTableWidgetItem(QString::number(Count)));
}


void AddBuy::on_DialogButtonBox_rejected()
{
    reject();
}
