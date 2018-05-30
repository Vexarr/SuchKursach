#ifndef MYSQLAUTHDLG_H
#define MYSQLAUTHDLG_H

#include <QDialog>
#include "ui_mysqlauthdlg.h"
#include <QSqlDatabase>

class MysqlAuthDlg : public QDialog
{
	Q_OBJECT

public:
	MysqlAuthDlg(QWidget *parent = 0);
	~MysqlAuthDlg();
    QSqlDatabase db;
	bool authirizate();
	void LoadPrefs();
	void SavePrefs();
private:
	Ui::MysqlAuthDlg ui;
private slots:
	void on_pushButton_accept_clicked();
};

#endif // MYSQLAUTHDLG_H
