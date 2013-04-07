#ifndef SECURITYINTERFACE_H
#define SECURITYINTERFACE_H

#include <iostream>

using namespace std;

class SecurityInterface
{
private:
	string password;

public:
	void ErrorSound();
	bool LogIn(string accountType);
	void setpassword(string accountType);
	bool ChangePass(string accountType);
};
#endif