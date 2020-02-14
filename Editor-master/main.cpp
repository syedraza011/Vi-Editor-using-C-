#include"Editor.h"
#include<conio.h>
#include<iostream>
#include <Windows.h>
using namespace std;
int main(int argc, char *argv[])
{
	Editor myEditor;
	string userCommmand;
	myEditor.readFile(argv[1]);
	myEditor.readFile(argv[2]);
	myEditor.displayLines();


	char ch = _getche();
	do {
		myEditor.processCommand(ch);
		system("cls");
		myEditor.displayLines();
		ch = _getch();
		Sleep(10);
	} while (ch != 'q');

	system("PAUSE");
	return 0;
}