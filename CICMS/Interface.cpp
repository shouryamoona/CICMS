#include <ctype.h>
#include <vector>
#include <fstream>
#include "Interface.h"
#include <windows.h>
#include <string>
#include <sstream>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void Interface::ErrorSound()
{
	PlaySound(TEXT("Windows Exclamation.wav"), NULL, SND_ASYNC | SND_FILENAME);
}

Interface::Interface(Database &Data, Operations &Op, string accountType)
{
	cashier=0;manager=0;stocks=0;marketing=0;
	PreMain(Data,Op,"NULL");
}

void Interface::PreMain(Database &Data, Operations &Op, string accountType)
{
	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, 7);

	cout << "Please enter the user type (Cashier, Marketing, Stock, Manager): ";
	cin >> accountType;

	while(accountType!="Cashier" && accountType!="Marketing" && accountType!="Stock" && accountType!="Manager")
	{
		ErrorSound();
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Invalid user type! Please try again." << endl;
		cout << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << "Please enter the user type (Cashier, Marketing, Stock, Manager): ";
		cin >> accountType;

	}

	if(Authorize.LogIn(accountType))
	{
		if(accountType=="Cashier")
		{
			cin.ignore();
			if(cashier==0)
				PlaySound(TEXT("Cashier.wav"), NULL, SND_ASYNC | SND_FILENAME);
			MainMenuCashier(Data, Op, accountType);
		}

		if(accountType=="Marketing")
		{
			cin.ignore();
			if(marketing==0)
				PlaySound(TEXT("Marketing.wav"), NULL, SND_ASYNC | SND_FILENAME);
			MainMenuMarketing(Data,Op, accountType);
		}

		if(accountType=="Stock")
		{
			cin.ignore();
			if(stocks==0)
				PlaySound(TEXT("Stocks.wav"), NULL, SND_ASYNC | SND_FILENAME);
			MainMenuStock(Data, Op, accountType);
		}

		if(accountType=="Manager")
		{
			cin.ignore();
			if(manager==0)
				PlaySound(TEXT("Manager.wav"), NULL, SND_ASYNC | SND_FILENAME);
			MainMenuManager(Data, Op, accountType);
		}
	}
}

void Interface:: ini()
{
	_name = "NO SUCH PRODUCT";
	_cat = "NO SUCH CATEGORY";
	_barnum = NULL;
	_price = NULL;
	_manu = "NO SUCH MANUFACTURER";
	_stock = NULL;
	_Numsoldpermth = NULL;
	Perishable = NULL;
	_expdate = NULL;
	_disc = NULL;
}

void Interface::MainMenuManager(Database &Data,Operations &Op, string accountType)
{
	bool loop=true;
	bool contd=true;

	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

	while(loop)
	{
		manager++;
		system ("cls");
		SetConsoleTextAttribute(hConsole, 7);
		cout << "--------------------------------------------------------------------------------";
		cout << "|                        Welcome to the CEG Hypermarket                        |";
		cout << "|                                   MANAGER                                    |";
		cout << "--------------------------------------------------------------------------------"<<endl;
		cout << "                                 <<MAIN MENU>>" <<endl;
		cout << endl;
		SetConsoleTextAttribute(hConsole, 10);
		cout <<"		            <PRODUCTS> "<< endl;
		cout << "		            1> Add new product" << endl;
		cout << "			    2> Delete product" << endl;
		cout << "			    3> Reset product sales" << endl;
		cout << "			    4> Sell Product" << endl;
		cout << "			    5> Restock product" << endl;
		cout << "                            6> Expiry Check" << endl;
		cout << endl;
		SetConsoleTextAttribute(hConsole,11);
		cout <<"		            <INFORMATION> "<< endl;
		cout << "			    7> Generate statistics" << endl;
		cout << "			    8> List all products" << endl;
		cout << "                            9> Search for product" << endl;
		cout << endl;
		SetConsoleTextAttribute(hConsole, 13);
		cout <<"		            <LOAD/SAVE> "<< endl;
		cout << "                            10> Load Data" << endl;
		cout << "			    11> Save Data" << endl;
		cout << endl;
		SetConsoleTextAttribute(hConsole, 14);
		cout <<"		            <BATCH PROCESSING> "<< endl;
		cout << "                            12> Load Jobs" << endl;
		cout << "                            13> View Error Log" << endl;
		cout << endl;
		SetConsoleTextAttribute(hConsole, 15);
		cout <<"		            <CHANGE PASSWORD/EXIT> "<< endl;
		cout << "                            14> Change password" << endl;
		cout << "			    15> Quit" << endl;
		cout << "                            16> Switch user" << endl;

		cout << endl;
		cout << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << "Please enter your choice: ";
		int choice;
		string choiceInput;
		getline(cin, choiceInput);
		stringstream buffer(choiceInput);
		buffer >> choice;

		if (!buffer)
		{
			ErrorSound();
			system ("cls");
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
			getchar();
			continue;
		}

		switch (choice)
		{
		case 1:
			Int_AddProd(Data,Op);
			break;

		case 2:
			Int_DelProd(Data,Op);
			break;

		case 3:
			Int_ResetProdSales(Data,Op);
			break;

		case 4:
			Int_SellProd(Data,Op);
			break;

		case 5:
			Int_RestockProd(Data,Op);
			break;

		case 6:
			Int_CheckifExpired(Data,Op, accountType);
			break;

		case 7:
		{
			Statistics stat;
			Int_GenStats(Data,stat,Op);
			break;
		}

		case 8:
			Int_ListAllProd(Data,Op);
			break;

		case 9:
			Int_SearchProd(Data,Op);
			break;

		case 10:
			Int_LoadData(Data,Op);
			break;

		case 11:
			Int_SaveData(Data,Op);
			break;

		case 12:
			Int_LoadJobs(Data,Op);
			break;

		case 13:
			Int_ErrorLog(Data,Op);
			break;

		case 14:
			Int_ChangePass(Data,Op, accountType);
			break;

		case 15:
			Int_Exit(Data,Op);
			loop=false;

		case 16:
			Int_SwitchUser(Data, Op);
			break;

		default:
			system ("cls"); //make previous screen blank
			SetConsoleTextAttribute(hConsole, 12);
			ErrorSound();
			cout << "Sorry, your choice is invalid!" << endl;
			cout << "Please try again." << endl;
			getchar();
			getchar();
		}
	}
}

