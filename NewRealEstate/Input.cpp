#pragma once

#include <conio.h>
#include "Input.h"
#include "fun_console.h"
#include "Menu.h"
#include "Window.h"
#include <iostream>
#include <string>

using namespace std;

void Input::customInput(Window& win, const char* text, int y) {
	y += win.GetY();
	GotoXY(win.GetX(), y);
	int width = win.GetWidth();
	width -= 2;

	int length = width - (strlen(text) - 1);
	input = new char[length + 1];
	input[0] = 0;
	int k = 0;
	cout << text;

	while (k <= length) {
		GotoXY(win.GetX() + strlen(text), y);
		cout << string(length, ' ');
		GotoXY(win.GetX() + strlen(text), y);
		cout << input;
		int key = _getch();
		if (key == 8) {
			GotoXY(win.GetX(), y);
			k--;
			input[k] = 0;
			continue;
		}
		if (key == 13) {
			break;
		}
		if (key == 27) continue;
		if (k == length) {
			k = 0;
			continue;
		}
		input[k] = key;
		k++;
		input[k] = 0;
	}
}

bool Input::operator==(const char* text)
{
	return strcmp(input, text) == 0;
}
