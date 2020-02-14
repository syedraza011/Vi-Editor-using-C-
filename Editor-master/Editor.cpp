#include"Editor.h"
#include"LinkedList.h"
#include"Command.h"
#include<fstream>
#include<string>
#include <conio.h>

void goToXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void colorText(int value)
{
	COORD coord;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hConsole);
	SetConsoleTextAttribute(hConsole, value);
}

Editor::Editor()
{
	mCurrentPosition = 1;
	mCurrentLine = 1;
}

void Editor::readFile(string fileName)
{
	fstream inData;
	string line;
	inData.open(fileName);
	if (!inData)
		cout << "Error opening file" << endl;
	if (fileName == "Input.txt")
	{
		for (int i = 1; !inData.eof(); i++)
		{
			getline(inData, line);
			myList.insert(i, line);
		}
	}
	else
	{
		while (!inData.eof())
		{
			inData >> line;
			bst.add(line);
		}
	}
	inData.close();
}
/*
void Editor::displayLines() const
{
	int i, j;
	for (i = 1; i < myList.getLength() + 1; i++)
	{
		if (i == mCurrentLine)
			cout << myList.getEntry(i) << endl;
		else
			cout << myList.getEntry(i) << endl;
	}
	goToXY(mCurrentPosition, mCurrentLine - 1);
}
*/
void Editor::displayLines() const
{
	int i, j;
	for (i = 1; i < myList.getLength() + 1; i++)
	{
		//myLine = myList.getEntry(i);

		istringstream streamWords{ myList.getEntry(i) };

		vector<string> words
		{
			istream_iterator<string>(streamWords), istream_iterator<string>()
		};

		for (string w : words)
		{
			if (bst.contains(w))
				colorText(240);   //blue
			else
				colorText(241);    //unknown color
			cout << " " << w;
		}
		cout << endl;

	}
	goToXY(mCurrentPosition, mCurrentLine - 1);

}


int Editor::getCurrentPosition() const
{
	return mCurrentPosition;
}

void Editor::setCurrentPositon(int inCurrentPosition)
{
	mCurrentPosition = inCurrentPosition;
}

int Editor::getCurrentLine() const
{
	return mCurrentLine;
}

void Editor::setCurrentLine(int inCurrentLine)
{
	mCurrentLine = inCurrentLine;
}

