#pragma once
#include"LinkedStack.h"
#include"BinarySearchTree.h"
#include"LinkedList.h"
#include"Command.h"
#include<windows.h>
#include<vector>
#include<iterator> 
#include<string>
#include<sstream>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class Editor
{
public:
	Editor();
	void displayLines() const;
	void readFile(string);
	void readKeywords(string);
	int getCurrentPosition() const;
	void setCurrentPositon(int);
	int getCurrentLine() const;
	void setCurrentLine(int);
	void processCommand(char);
private:
	LinkedList<string> myList;
	LinkedStack<Command> undoStack;
	BinarySearchTree<string> bst;
	int mCurrentPosition;
	int mCurrentLine;
};
