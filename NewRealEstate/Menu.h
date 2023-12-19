#pragma once
#include "Window.h"
#include "fun_console.h"
#include <vector>

using namespace std;

class Menu : public Window {
protected:
	int active;
	int selectColor, selectBgColor;
	int first;

	vector<const char*> items;
public:
	Menu() : Window() {
		Move(20, 5);
		SetWidth(44);
		SetHeight(8);
		SetSelectColor(0);
		SetSelectBgColor(15);



		active = -1;
	}
	void customExit(int x, int y);

	void SetSelectColor(int c) { selectColor = c; }
	void SetSelectBgColor(int c) { selectBgColor = c; };
	int GetSelect() { return active; }
	int Select();
	Menu& AddElement(const char* m, bool isSelectable = true) {
		items.push_back(m);
		return *this;
	}

	int GetCount() {
		return items.size();
	}
	void DrawItem(int row, int index) {
		Write(0, row, items[index]);
	}
};
