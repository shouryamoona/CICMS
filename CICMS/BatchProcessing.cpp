#include <fstream>
#include "BatchProcessing.h"


BatchProcess::BatchProcess()
{
	staff=new stack<queue<Job>>;
	numjobs=0;
	numemployees=0;
	ebarnum.clear();
	eprocess.clear();
	eemployee.clear();
}

bool BatchProcess::loadJobs()
{
	ifstream f2;
	f2.open("batchjobs.txt");

	f2>>numemployees;
	
	for(int i=0;i<numemployees;i++)
	{
		getline(f2,employee);getline(f2,employee);
		employeeV.push_back(employee);

		f2>>numjobs;
		list=new queue<Job>;
		for(int i=0;i<numjobs;i++)
		{
			f2>>process;
			if(process=="ADD")
			{
				f2.ignore(80,'\n');
				getline(f2,name);
				getline(f2,cat);
				f2>>barnum>>price;
				f2.ignore(80,'\n');
				getline(f2,manu);

				f2>>stock;

				job=new Job(name,cat,barnum,price,manu,stock);
				list->push_back(job);
			}
			else if(process=="DELETE")
			{
				f2>>barnum;

				job=new Job(barnum);
				list->push_back(job);
			}
			else if(process=="RESTOCK")
			{
				f2>>barnum>>stock;

				job=new Job(barnum,qty,"r");
				list->push_back(job);
			}
			else if(process=="DISPOSE")
			{
				f2>>barnum>>expdate;

				job=new Job(barnum,expdate,"d");
				list->push_back(job);
			}
			else if(process=="SALE")
			{
				f2>>barnum>>qty;

				job=new Job(barnum,qty,"s");
				list->push_back(job);
			}
			else
			{
				cout << "Error loading jobs!" << endl;
				return false;
			}
		}
		staff->push_back(list);
	}
	if(f2.bad())
		perror("Error while reading file.");

	f2.close();

	return true;
}

bool BatchProcess::processJobs(Database& Data) 
{
	int i = employeeV.size()-1;

	while(!staff->empty())
	{
		staff->retrieve(list);	// Access the top of stack
		
		while(!list->empty())
		{
			list->retrieve(job);	//first job in queue
			int jobType = job->getJobType();

			switch(jobType)
			{	
			case 0:	//case ADD:
				if( !(job->dojob1(Data,job->getName(), job->getCat(), job->getBarNum(),job->getPrice() , job->getManu(), job->getStock())) )
					addError(job->getBarNum(),"ADD",employeeV[i]);	
				break;

			case 1:	//case DELETE:
				if( !(job->dojob2(Data,job->getBarNum())) )
					addError(job->getBarNum(),"DELETE",employeeV[i]);
				break;
				
			case 2:	//case RESTOCK:
				if( !(job->dojob3(Data,job->getBarNum(), job->getStockorexporsale())) )
					addError(job->getBarNum(),"RESTOCK",employeeV[i]);
				break;

			case 3:	//case DISPOSE:
				if( !(job->dojob4(Data,job->getBarNum(), job->getStockorexporsale())) )
					addError(job->getBarNum(),"DISPOSE",employeeV[i]);
				break;
				
			case 4:	//case SALE:
				if( !(job->dojob5(Data,job->getBarNum(), job->getStockorexporsale())) )
					addError(job->getBarNum(),"SALE",employeeV[i]);
				break;
			}
			list->pop();
		}
		staff->pop();
		i--; // to change the employee	
	}
	return true;
}

void BatchProcess::addError(int barcode,string process,string nameOfEmployee)	// Adding into vectors the error cases and details
{
	ebarnum.push_back(barcode);
	eprocess.push_back(process);
	eemployee.push_back(nameOfEmployee);
}

bool BatchProcess::saveLog()	// Saving the error encountered in each job into log.txt file
{
	ofstream f1;
	f1.open("log.txt");

	for(int i = 0; i < ebarnum.size(); i++)
	{
		f1 << ebarnum[i] << " " << eprocess[i] << " " << eemployee[i] << endl;
	}	
	
	f1.close();

	return true;
}