void Interface::MainMenuCashier( Database &Data, Operations &Op, string accountType )
{
	bool loop=true;
	bool contd=true;

	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

	while(loop)
	{
		cashier++;
		system ("cls");
		SetConsoleTextAttribute(hConsole, 7);
		cout << "--------------------------------------------------------------------------------";
		cout << "|                       Welcome to the CEG Hypermarket                         |";
		cout << "|                                  CASHIER                                     |";
		cout << "--------------------------------------------------------------------------------"<<endl;
		cout << "                                 <<MAIN MENU>>" <<endl;
		cout << endl;
		SetConsoleTextAttribute(hConsole, 10);
		cout <<"		            <PRODUCTS> "<< endl;
		cout << "			    1> Sell Product" << endl;
		cout << "                            2> Expiry Check" << endl;
		cout << endl;
		SetConsoleTextAttribute(hConsole,11);
		cout <<"		            <INFORMATION> "<< endl;
		cout << "                            3> Search for product" << endl;
		cout << endl;
		SetConsoleTextAttribute(hConsole, 15);
		cout <<"		            <EXIT> "<< endl;
		cout << "			    4> Quit" << endl;
		cout << "                            5> Switch user" << endl;
		
		cout << endl;
		cout << endl;
		
		SetConsoleTextAttribute(hConsole, 7);
		cout << "Please enter your choice: ";
		
		int choice;
		string choiceInput;
		getline(cin, choiceInput);
		stringstream buffer(choiceInput);
		buffer >> choice;

		if (!buffer)
		{
			ErrorSound();
			system ("cls");
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
			getchar();
			continue;
		}

		switch (choice)
		{
		case 1:
			Int_SellProd(Data,Op);
			break;

		case 2:
			Int_CheckifExpired(Data,Op, accountType);
			break;

		case 3:
			Int_SearchProd(Data,Op);
			break;

		case 4:
			Int_Exit(Data,Op);
			loop=false;

		case 5:
			Int_SwitchUser(Data, Op);
			break;

		default:
			system ("cls"); //make previous screen blank
			SetConsoleTextAttribute(hConsole, 12);
			ErrorSound();
			cout << "Sorry, your choice is invalid!" << endl;
			cout << "Please try again." << endl;
			getchar();
			getchar();
		}
	}
}

