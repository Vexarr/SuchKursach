#include "addpersonal.h"
#include "ui_addpersonal.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

AddPersonal::AddPersonal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPersonal)
{
    ui->setupUi(this);

    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("SELECT Должность FROM Должности");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBoxPosition->setModel(modal);

    QSqlQueryModel * modal2=new QSqlQueryModel;
    QSqlQuery* qry2=new QSqlQuery();
    qry2->prepare("SELECT Пол FROM Пол");
    qry2->exec();
    modal2->setQuery(*qry2);
    ui->comboBoxMal->setModel(modal2);
}

AddPersonal::~AddPersonal()
{
    delete ui;
}

void AddPersonal::on_buttonBox_accepted()
{
    QSqlDatabase::database().transaction();
    QString Fio, Male, Position;
    int idPosition, idMale;

    Fio = ui->NamePerson->text();
    Male = ui->comboBoxMal->currentText();
    Position = ui->comboBoxPosition->currentText();

    QSqlQuery qry;
    qry.prepare("SELECT idПола FROM Пол WHERE Пол=?");
    qry.addBindValue(Male);

    if(qry.exec()){
        qry.next();
        idMale = qry.value(0).toInt();
    }

    qry.prepare("SELECT idДолжности FROM Должности WHERE Должность=?");
    qry.addBindValue(Position);

    if(qry.exec()){
        qry.next();
        idPosition = qry.value(0).toInt();
    }

    qry.prepare("INSERT INTO Персонал(ФИО, idПол, idДолжности) VALUES(?, ?, ?)");
    qry.addBindValue(Fio);
    qry.addBindValue(idMale);
    qry.addBindValue(idPosition);
    if(qry.exec()){
        QSqlDatabase::database().commit();
        accept();
    }
    else
    {
        QMessageBox::critical(this,tr("Ошибка добавления записи"), tr("Запись не была добавлена"));
    }
}

void AddPersonal::on_buttonBox_rejected()
{
    reject();
}
