#pragma once

class Window
{
protected:
	int x, y, width, height;
	int indexY = y;
	int color, bgColor, borderColor;
	char buf[6];
	int active;
	int selectColor, selectBgColor;
	int first;
public:
	Window();
	Window(Window& win);
	void Move(int _x, int _y);
	int GetColor() { return color; }
	int GetBgColor() { return bgColor; }
	int GetSelectColor() { return selectColor; }
	int GetSelectBgColor() { return selectBgColor; }
	void SetColor(int c);
	void SetBgColor(int c);
	void SetSelectColor(int c) { selectColor = c; }
	void SetSelectBgColor(int c) { selectBgColor = c; };
	void SetBorderColor(int c);

	int GetX() { return x; }
	int GetY() { return y; }
	void SetY(int _y) { y = _y; }
	int GetIndexY() { return indexY; }
	void SetIndexY(int _y) { indexY = _y; }

	int GetWidth() { return width; }
	int GetHeight() { return height; }
	void SetWidth(int w);
	void SetHeight(int h);

	void Show();
	Window& Center(int x, int y);
	int Select();
	int GetCount() { return 16; }
	void DrawItem(int row, int index);
	Window& Write(int _x, int _y, const char* str);
	void writeText(int _y, const char* str);
	int GetSelect() { return active; };

	void clear();
	Window* createWindow(int width, int height);
};