void Editor::processCommand(char ch)
{
	string myLine, nextLine, previousLine, val, StringToInsert;
	Command undoCommand;
	int pos, nbComRepeat;
	char chtwo, val2, escapeKey(27);
	ofstream inData2;
	//prefix processing (repeating commands n times)
	if (ch >= '1' && ch <= '9') //check if the first char goes from 0 to 9
	{
		nbComRepeat = ch - '0'; //convert char to int
		myLine = myList.getEntry(mCurrentLine);
		chtwo = _getwch();
		//make sure the user doesn't try to delete an unexisting data
		if (chtwo == 'u')
		{
			for (int i = 0; i < nbComRepeat; i++)
			{
				if (!undoStack.isEmpty())
				{
					if (undoStack.peek().getCommand() == "r" || undoStack.peek().getCommand() == "x"
						|| undoStack.peek().getCommand() == "i")
						myList.replace(undoStack.peek().getLineNumber(), undoStack.peek().getValue());
					else if (undoStack.peek().getCommand() == "I")
						myList.remove(undoStack.peek().getLineNumber());
					else
						myList.insert(undoStack.peek().getLineNumber(), undoStack.peek().getValue());
					undoStack.pop();
				}
			}
		}

		if (nbComRepeat <= (myList.getLength() - mCurrentLine) ||
			(nbComRepeat <= myLine.length() - mCurrentPosition))
		{
			for (int i = 0; i < nbComRepeat; i++)
			{
				if (chtwo == 'x')
				{
					undoCommand.setCommand("x");
					undoCommand.setValue(myList.getEntry(mCurrentLine));
					undoCommand.setLineNumber(mCurrentLine);
					undoCommand.setPosition(mCurrentPosition );
					undoStack.push(undoCommand);
					val = myList.getEntry(mCurrentLine);
					val.erase(mCurrentPosition , 1);
					myList.replace(mCurrentLine, val);

				}
				else if (chtwo == 'd') //delete a number of lines accordingly to the user input
				{
					undoCommand.setCommand("dd");
					undoCommand.setValue(myList.getEntry(mCurrentLine));
					undoCommand.setLineNumber(mCurrentLine);
					undoCommand.setPosition(mCurrentPosition);
					undoStack.push(undoCommand);
					myList.remove(mCurrentLine);
				}
				else if (chtwo == 'h' || chtwo == KEY_LEFT)
				{
					if (mCurrentPosition == 0)
						mCurrentPosition = mCurrentPosition;
					else
						mCurrentPosition--;
				}
				else if (chtwo == 'j' || chtwo == KEY_DOWN)
				{
					if (mCurrentLine < myList.getLength())
					{
						nextLine = myList.getEntry(mCurrentLine + 1);
						if (mCurrentPosition >= nextLine.length())
							mCurrentPosition = nextLine.length();
						mCurrentLine++;
					}
				}
				else if (chtwo == 'k' || chtwo == KEY_UP)
				{
					if (mCurrentLine > 1)
					{
						previousLine = myList.getEntry(mCurrentLine - 1);
						if (mCurrentPosition >= previousLine.length())
							mCurrentPosition = previousLine.length();
						mCurrentLine--;
					}
				}
				else if (chtwo == 'l' || chtwo == KEY_RIGHT)
				{
					myLine = myList.getEntry(mCurrentLine);
					if (mCurrentPosition == myLine.length())
						mCurrentPosition = mCurrentPosition;
					else
						mCurrentPosition++;
				}
			}
		}
		else //inform the user that they are out of range
			cout << "Sorry, this operation cannot be processed !";
	}
	else
	{
		switch (ch)
		{
		case 'd':
			chtwo = _getwch();
			if (chtwo == 'd')
			{
				undoCommand.setCommand("dd");
				undoCommand.setValue(myList.getEntry(mCurrentLine));
				undoCommand.setLineNumber(mCurrentLine);
				undoCommand.setPosition(mCurrentPosition);
				undoStack.push(undoCommand);
				myList.remove(mCurrentLine);
			}
			break;
		case KEY_LEFT:
		case 'h':
			if (mCurrentPosition == 0)
				mCurrentPosition = mCurrentPosition;
			else
				mCurrentPosition--;
			break;

		case 'I':
			cout << ":>> ";
			getline(cin, val);
			undoCommand.setCommand("I");
			undoCommand.setValue(val);
			undoCommand.setLineNumber(mCurrentLine);
			undoCommand.setPosition(mCurrentPosition);
			undoStack.push(undoCommand);
			myList.insert(mCurrentLine, val);
			break;

		case 'i':
			undoCommand.setCommand("i");
			undoCommand.setValue(myList.getEntry(mCurrentLine));
			undoCommand.setLineNumber(mCurrentLine);
			undoCommand.setPosition(mCurrentPosition);
			undoStack.push(undoCommand);
			val = myList.getEntry(mCurrentLine);

			while ((val2 = _getche()) != escapeKey)
			{
				StringToInsert += val2;
			}
			val.insert(mCurrentPosition-1, StringToInsert);
			myList.replace(mCurrentLine, val);
			break;
		case KEY_DOWN:
		case 'j':
			if (mCurrentLine < myList.getLength())
			{
				nextLine = myList.getEntry(mCurrentLine + 1);
				if (mCurrentPosition >= nextLine.length())
					mCurrentPosition = nextLine.length();
				mCurrentLine++;
			}

			break;
		case KEY_UP:
		case 'k' :
			if (mCurrentLine > 1)
			{
				previousLine = myList.getEntry(mCurrentLine - 1);
				if (mCurrentPosition >= previousLine.length())
					mCurrentPosition = previousLine.length();
				mCurrentLine--;
			}

			break;
		case KEY_RIGHT:
		case 'l':
			myLine = myList.getEntry(mCurrentLine);
			if (mCurrentPosition == myLine.length())
				mCurrentPosition = mCurrentPosition;
			else
				mCurrentPosition++;
			break;

		case 'r':
			undoCommand.setCommand("r");
			undoCommand.setValue(myList.getEntry(mCurrentLine));
			undoCommand.setLineNumber(mCurrentLine);
			undoCommand.setPosition(mCurrentPosition);
			undoStack.push(undoCommand);
			getline(cin, val);
			myList.replace(mCurrentLine, val);
			break;

		case 'u':
			if (!undoStack.isEmpty())
			{
				if (undoStack.peek().getCommand() == "r" || undoStack.peek().getCommand() == "x"
					|| undoStack.peek().getCommand() == "i")
					myList.replace(undoStack.peek().getLineNumber(), undoStack.peek().getValue());
				else if (undoStack.peek().getCommand() == "I")
					myList.remove(undoStack.peek().getLineNumber());
				else
					myList.insert(undoStack.peek().getLineNumber(), undoStack.peek().getValue());
				undoStack.pop();
			}
			break;

		case ':':
			chtwo = _getwch();
			if (chtwo == 'w')
			{
				inData2.open("Output.txt");
				if (inData2)
				{
					for (int i = 1; i <= myList.getLength(); i++)
					{
						inData2 << myList.getEntry(i) << endl;
					}
				}
				inData2.close();
			}
			break;

		case'x':
			do {
				undoCommand.setCommand("x");
				undoCommand.setValue(myList.getEntry(mCurrentLine));
				undoCommand.setLineNumber(mCurrentLine);
				undoCommand.setPosition(mCurrentPosition-1);
				undoStack.push(undoCommand);
			} while (undoStack.peek().getLineNumber() != mCurrentLine);
			val = myList.getEntry(mCurrentLine);
			val.erase(mCurrentPosition-1, 1);
			myList.replace(mCurrentLine, val);

			break;
		}
	}
}