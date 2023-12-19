#include <iostream>
#include "Window.h"
#include <conio.h>
#include "fun_console.h"

using namespace std;

Window::Window() {
	x = y = 0;
	width = GetCols();
	height = GetRows();
	SetColor(White);
	SetBgColor(Black);
	SetBorderColor(White);

	buf[0] = 201;
	buf[1] = 205;
	buf[2] = 187;
	buf[3] = 186;
	buf[4] = 200;
	buf[5] = 188;

	active = -1;
}

Window::Window(Window& win) {
	x = y = 0;
	width = GetCols();
	height = GetRows();
	SetColor(White);
	SetBgColor(Black);
	SetBorderColor(White);

	buf[0] = 201;
	buf[1] = 205;
	buf[2] = 187;
	buf[3] = 186;
	buf[4] = 200;
	buf[5] = 188;

	active = -1;

}

void Window::SetBgColor(int c) {
	bgColor = c;
}

void Window::SetColor(int c) {
	color = c;
}

void Window::SetBorderColor(int c) {
	borderColor = c;
}

void Window::Move(int _x, int _y) {
	if (_x + width <= GetCols()) {
		x = _x;
	}
	else {
		width -= (_x - x);
		x = _x;
	}

	if (_y + height <= GetRows()) {
		y = _y;
	}
	else {
		height -= (_y - y);
		y = _y;
	}
}

void Window::SetWidth(int w) {
	if (w >= 3 && x + w <= GetCols()) {
		width = w;
	}
}

void Window::SetHeight(int h) {
	if (h >= 3 && y + h <= GetRows()) {
		height = h;
	}
}

void Window::DrawItem(int row, int index) {
	for (int i = 1; i < GetWidth(); i++) {
		Write(i, row, " ");
	}
}

Window& Window::Write(int _x, int _y, const char* str) {
	if (_x < 0 || _x >= GetWidth() || _y < 0 || _y >= GetHeight()) return *this;
	SetColor(color);
	SetBgColor(bgColor);
	GotoXY(x + _x + 1, y + _y + 1);
	for (int i = 0; str[i]; i++) {
		if (_x + i >= GetWidth()) {
			break;
		}
		std::cout << str[i];
	}
	return *this;
}

void Window::writeText(int _y, const char* str) {
	int _x = GetX();
	int isOutOfWidth = 0;
	for (int i = 0; str[i]; i++) {
		if ( i >= GetWidth() * (isOutOfWidth + 1)) {
			_y += 1;
			_x = GetX();
			isOutOfWidth++;
		}
		GotoXY(_x + i - (GetWidth() * isOutOfWidth), _y);
		cout << str[i];
	}
}

void Window::Show() {

	::SetColor(borderColor, Black);
	GotoXY(x - 1, y);
	std::cout << buf[0];
	for (int j = 0; j < width; j++) {
		std::cout << buf[1];
	}
	std::cout << buf[2];
	for (int i = 1; i < height; i++) {
		GotoXY(x - 1, y + i);
		std::cout << buf[3];
		GotoXY(x + width, y + i);
		std::cout << buf[3];
	}
	GotoXY(x - 1, y + height);
	std::cout << buf[4];
	for (int j = 0; j < width; j++) {
		std::cout << buf[1];
	}
	std::cout << buf[5];
	::SetColor(color, bgColor);
	for (int i = 1; i < height; i++) {
		GotoXY(x, y + i);
		for (int j = 0; j < width; j++) {
			std::cout << " ";
		}
	}
	GotoXY(x, y);
}

void Window::clear() {
	SetColor(White);
	SetBgColor(Black);
	cls();
}

Window* Window::createWindow(int width, int height) {
	clear();

	Window* win = new Window;
	win->Move(20, 5);
	win->SetHeight(height);
	win->SetWidth(width);
	SetColor(15);
	SetBgColor(Black);
	win->Show();

	return win;
}