void Interface::MainMenuStock( Database &Data, Operations &Op, string accountType )
{
	bool loop=true;
	bool contd=true;

	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

	while(loop)
	{
		stocks++;
		system ("cls");
		SetConsoleTextAttribute(hConsole, 7);
		cout << "--------------------------------------------------------------------------------";
		cout << "|                       Welcome to the CEG Hypermarket                         |";
		cout << "|                             STOCKS DEPARTMENT                                |";
		cout << "--------------------------------------------------------------------------------"<<endl;
		cout << "                                 <<MAIN MENU>>" <<endl;
		cout << endl;
		SetConsoleTextAttribute(hConsole, 10);
		cout <<"		            <PRODUCTS> "<< endl;
		cout << "		            1> Add new product" << endl;
		cout << "			    2> Delete product" << endl;
		cout << "			    3> Restock product" << endl;
		cout << "                            4> Expiry Check" << endl;
		cout << endl;
		SetConsoleTextAttribute(hConsole,11);
		cout <<"		            <INFORMATION> "<< endl;
		cout << "			    5> List all products" << endl;
		cout << "                            6> Search for product" << endl;
		cout << endl;
		SetConsoleTextAttribute(hConsole, 13);
		cout <<"		            <LOAD/SAVE> "<< endl;
		cout << "                            7> Load Data" << endl;
		cout << "			    8> Save Data" << endl;
		cout << endl;

		SetConsoleTextAttribute(hConsole, 15);
		cout <<"		            <EXIT> "<< endl;
		cout << "			    9> Quit" << endl;
		cout <<"                            10> Switch user" << endl;

		cout << endl;
		cout << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << "Please enter your choice: ";
		int choice;
		string choiceInput;
		getline(cin, choiceInput);
		stringstream buffer(choiceInput);
		buffer >> choice;

		if (!buffer)
		{
			system ("cls");
			ErrorSound();
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
			getchar();
			continue;
		}

		switch (choice)
		{
		case 1:
			Int_AddProd(Data,Op);
			break;

		case 2:
			Int_DelProd(Data,Op);
			break;

		case 3:
			Int_RestockProd(Data,Op);
			break;

		case 4:
			Int_CheckifExpired(Data,Op, accountType);
			break;

		case 5:
			Int_ListAllProd(Data,Op);
			break;

		case 6:
			Int_SearchProd(Data,Op);
			break;

		case 7:
			Int_LoadData(Data,Op);
			break;

		case 8:
			Int_SaveData(Data,Op);
			break;

		case 9:
			Int_Exit(Data,Op);
			loop=false;

		case 10:
			Int_SwitchUser(Data, Op);
			break;

		default:
			system ("cls"); //make previous screen blank
			ErrorSound();
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Sorry, your choice is invalid!" << endl;
			cout << "Please try again." << endl;
			getchar();
			getchar();
		}
	}
}

void Interface::MainMenuMarketing( Database &Data, Operations &Op, string accountType )
{
	bool loop=true;
	bool contd=true;

	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

	while(loop)
	{
		marketing++;
		system ("cls");
		SetConsoleTextAttribute(hConsole, 7);
		cout << "--------------------------------------------------------------------------------";
		cout << "|                        Welcome to the CEG Hypermarket                        |";
		cout << "|                                  MARKETING                                   |";
		cout << "--------------------------------------------------------------------------------"<<endl;
		cout << "                                 <<MAIN MENU>>" <<endl;
		cout << endl;
		SetConsoleTextAttribute(hConsole, 10);
		cout <<"		            <PRODUCTS> "<< endl;
		cout << "			    1> Reset product sales" << endl;
		cout << "                            2> Expiry Check" << endl;
		cout << endl;
		SetConsoleTextAttribute(hConsole,11);
		cout <<"		            <INFORMATION> "<< endl;
		cout << "			    3> Generate statistics" << endl;
		cout << "			    4> List all products" << endl;
		cout << "                            5> Search for product" << endl;
		cout << endl;

		SetConsoleTextAttribute(hConsole, 15);
		cout <<"		            <EXIT> "<< endl;
		cout << "			    6> Quit" << endl;
		cout <<"                            7> Switch user" << endl;

		cout << endl;
		cout << endl;

		SetConsoleTextAttribute(hConsole, 7);
		cout << "Please enter your choice: ";

		int choice;
		string choiceInput;
		getline(cin, choiceInput);
		stringstream buffer(choiceInput);
		buffer >> choice;

		if (!buffer)
		{
			ErrorSound();
			system ("cls");
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
			getchar();
			continue;
		}

		switch (choice)
		{
		case 1:
			Int_ResetProdSales(Data,Op);
			break;

		case 2:
			Int_CheckifExpired(Data,Op, accountType);
			break;

		case 3:
		{
			Statistics stat;	
			Int_GenStats(Data,stat,Op);
			break;
		}

		case 4:
			Int_ListAllProd(Data,Op);
			break;

		case 5:
			Int_SearchProd(Data,Op);
			break;

		case 6:
			Int_Exit(Data,Op);
			loop=false;

		case 7:
			Int_SwitchUser(Data, Op);
			break;

		default:
			system ("cls"); //make previous screen blank
			SetConsoleTextAttribute(hConsole, 12);
			ErrorSound();
			cout << "Sorry, your choice is invalid!" << endl;
			cout << "Please try again." << endl;
			getchar();
			getchar();
		}
	}
}


