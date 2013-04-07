#ifndef BATCHPROCESSING_H
#define BATCHPROCESSING_H

#include "Job.h"
#include "queue.h"
#include "stack.h"

#include <cctype>

using namespace std;

class BatchProcess
{
private:
	Job* job;
	queue<Job>* list;
	stack<queue<Job>>* staff;
	vector<int> ebarnum;
	vector<string> eprocess;
	vector<string> employeeV;	// to store order of user submissions
	vector<string> eemployee;	// for errors

	string process;
	string name, cat, manu;
	string employee;
	double price;
	int barnum, stock, expdate, qty;
	int numjobs, numemployees;

public:
	BatchProcess();
	bool loadJobs();
	bool processJobs(Database& Data);
	void addError(int barcode,string process,string nameOfEmployee);
	bool saveLog();

};

#endif