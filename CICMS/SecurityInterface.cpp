#include <fstream>
#include <iostream>
#include <string>
#include <conio.h>
#include "SecurityInterface.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

void SecurityInterface::ErrorSound()
{
	PlaySound(TEXT("Windows Exclamation.wav"), NULL, SND_ASYNC | SND_FILENAME);
}

void SecurityInterface::setpassword(string accountType)
{
	ifstream f1;

	if(accountType=="Cashier")
	{
		f1.open("cashierPassword.txt");	
		f1>>password;
		f1.close();
	}

	if(accountType=="Marketing")
	{
		f1.open("marketingPassword.txt");	
		f1>>password;
		f1.close();
	}

	if(accountType=="Stock")
	{
		f1.open("stockPassword.txt");	
		f1>>password;
		f1.close();
	}

	if(accountType=="Manager")
	{
		f1.open("password.txt");	
		f1>>password;
		f1.close();
	}
}

bool SecurityInterface::LogIn(string accountType)
{
	setpassword(accountType);
	char temp[5];
	int i=0,count=0;
	char a;
	int flag=0;
	bool backspace=false;
	do
	{
		count=0;
		cout<< "Please enter the password (Case Sensitive): ";
		for(i=0;i<100;i++)
		{
			if(backspace)
			{
				i--;
				i--;
			}
		
			a=getch();

			if(a==13)
			{
				break;
			}


			else if(i<5)
			{
				temp[i]=a;
			}

			if(a==8)
			{
				cout << "\b \b";
				backspace=true;
			}
			else
			{
				backspace=false;
				cout<<"*";
			}
		}
		for(int k=0;k<5;k++)
		{
			if(temp[k]==password[k] && i==5)
				count++;
		}

		if(count!=5)
		{
			ErrorSound();
			flag++;
			cout<<endl<<"Wrong password!!"<<endl<<"You have "<<5-flag<<" tries left"<<endl<<endl;
		}
	}while(count!=5 && flag<5);

	if(flag==5)
	{
		cout<<"Shutting Down....";
		getchar();
		getchar();
		exit(0);
	}

	return true;
}

bool SecurityInterface::ChangePass(string accountType)
{
	int flag=0;
	char check[5],newpass1[5],newpass2[5];
	ofstream f1;
	char a;
	int i=0;

	while(flag<5)
	{
		cout<<"Please enter old password: ";
		for(i=0;i<100;i++)
		{
			a=getch();
			if(a==13)
			{
				break;
			}
			else if(i<5)
			{
				check[i]=a;
			}
			cout<<"*";
		}
		cout<<endl;

		if(password[0]==check[0] && password[1]==check[1] && password[2]==check[2] && 
			password[3]==check[3] && password[4]==check[4] && i==5)
		{
			do
			{
				do
				{
					cout<<"Please enter new password (should be EXACTLY 5 characters): ";
					for(i=0;i<100;i++)
					{
						a=getch();
						if(a==13)
						{
							break;
						}
						else if(i<5)
						{
							newpass1[i]=a;
						}
						cout<<"*";
					}
					if(i!=5)
					{
						ErrorSound();
						cout<<endl<<"Password should be 5 characters long."<<endl<<endl;
					}
				}while(i!=5);

				cout<<endl<<"Please enter new password again: ";
				for(i=0;i<100;i++)
				{
					a=getch();
					if(a==13)
					{
						break;
					}
					else if(i<5)
					{
						newpass2[i]=a;
					}
					cout<<"*";
				}

				if(newpass1[0]!=newpass2[0] || newpass1[1]!=newpass2[1] || newpass1[2]!=newpass2[2] || 
					newpass1[3]!=newpass2[3] || newpass1[4]!=newpass2[4] || i!=5)
				{
					ErrorSound();
					cout<<endl<<"The passwords don't match!!"<<endl<<endl;
				}
			}while(newpass1[0]!=newpass2[0] || newpass1[1]!=newpass2[1] || newpass1[2]!=newpass2[2] || 
				newpass1[3]!=newpass2[3] || newpass1[4]!=newpass2[4] ||i!=5);

			if(accountType=="Cashier")
				f1.open("cashierPassword.txt");

			if(accountType=="Marketing")
				f1.open("marketingPassword.txt");

			if(accountType=="Stock")
				f1.open("stock.txt");

			if(accountType=="Manager")
				f1.open("password.txt");
			for(int j=0;j<5;j++)
			{	
				f1<<newpass1[j];
				password[j]=newpass1[j];
			}
			flag=5;
			cout<<endl<<endl<<"PASSWORD CHANGED!!";
		}

		else
		{
			ErrorSound();
			flag++;
			cout<<"Wrong Password!!"<<endl<<"You have "<<5-flag<<" tries left."<<endl<<endl;
		}
	}
	getchar();getchar();
	return true;
}