#pragma once

#include <Windows.h>
//Memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <conio.h>

#include <iostream>
using namespace std;

#include "Structures.h"
#include <string>
#include <fstream>

SLList<menu>& ReadMenuFile(string path, SLList<menu>& managedManu);
void ShowMenu(SLList<menu>& managedManu, menuManager *Menus);

int main(int argc, char** argv)
{
	//memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//_CrtSetBreakAlloc(334);

	menuManager *myMenus = new menuManager;
	SLList<menu> myMenuList;
	myMenuList = myMenus->GetActiveMenus();

	for (int i = 1; i < argc; ++i)
		cout << argv[i] << endl;
	string filename;
	

	if (argc > 1){
		filename = argv[1];
		if (filename.find(".mnu") != string::npos)
			myMenuList = ReadMenuFile(filename, myMenuList);
		else{
			filename = "Resources//main.mnu";
			myMenuList = ReadMenuFile(filename, myMenuList);
			}
			myMenus->SetActiveMenus(myMenuList);
			ShowMenu(myMenuList, myMenus);

		}
	else{
		filename = "Resources//main.mnu";
		myMenuList = ReadMenuFile(filename, myMenuList);
		myMenus->SetActiveMenus(myMenuList);
		ShowMenu(myMenuList, myMenus);
	}

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { 24, 30 };
	SetConsoleCursorPosition(out, position);

	delete myMenus;
	system("pause");
	return 0;
}

SLList<menu>& ReadMenuFile(string path, SLList<menu>& managedManu){
	ifstream fin;
	fin.open(path);

	if (!fin.is_open()){
		path = "Resources//main.mnu";
		fin.open(path);
	}



	if (fin.is_open()){
		menu *myMenu = new menu();
		DynArray<menuItem> myChoices;

		string mainName;
		string itemType;
		string itemName;
		int count;
		getline(fin, mainName, '\n');
		fin >> count;
		fin.ignore(INT_MAX, '\n');
		myMenu->SetTitle(mainName);

		for (int i = 0; i < count; i++){
			string itemPath;
			getline(fin, itemType, ' ');
			menuItem myNewItem;
			string garbage;
			if (itemType == "MENU"){

				getline(fin, garbage, '"');
				getline(fin, itemName, '"');
				getline(fin, garbage, '"');
				getline(fin, itemPath, '"');
				
				myNewItem.is_subMenu = true;
				myNewItem.name = itemName;
				myNewItem.subMenuPath = itemPath;
			}
			else{
				getline(fin, garbage, '"');
				getline(fin, itemName, '"');

				myNewItem.is_subMenu = false;
				myNewItem.name = itemName;
			}
			getline(fin, garbage, '\n');
			myChoices.append(myNewItem);

			myMenu->SetCurrent(0);
		}
		fin.close();
		myMenu->SetChoices(myChoices);
		managedManu.addHead(*myMenu);

		delete myMenu;
	}
	

	return managedManu;
}

void ShowMenu(SLList<menu>& managedManu, menuManager *Menus){

	bool end = false;
	SLLIter<menu> *myIter = new SLLIter<menu>(managedManu);
	DynArray<menuItem> myChoices;
	if (Menus->GetActiveMenus().size() > 0){
		while (!end){
			delete myIter;
			myIter = new SLLIter<menu>(Menus->GetActiveMenus());
			myIter->begin();
			myChoices = myIter->current().Getchoices();
			
			bool refresh = false;

			myIter->begin();
			
			HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD position = { 18, 0 };

			system("cls");
			position.X = 10;
			position.Y = 6;
			SetConsoleCursorPosition(out, position);
			SetConsoleTextAttribute(out, FOREGROUND_RED);
			cout << "*******************************************************************";
			position.X = 10;
			position.Y = 7;
			SetConsoleCursorPosition(out, position);
			cout << "\t\t\t " << myIter->current().GetTitle().c_str();
			position.X = 10;
			position.Y = 8;
			SetConsoleCursorPosition(out, position);
			cout << "*******************************************************************";

			SetConsoleTextAttribute(out, 0 | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			position.X = 12;
			position.Y = 10;
			SetConsoleCursorPosition(out, position);

			for (unsigned int i = 0; i < myChoices.size(); i++){

				position.X = 12;
				position.Y += 1;
				SetConsoleCursorPosition(out, position);

				cout << myChoices[i].name;
			}

			position.Y += 1;
			SetConsoleCursorPosition(out, position);

			cout << "Back";

			position.X = 10;
			position.Y = 11 + (short)myIter->current().GetCurrent();
			SetConsoleCursorPosition(out, position);

			SetConsoleCursorPosition(out, position);
			cout << ">\b";
			refresh = false;
			while (!refresh){
				if (!(GetAsyncKeyState(VK_UP) & 0x8000) && !(GetAsyncKeyState(VK_DOWN) & 0x8000)){
					// Key held. The cursor moves two spots because the KEY_UP state

					switch (_getch()){
					case 80: { // DOWN ARROW
								 cout << " ";
								 if (position.Y == (short)(11 + myChoices.size()))
									 position.Y = 11;
								 else
									 position.Y += 1;
								 SetConsoleCursorPosition(out, position);
								 cout << ">\b";
								 myIter->current().SetCurrent((unsigned int)(position.Y - 11));
								 break;
					}
					case 72:{ //UP ARROW 
								cout << " ";
								if (position.Y == 11)
									position.Y += (short)(myChoices.size());
								else
									position.Y -= 1;
								SetConsoleCursorPosition(out, position);
								cout << ">\b";
								myIter->current().SetCurrent((unsigned int)(position.Y - 11));
								break;
					}

					case '\r':{ // Enter pressed 
								  unsigned int index = position.Y - 11;
								  if (index < myChoices.size() && myChoices[index].is_subMenu){
									  string file = "Resources//";

									  file.append((myChoices[index].subMenuPath).c_str());

									  managedManu = Menus->GetActiveMenus();

									  managedManu = ReadMenuFile(file, managedManu);

									  Menus->SetActiveMenus(managedManu);

									  /*delete myIter;
									  myIter = new SLLIter<menu>(Menus->GetActiveMenus());
									  myIter->begin();
									  myChoices = myIter->current().Getchoices();*/
								  }
								  else if (position.Y == (short)(11 + myChoices.size()))
								  {
									 
									  delete myIter;
									  myIter = new SLLIter<menu>(Menus->GetActiveMenus());
									  myIter->begin();
									 
									  Menus->GetActiveMenus().remove(*myIter);
								  }
								  if (myIter->end()){
									  end = true;
									  delete myIter;
								  }

								  refresh = true;
								  break;
					}
					}
				}

			}

		}
	}
}