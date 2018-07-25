#pragma once

#include "DynArray.h"
#include "SLList.h"
#include <iostream>
using namespace std;

struct menuItem
{
	string name;
	bool is_subMenu;
	string subMenuPath;
};

class menu
{
	string title;
	DynArray<menuItem> choices;
	unsigned int currSelection;

public:
	inline string GetTitle() const { return title; }
	inline unsigned int GetCurrent() const { return currSelection; }
	inline DynArray<menuItem>& Getchoices() { return choices; }

	inline void SetChoices(DynArray<menuItem>& newChoices) { choices = newChoices; }
	inline void SetTitle(string newTitle) { title = newTitle; }
	inline void SetCurrent(const unsigned int newCurrSelect) { currSelection = newCurrSelect; }

};

class menuManager
{
private:
	SLList<menu> activeMenus;
public:
		//Accessor
	inline SLList<menu>& GetActiveMenus() { return activeMenus; }

	inline void SetActiveMenus(SLList<menu>& newActiveMenus) { activeMenus = newActiveMenus; }

};
