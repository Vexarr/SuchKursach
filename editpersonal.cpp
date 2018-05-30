#include "editpersonal.h"
#include "ui_editpersonal.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>

EditPersonal::EditPersonal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPersonal)
{
    ui->setupUi(this);
}

EditPersonal::~EditPersonal()
{
    delete ui;
}

void EditPersonal::on_buttonBox_accepted()
{
    QSqlDatabase::database().transaction();
    QString person_name, position, male;
    int idPosition, idMale;

    person_name= ui->EditNamePerson->text();
    male = ui->comboBoxEditMal->currentText();
    position = ui->comboBoxEditPosition->currentText();

    QSqlQuery qry;
    qry.prepare("SELECT idПола FROM Пол WHERE Пол=?");
    qry.addBindValue(male);

    if(qry.exec()){
        qry.next();
        idMale = qry.value(0).toInt();
    }

    qry.prepare("SELECT idДолжности FROM Должности WHERE Должность=?");
    qry.addBindValue(position);

    if(qry.exec()){
        qry.next();
        idPosition = qry.value(0).toInt();
    }

    qry.prepare("UPDATE Персонал SET ФИО=?, idПол=?, idДолжности=? WHERE idПерсонала=?");
    qry.addBindValue(person_name);
    qry.addBindValue(idMale);
    qry.addBindValue(idPosition);
    qry.addBindValue(person_id);
    if(qry.exec()){
        QSqlDatabase::database().commit();
        accept();
    }
    else
    {
        QMessageBox::critical(this,tr("Ошибка редактирования записи"), tr("Запись не была отредактирована"));
    }
}

void EditPersonal::on_buttonBox_rejected()
{
    reject();
}

void EditPersonal::setDataPerson(const int &row_num_person)
{
    QSqlQueryModel * modal=new QSqlQueryModel;
    QSqlQuery* qry3=new QSqlQuery();
    qry3->prepare("SELECT Должность FROM Должности");
    qry3->exec();
    modal->setQuery(*qry3);
    ui->comboBoxEditPosition->setModel(modal);

    QSqlQueryModel * modal2=new QSqlQueryModel;
    QSqlQuery* qry2=new QSqlQuery();
    qry2->prepare("SELECT Пол FROM Пол");
    qry2->exec();
    modal2->setQuery(*qry2);
    ui->comboBoxEditMal->setModel(modal2);

    QString person_name, position, male;

    if (row_num_person >=0){
        QSqlQuery qry;
        qry.prepare("SELECT Персонал.idПерсонала, ФИО, Должность, Пол FROM ((Персонал INNER JOIN Должности ON Персонал.idДолжности=Должности.idДолжности) INNER JOIN Пол ON Персонал.idПол=Пол.idПола) LIMIT ?, 1");
        qry.addBindValue(row_num_person);
        if(qry.exec()){
            qry.next();
            person_id = qry.value(0).toInt();
            person_name = qry.value(1).toString();
            position = qry.value(2).toString();
            male = qry.value(3).toString();
        }
        ui->EditNamePerson->setText(person_name);

        ui->comboBoxEditPosition->setCurrentText(position);

        ui->comboBoxEditMal->setCurrentText(male);
    }
}