void Interface::Int_AddProd(Database &Data,Operations &Op)
{
	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	system ("cls"); //make previous screen blank
	SetConsoleTextAttribute(hConsole, 7);
	cout << "----------------------------------Add New Product-------------------------------" << endl;
	char per;
	int flag=0;
	cout<<"Please Enter Product Details"<<endl;
	cout<<"----------------------------"<<endl;
	cout<<"Name of product: ";
	getline(cin,_name);

	cout<<"Category: ";
	getline(cin,_cat);

	cout<<"Barcode Number: ";

	string barnumInput;
	getline(cin, barnumInput);
	stringstream buffer1(barnumInput);
	buffer1 >> _barnum;

	while (!buffer1)
	{
		ErrorSound();
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << endl;
		cout<<"Barcode Number: ";

		getline(cin, barnumInput);
		stringstream buffer1(barnumInput);
		buffer1 >> _barnum;

		if (buffer1)
			break;

	}

	cout<<"Manufacturer: ";
	getline(cin,_manu);

	cout<<"Price: ";

	string priceInput;
	getline(cin, priceInput);
	stringstream buffer2(priceInput);
	buffer2 >> _price;

	while (!buffer2)
	{
		ErrorSound();
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << endl;
		cout<<"Price: ";

		getline(cin, priceInput);
		stringstream buffer2(priceInput);
		buffer2 >> _price;

		if (buffer2)
			break;

	}

	cout << "Stock: ";
	string stockInput;
	getline(cin, stockInput);
	stringstream buffer3(stockInput);
	buffer3 >> _stock;

	while (!buffer3)
	{
		ErrorSound();
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << endl;
		cout<<"Stock: ";

		getline(cin, stockInput);
		stringstream buffer3(stockInput);
		buffer3 >> _stock;

		if (buffer3)
			break;

	}

	cout << "Number sold per month: ";
	string numSoldInput;
	getline(cin, numSoldInput);
	stringstream buffer4(numSoldInput);
	buffer4 >> _Numsoldpermth;

	while (!buffer4)
	{
		ErrorSound();
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << endl;
		cout << "Number sold per month: ";

		getline(cin, numSoldInput);
		stringstream buffer4(numSoldInput);
		buffer4 >> _Numsoldpermth;

		if (buffer4)
			break;
	}

	do
	{
		cout<<"Is product a perishable good? y/n "<<endl;
		cin>> per;

		if(per=='Y'||per=='y')
		{
			flag++;
			cout <<"Expiry date (DDMMYYYY): ";
			string expiryDateInput;
			cin.ignore();
			getline(cin, expiryDateInput);
			stringstream buffer5(expiryDateInput);
			buffer5 >> _expdate;

			while (!buffer5)
			{
				ErrorSound();
				SetConsoleTextAttribute(hConsole, 12);
				cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
				SetConsoleTextAttribute(hConsole, 7);
				cout << endl;
				cout <<"Expiry date (DDMMYYYY): ";

				getline(cin, expiryDateInput);
				stringstream buffer5(expiryDateInput);
				buffer5 >> _expdate;

				if (buffer5)
					break;
			}

			cout <<"Discount percentage: ";
			string discountInput;
			getline(cin, discountInput);
			stringstream buffer6(discountInput);
			buffer6 >> _disc;

			while (!buffer6)
			{
				ErrorSound();
				SetConsoleTextAttribute(hConsole, 12);
				cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
				SetConsoleTextAttribute(hConsole, 7);
				cout << endl;
				cout<<"Discount percentage: ";

				getline(cin, discountInput);
				stringstream buffer6(discountInput);
				buffer6 >> _disc;

				if (buffer6)
					break;
			}

			if(Data.addProd(per,_name, _cat,_barnum,_price, _manu,_stock,_Numsoldpermth,_expdate,_disc))
			{
				PlaySound(TEXT("Mario-sms.wav"), NULL, SND_ASYNC | SND_FILENAME);
				cout<<endl<<"ITEM ADDED!"<<endl;
			}
			else 
			{
				ErrorSound();
				cout<<"Add product error!"<<endl;
			}
		}
		else if(per=='N'||per=='n')
		{
			flag++;
			_expdate=NULL;
			_disc=NULL;
			if(Data.addProd(per,_name, _cat,_barnum,_price, _manu,_stock,_Numsoldpermth,_expdate,_disc))
			{
				PlaySound(TEXT("Mario-sms.wav"), NULL, SND_ASYNC | SND_FILENAME);
				cout<<endl<<"ITEM ADDED!"<<endl;
			}
			else 
			{
				ErrorSound();
				cout<<"Add product error!!"<<endl;
			}
		}
		else 
		{
			ErrorSound();
			cout<<"Invalid choice!"<<endl;
		}
	}while(flag!=1);

	ini();

	getchar();
	getchar();
}

