//#pragma once
#ifndef COMMAND_
#define COMMAND_
#include <string>
#include<iostream>
using namespace std;

class Command
{
public:
	Command();
	Command(string, string, int, int);
	void setCommand(string);
	string getCommand() const;
	void setValue(string);
	string getValue() const;
	void setLineNumber(int);
	int getLineNumber() const;
	void setPosition(int);
	int getPosition() const;
	
private:
	string mCommand;
	string mValue;
	int mLineNumber;
	int mPosition;
};

#endif