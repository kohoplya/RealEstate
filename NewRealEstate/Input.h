#pragma once
#include "Window.h"

class Input {
	char* input;

public:
	Input(int len) {
		input = new char[len + 1];
		input[0] = 0;
	}
	~Input() { delete[] input;}

	void customInput(Window& win, const char* text = "", int y = 1);
	char* getInput() { return input; };

	bool operator==(const char* text);
};