void Interface::Int_DelProd(Database &Data,Operations &Op)
{
	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	system ("cls"); //make previous screen blank
	SetConsoleTextAttribute(hConsole, 7);
	cout << "----------------------------------Delete Product--------------------------------" << endl;

	cout<<"Barcode number of the product to delete:"<<endl;
	string barnumInput;
	getline(cin, barnumInput);
	stringstream buffer(barnumInput);
	buffer >> _barnum;

	while (!buffer)
	{
		ErrorSound();
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << endl;
		cout<<"Barcode number of the product to delete:"<<endl;

		getline(cin, barnumInput);
		stringstream buffer(barnumInput);
		buffer >> _barnum;

		if (buffer)
			break;
	}


	if(Data.delProd(_barnum))
	{
		PlaySound(TEXT("recycle.wav"), NULL, SND_ASYNC | SND_FILENAME);
		cout<<endl<<"ITEM DELETED!!"<<endl;
	}
	else 
	{
		ErrorSound();
		cout<<"Item can't be found. Please try again."<<endl;
	}

	ini();
	getchar();
	getchar();
}

void Interface::Int_ResetProdSales(Database &Data,Operations &Op)
{
	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	system ("cls"); //make previous screen blank
	SetConsoleTextAttribute(hConsole, 7);
	cout << "--------------------------------Reset Product Sales-----------------------------" << endl;

	cout<<"Barcode number of product to reset product sales to 0:";

	string barnumInput;
	getline(cin, barnumInput);
	stringstream buffer(barnumInput);
	buffer >> _barnum;

	while (!buffer)
	{
		ErrorSound();
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << endl;
		cout<<"Barcode number of product to reset product sales to 0:";

		getline(cin, barnumInput);
		stringstream buffer(barnumInput);
		buffer >> _barnum;

		if (buffer)
			break;
	}

	if (Op.ResetProdSales(Data,_barnum))
		cout<<"Product Sales Resetted.";
	else
	{
		ErrorSound();
		cout<<"Barcode number not found.";
	}

	ini();
	getchar();
	getchar();
}

void Interface::Int_SellProd(Database &Data,Operations &Op)
{
	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	system ("cls"); //make previous screen blank
	cout << "-----------------------------------Sell Product---------------------------------" << endl;

	cout<<"Enter barcode number of product to sell: "<<endl;
	string barnumInput;
	getline(cin, barnumInput);
	stringstream buffer1(barnumInput);
	buffer1 >> _barnum;

	while (!buffer1)
	{
		ErrorSound();
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << endl;
		cout<<"Barcode Number:";

		getline(cin, barnumInput);
		stringstream buffer1(barnumInput);
		buffer1 >> _barnum;

		if (buffer1)
			break;
	}

	int qty;
	cout<<"Enter quantity: "<<endl;
	string quantityInput;
	getline(cin, quantityInput);
	stringstream buffer2(quantityInput);
	buffer2 >> qty;

	while (!buffer2)
	{
		ErrorSound();
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << endl;
		cout<<"Enter quantity: "<<endl;

		getline(cin, quantityInput);
		stringstream buffer2(quantityInput);
		buffer2 >> qty;

		if (buffer2)
			break;
	}

	if(Op.SellProd(Data,_barnum,qty))
	{
		PlaySound(TEXT("sell.wav"), NULL, SND_ASYNC | SND_FILENAME);
		cout<<"Product sold!";
	}
	else
	{
		ErrorSound();
		cout<<"Failed!";
	}

	ini();
	getchar();
	getchar();
}

void Interface::Int_RestockProd(Database &Data,Operations &Op)
{
	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	system ("cls"); //make previous screen blank
	SetConsoleTextAttribute(hConsole, 7);
	cout << "----------------------------------Restock Product-------------------------------" << endl;

	cout<<"Enter barcode number of product to restock: "<<endl;
	string barnumInput;
	getline(cin, barnumInput);
	stringstream buffer1(barnumInput);
	buffer1 >> _barnum;

	while (!buffer1)
	{
		ErrorSound();
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << endl;
		cout<<"Enter barcode number of product to restock: "<<endl;

		getline(cin, barnumInput);
		stringstream buffer1(barnumInput);
		buffer1 >> _barnum;

		if (buffer1)
			break;
	}

	int qty;
	cout<<"Enter quantity of stock to add: "<<endl;
	string quantityInput;
	getline(cin, quantityInput);
	stringstream buffer2(quantityInput);
	buffer2 >> qty;

	while (!buffer2)
	{
		ErrorSound();
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << endl;
		cout<<"Enter quantity of stock to add: "<<endl;

		getline(cin, quantityInput);
		stringstream buffer2(quantityInput);
		buffer2 >> qty;

		if (buffer2)
			break;
	}

	if(Op.RestockProd(Data,_barnum,qty))
		cout<<"Product restocked!";
	else
	{
		ErrorSound();
		cout<<"Failed!";
	}

	ini();
	getchar();
	getchar();
}

