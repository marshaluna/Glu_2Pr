#include <iostream>
#include <string>
#include <sstream>

#include "SupportFunc.h"
using namespace std;

SupportFunc::string IntToString(int num)
{
	stringstream ss;
	ss << num;
	string str;
	ss >> str;
	return str;

}

SupportFunc::int StringToInt(string str)
{
//	return atoi(str.c_str());

	stringstream ss;
	ss << str;
	int intt;
	ss >> intt;
	return intt;	
}