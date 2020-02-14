#include <cassert>       // For assert
#include"Command.h"


Command::Command()
{
	mCommand ="";
	mValue = "";
	mLineNumber = 1;
	mPosition = 0;
}  // end default constructor


Command::Command(string inCommand, string inValue,int inLineNumber, int inPostion)
{
	mCommand = inCommand;
	mValue = inValue;
	mLineNumber = inLineNumber;
	mPosition = inPostion;
}


void Command::setCommand(string inCommand)
{
	mCommand = inCommand;
}


string Command::getCommand() const
{
	return mCommand;
}


void Command::setValue(string inValue)
{
	mValue = inValue;
}

string Command::getValue() const
{
	return mValue;
}

void Command::setLineNumber(int inLineNumber)
{
	mLineNumber=inLineNumber;
}

int Command::getLineNumber() const
{
	return mLineNumber;
}

void Command::setPosition(int inPosition)
{
	mPosition=inPosition;
}

int Command::getPosition() const
{
	return mPosition;
}
	