void Interface::Int_GenStats(Database &Data,Statistics &stat,Operations &Op)
{
	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	int choice;
	system ("cls"); //make previous screen blank
	SetConsoleTextAttribute(hConsole, 7);
	cout << "--------------------------------Generate statistics-----------------------------" << endl;
	cout<<"Select options:"<<endl;
	cout<<"1.Top selling X products"<<endl;
	cout<<"2.Top selling product in given category"<<endl;
	cout<<"3.Top selling manufacturer"<<endl;
	cout << "Please enter a choice:";
	string choiceInput;
	getline(cin, choiceInput);
	stringstream buffer1(choiceInput);
	buffer1 >> choice;

	while (!buffer1)
	{
		ErrorSound();
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << endl;
		cout << "Please enter a choice:";

		getline(cin, choiceInput);
		stringstream buffer1(choiceInput);
		buffer1 >> choice;

		if (buffer1)
			break;
	}

	string str;
	vector<int> topx;

	switch(choice)
	{
	case 1:
		{
			int x;
			cout<<"Enter number of products to be listed: ";

			string xInput;
			getline(cin, xInput);
			stringstream buffer2(xInput);
			buffer2 >> x;

			while (!buffer2)
			{
				ErrorSound();
				SetConsoleTextAttribute(hConsole, 12);
				cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
				SetConsoleTextAttribute(hConsole, 7);
				cout << endl;
				cout<<"Enter number of products to be listed: ";

				getline(cin, xInput);
				stringstream buffer2(xInput);
				buffer2 >> x;

				if (buffer2)
					break;
			}
			cout<<endl;

			if(stat.TopXprod(Data,x,topx))
			{
				for (int i=0;i<topx.size();i++)
				{
					str=Data.toStringPara(topx[i]);
					cout<<i+1<<". "<<str;
				}
			}
			else
				cout<<x<<"Products have not been sold yet!";

			break;
		}

	case 2:
		{
			string cat;
			cout << endl << "Please insert the category:" << endl;
			cin >> cat;
			cout << stat.BestSaleProdByCat(Data,cat) << endl;
			break;
		}

	case 3:
		{
			cout << stat.BestSaleManu(Data) << endl;
			break;
		}

	default:
		break;
	}

	ini();
	getchar();
	getchar();
}

void Interface::Int_ListAllProd(Database &Data,Operations &Op)
{
	system ("cls"); //make previous screen blank
	cout << "--------------------------------List all the products---------------------------" << endl;

	string str;
	int i = 0;
	cout << endl;
	int curr=0;
	while(i<Data.getindex())
	{
		for (i = curr; i < 6+curr; i++)
		{   
			str = Data.toString(i);
			cout << str << endl;

			if(i >= Data.getindex()-1)
				break;
		}

		curr=i;
		getchar();
		system("cls");

		if(i>=Data.getindex()-1)
			break;
	}
}

void Interface::Int_SaveData(Database &Data,Operations &Op)
{
	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	system ("cls"); //make previous screen blank
	cout << "------------------------------------Save Data-----------------------------------" << endl;

	if(Data.SaveToFile())
	{
		getchar();
		cout<<"Save successful!";
	}
	else
	{
		ErrorSound();
		SetConsoleTextAttribute(hConsole, 12);
		cout<<"Error!";
	}

	getchar();
	getchar();
}

void Interface::Int_LoadJobs(Database &Data,Operations &Op)
{
	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	system ("cls"); //make previous screen blank
	cout << "----------------------------------Load Jobs-------------------------------------" << endl;

	BatchProcess bjobs;
	if(Op.LoadBatch(Data,bjobs)==true)
		cout<<"File successfully loaded!"<<endl;
	else
	{
		ErrorSound();
		SetConsoleTextAttribute(hConsole, 12);
		cout<<"File failed to load."<<endl;
	}

	getchar();
}

void Interface::Int_ErrorLog(Database &Data,Operations &Op)
{
	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	system ("cls"); //make previous screen blank
	cout << "----------------------------------Error Log-------------------------------------" << endl;

	cout << endl;
	string error;
	ifstream f1;
	f1.open("log.txt");

	while( !f1.eof() )
	{
		getline(f1,error,'\n');
		cout<<error<<endl;
	}

	f1.close();

	getchar();
}

