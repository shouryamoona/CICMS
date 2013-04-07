#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include "Database.h"
#include "Product.h"
#include "PerishableFood.h"
#include "Operations.h"
#include "SecurityInterface.h"
#include "Statistics.h"

using namespace std;

class Interface
{
private:
	int cashier,stocks,marketing,manager;
	string _name;
	string _cat;
	int _barnum;
	double _price;
	string _manu;
	int _stock;
	int _Numsoldpermth;
	char Perishable;
	int _expdate;
	double _disc;
	SecurityInterface Authorize;
	
public:
	void ini();
	Interface( Database &Data, Operations &Op, string accountType );
	void PreMain(Database &Data, Operations &Op, string accountType);
	void MainMenuManager( Database &Data, Operations &Op, string accountType );
	void MainMenuCashier( Database &Data, Operations &Op, string accountType );
	void MainMenuStock( Database &Data, Operations &Op, string accountType );
	void MainMenuMarketing( Database &Data, Operations &Op, string accountType );
	void Int_AddProd( Database &Data, Operations &Op);
	void Int_DelProd( Database &Data, Operations &Op);
	void Int_ResetProdSales( Database &Data, Operations &Op);
	void Int_SellProd( Database &Data, Operations &Op);
	void Int_RestockProd( Database &Data, Operations &Op);
	void Int_GenStats( Database &Data, Statistics &stat, Operations &Op);
	void Int_ListAllProd( Database &Data, Operations &Op );
	void Int_SaveData( Database &Data, Operations &Op);
	void Int_LoadJobs(Database &Data,Operations &Op);
	void Int_ErrorLog(Database &Data,Operations &Op);
	void Int_SearchProd( Database &Data, Operations &Op);
	void Int_ChangePass( Database &Data, Operations &Op, string accountType );
	void Int_CheckifExpired( Database &Data, Operations &Op, string accountType );
	void Int_LoadData( Database &Data, Operations &Op);
	void Int_Exit( Database &Data, Operations &Op );
	void Int_SwitchUser( Database &Data, Operations &Op);
	void Exit();
	void ErrorSound();

};

#endif