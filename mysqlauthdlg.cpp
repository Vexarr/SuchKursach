#include "mysqlauthdlg.h"
#include "global.h"
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>

QString sConfigMySqlFilePath;

MysqlAuthDlg::MysqlAuthDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	sConfigMySqlFilePath = qApp->applicationDirPath()+"/database_mysql.cfg";
	LoadPrefs();
}

MysqlAuthDlg::~MysqlAuthDlg()
{

}

bool MysqlAuthDlg::authirizate()
{
// 	QCoreApplication::addLibraryPath(QString("%1/%2")
// 		.arg(qApp->applicationDirPath())
// 		.arg("sqldrivers"));

	::sCurrentDatabaseType = "QMYSQL";
    db = QSqlDatabase::addDatabase(::sCurrentDatabaseType);
	db.setHostName(ui.lineEdit_host->text());
	db.setPort(ui.spinBox->value());
	db.setDatabaseName(ui.lineEdit_base->text());
	db.setUserName(ui.lineEdit_username->text());
	db.setPassword(ui.lineEdit_passw->text());
	
	bool login = db.open();
	if(db.lastError().isValid()){
		QMessageBox::information(this, "", db.lastError().text());
	}
	return login;
}

void MysqlAuthDlg::LoadPrefs()
{
	QFile file(sConfigMySqlFilePath);
	if(file.open(QIODevice::ReadOnly)){
		QStringList lst = QString().append(file.readAll()).split("\n");
		if(lst.count()>=4){
			QString sHostname = lst.at(0);
			QString sPort = lst.at(1);
			QString sDatabase = lst.at(2);
			QString sUsername = lst.at(3);
			
			ui.lineEdit_base->setText(sDatabase);
			ui.lineEdit_host->setText(sHostname);
			ui.lineEdit_username->setText(sUsername);
			ui.spinBox->setValue(sPort.toInt());

			if(lst.count()==5){
				ui.lineEdit_passw->setText( lst.at(4) );
				ui.checkBox_savePass->setChecked(true);
				authirizate();
			}
		}
		file.close();
	}
}

void MysqlAuthDlg::SavePrefs()
{
	QFile f(sConfigMySqlFilePath);
	if(f.open(QIODevice::WriteOnly)){
		QStringList lstValues;
		lstValues << ui.lineEdit_host->text() 
			<< QString::number(ui.spinBox->value())
			<< ui.lineEdit_base->text()
			<< ui.lineEdit_username->text();
		if(ui.checkBox_savePass->isChecked()) lstValues << ui.lineEdit_passw->text();
		f.write(QByteArray().append(lstValues.join("\n")));

		f.close();
	}	else {
		QMessageBox::information(this, "", tr("Failed to open config file!") );
	}
}

void MysqlAuthDlg::on_pushButton_accept_clicked()
{
	if(authirizate()){
		SavePrefs();
		accept();
	}
}