void Interface::Int_SearchProd(Database &Data,Operations &Op)
{
	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	int searchChoice=0;
	string name, cat, manu;
	int barnum;
	system ("cls"); //make previous screen blank
	SetConsoleTextAttribute(hConsole, 7);
	cout << "--------------------------------Search Product--------------------------------" << endl;

	cout << "Please enter the criteria that you want to search by: " << endl;
	cout << "1. Full product name" << endl;
	cout << "2. Barcode Number" << endl;
	cout << "3. Category" << endl;
	cout << "4. Manufacturer" << endl;

	cout << "Please enter your choice: ";
	string choiceInput;
	getline(cin, choiceInput);
	stringstream buffer1(choiceInput);
	buffer1 >> searchChoice;

	while (!buffer1)
	{
		ErrorSound();
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << endl;
		cout << "Please enter your choice: ";

		getline(cin, choiceInput);
		stringstream buffer1(choiceInput);
		buffer1 >> searchChoice;

		if (buffer1)
			break;
	}

	vector<int>ListofIndex;
	switch (searchChoice)
	{
	case 1:
		cout << "Product name: ";
		//cin.ignore();
		getline(cin,name);

		Data.SearchProdByName(name,ListofIndex);
		cout<<endl<<endl;
		for (int i=0;i<ListofIndex.size();i++)
		{   
			cout<<i+1<<". "; //just prints out 1., 2., 3. for user to see more easily
			string str=Data.toStringPara(ListofIndex[i]);
			cout<<str<<endl;
		}
		SetConsoleTextAttribute(hConsole, 12);
		if (ListofIndex.size()==0) //when vector is empty- which means couldn't find any match
		{
			ErrorSound();
			cout << " Sorry unable to find the product" << endl;
		}
		break;

	case 2:
		cout << "Barcode Number: ";
		cin >> barnum;
		/*string barnumInput;
		getline(cin, barnumInput);
		stringstream buffer2(barnumInput);
		buffer2 >> barnum;

		while (!buffer2)
		{
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << endl;
		cout<<"Barcode Number:";

		getline(cin, barnumInput);
		stringstream buffer2(barnumInput);
		buffer2 >> barnum;

		if (buffer2)
		break;
		}
		*/
		Data.SearchProdByBarNum(barnum, ListofIndex);
		cout<< endl<< endl;

		for (int i=0;i<ListofIndex.size();i++)
		{   
			cout<<i+1<<". "; //just prints out 1., 2., 3. for user to see more easily
			string str=Data.toStringPara(ListofIndex[i]);
			cout<<str<<endl;
		}

		SetConsoleTextAttribute(hConsole, 12);
		if (ListofIndex.size()==0) //when vector is empty- which means couldn't find any match
		{
			ErrorSound();
			cout << " Sorry unable to find the product" << endl;
		}
		break;

	case 3:
		cout << "Category: ";
		getline(cin,cat);

		Data.SearchProdByCat(cat,ListofIndex);
		cout<<endl<<endl;

		//PRINTS
		for (int i=0;i<ListofIndex.size();i++)
		{   
			cout<<i+1<<". "; //just prints out 1., 2., 3. for user to see more easily
			string str=Data.toStringPara(ListofIndex[i]);
			cout<<str<<endl;
		}

		SetConsoleTextAttribute(hConsole, 12);
		if (ListofIndex.size()==0) //when vector is empty- which means couldn't find any match
		{
			ErrorSound();
			cout << "Sorry unable to find the product" << endl;
		}
		break;

	case 4:
		cout << "Manufacturer: ";
		getline(cin,manu);

		Data.SearchProdByManu(manu, ListofIndex);
		cout<<endl<<endl;

		//PRINTS
		for (int i=0;i<ListofIndex.size();i++)
		{   
			cout<<i+1<<". "; //just prints out 1., 2., 3. for user to see more easily
			string str=Data.toStringPara(ListofIndex[i]);
			cout<<str<<endl;
		}

		SetConsoleTextAttribute(hConsole, 12);
		if (ListofIndex.size()==0) //when vector is empty- which means couldn't find any match
		{
			ErrorSound();
			cout << " Sorry unable to find the product" << endl;
		}
		break;

	default:
		SetConsoleTextAttribute(hConsole, 12);
		ErrorSound();
		cout << "Sorry invalid choice" << endl;
		break;
	}

	getchar();
	getchar();
}

void Interface::Int_ChangePass(Database &Data,Operations &Op, string accountType)
{
	system ("cls"); //make previous screen blank
	cout << "----------------------------------Change Password-------------------------------" << endl;

	Authorize.ChangePass(accountType);
}

