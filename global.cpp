#include "global.h"
#include "mysqlauthdlg.h"
#include <QString>
#include <QSqlDatabase>

QString sGLobalSchemaDot;
int iGlobalLangId;
QString sCurrentDatabaseType;

bool connectDatabase()
{
	bool bResult = false;
	
	//if last connection is ok, remove all there
	if(QSqlDatabase::database().driverName()!=::sCurrentDatabaseType){
		//here do some actions	
	}
	
	if(QSqlDatabase::database().isOpen())
		QSqlDatabase::database().close();

    if(::sCurrentDatabaseType == "MySQL"){
        MysqlAuthDlg * dlg = new MysqlAuthDlg();
        if(!QSqlDatabase::database().isOpen()) bResult = dlg->exec();
        else bResult = true;
        delete dlg;
    }
	
	return bResult;
}
