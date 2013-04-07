#include <iostream>
#include "Interface.h"
#include "Database.h"
#include "Product.h"
#include "Operations.h"
#include "PerishableFood.h"

using namespace std;

int main()
{
	Operations Op;
	Database Data;
	Interface UI(Data,Op, "null");
	
	return 0;
}