void Interface::Int_CheckifExpired(Database &Data,Operations &Op, string accountType)
{
	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	system ("cls"); //make previous screen blank
	SetConsoleTextAttribute(hConsole, 7);
	cout<<"-------------------------------Check Product Expiry----------------------------"<<endl;
	Product *p;
	cout<<"Enter Product barcode number: ";

	string barnumInput;
	getline(cin, barnumInput);
	stringstream buffer(barnumInput);
	buffer >> _barnum;

	while (!buffer)
	{
		ErrorSound();
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Sorry invalid input. (Do check if the type is correct) Please try again." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << endl;
		cout<<"Barcode Number:";

		getline(cin, barnumInput);
		stringstream buffer(barnumInput);
		buffer >> _barnum;

		if (buffer)
			break;
	}

	int i;
	for (i=0;i<Data.getindex();i++)
	{
		Data.getinven()->retrieve(i,p);

		if(_barnum==p->getbarnum())
		{
			if(p->isPerishable()=='n' || p->isPerishable()=='N')
			{
				cout<<"Product is not Perishable!";
				getchar();getchar();
				if(accountType=="Manager")
					MainMenuManager(Data,Op, accountType);

				if(accountType=="Cashier")
					MainMenuCashier(Data,Op, accountType);

				if(accountType=="Marketing")
					MainMenuMarketing(Data,Op, accountType);

				if(accountType=="Stock")
					MainMenuStock(Data,Op, accountType);
			}
			else
			{
				if(p->ifExpired())
				{
					cout<<"Product has EXPIRED. You are advised to scrap the product.";
					getchar();getchar();
					if(accountType=="Manager")
						MainMenuManager(Data,Op, accountType);

					if(accountType=="Cashier")
						MainMenuCashier(Data,Op, accountType);

					if(accountType=="Marketing")
						MainMenuMarketing(Data,Op, accountType);

					if(accountType=="Stock")
						MainMenuStock(Data,Op, accountType);
				}
				else
				{
					cout<<"Product has NOT expired.";
					getchar();getchar();
					if(accountType=="Manager")
						MainMenuManager(Data,Op, accountType);

					if(accountType=="Cashier")
						MainMenuCashier(Data,Op, accountType);

					if(accountType=="Marketing")
						MainMenuMarketing(Data,Op, accountType);

					if(accountType=="Stock")
						MainMenuStock(Data,Op, accountType);
				}
			}
		}
	}

	if(i==Data.getindex())
	{
		SetConsoleTextAttribute(hConsole, 12);
		ErrorSound();
		cout<<"Product not found!";
		getchar();getchar();
		if(accountType=="Manager")
			MainMenuManager(Data,Op, accountType);

		if(accountType=="Cashier")
			MainMenuCashier(Data,Op, accountType);

		if(accountType=="Marketing")
			MainMenuMarketing(Data,Op, accountType);

		if(accountType=="Stock")
			MainMenuStock(Data,Op, accountType);
	}
}

void Interface::Int_LoadData(Database &Data,Operations &Op)
{
	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	system ("cls"); //make previous screen blank
	SetConsoleTextAttribute(hConsole, 7);
	cout << "------------------------------------Load Data-----------------------------------" << endl;

	if(Data.LoadFile())
	{
		//getchar();
		cout<<"Data loaded successfully!";
	}
	else
	{
		ErrorSound();
		SetConsoleTextAttribute(hConsole, 12);
		cout<<"Error!";
	}

	getchar();
	getchar();
}

void Interface::Int_Exit(Database &Data,Operations &Op)
{
	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	system ("cls"); //make previous screen blank
	SetConsoleTextAttribute(hConsole, 7);
	cout << "----------------------------------Exit Program----------------------------------" << endl;
	char ch;
	cout<<"Do you want to save the data into the file? (y/n): ";
	do
	{
		cin>>ch;
		if(ch=='y' || ch=='Y')
		{
			Data.SaveToFile();
			getchar();
			cout<<"Data saved!"<<endl;
			PlaySound(TEXT("Windows XP Shutdown.wav"), NULL, SND_ASYNC | SND_FILENAME);
			cout<<"Shutting Down....";
			getchar();getchar();		
			exit(0);
		}
		else if(ch=='n' || ch=='N')
		{
			PlaySound(TEXT("Windows XP Shutdown.wav"), NULL, SND_ASYNC | SND_FILENAME);
			cout<<"Shutting Down....";Sleep(1000);
			getchar();getchar();exit(0);
		}
		else
		{
			ErrorSound();
			SetConsoleTextAttribute(hConsole, 12);
			cout<<"Invalid Choice! Please enter again: ";
		}
	}while(ch!='y' || ch!='Y' || ch!='n' || ch!='N');
}

void Interface::Int_SwitchUser( Database &Data, Operations &Op)
{
	this->PreMain(Data, Op, "NULL");
}
