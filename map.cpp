#include "map.h"
#include<cstdlib>
#include<ctime>
#include<windows.h>
#include<conio.h>
#pragma warning(disable : 4309)
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { short(x),short(y) };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

map::map() {
	this->status = 0;
	this->main_map = new int* [int(Hight)];
	for (int i = 0; i<int(Hight); i++) {
		this->main_map[i] = new int[Widght];
	}
	for (int i = 0; i<int(Hight); i++) {
		for (int j = 0; j<int(Widght); j++) {
			this->main_map[i][j] = 0;
		}
	}
}
map::~map(){}
void map::draw_map() {
	char a = 186;
	char b =207;
	char c = 209;
	char d = 206;
	int td = int(tungdo);
	int hd = int(hoanhdo);
	int rong = int(Widght);
	int dai = int(Hight);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);
	gotoxy(hoanhdo + 2, tungdo + 3);
	cout << "Designed by NXN";
	for (int i = hd; i < hd + rong + 2; i++) {
		if (i == hd || i == hd + rong + 1) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			gotoxy(i, td + 4);
			cout << d;
			//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		}
		else {
			gotoxy(i, td + 4);
			cout << c;
		}
	}
	for (int x = hd; x <= hd + rong+1; x++) {
		for (int y = td+5; y < td +dai-3; y++) {
			if (x == hd || x == hd+ rong+1) {
				gotoxy(x, y);
				cout << a;
			}
		}
	}
	for (int i = hd; i < hd + rong+2 ; i++) {
		if (i == hd || i == hd + rong + 1) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			gotoxy(i, dai+td - 3);
			cout << d;
			//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		}
		else {
			gotoxy(i, dai + td - 3);
			cout << b;
		}
	}
}
void map::inmap() {
	for (int i = 0; i < Hight; i++) {
		for (int j = 0; j < Widght; j++) {
			cout << this->main_map[i][j];
		}
		cout << endl;
	}
}
void map::update_block() {
	char a = 1;
	for (int i = 8; i < Hight; i++) {
		for (int j = 0; j < Widght; j++) {
			if (this->main_map[i][j] == 1) {
				gotoxy(j + hoanhdo + 1, i + tungdo + 1 - 4);
				
				cout << a;
				
			}
			else { 
				gotoxy(j + hoanhdo + 1, i + tungdo + 1 - 4);
				cout << " ";
			}
		}
	}
}
void map::xoahang(int hang) {
	for (int i = hang; i >0; i--) {
		for (int j = 0; j < Widght; j++) {
			this->main_map[i][j] = this->main_map[i -1][j];
		}
	}
}
//====================================
info::info() {
	this->level = 1;
	this->score = 0;
	this->speed = 0.4f;
	this->x2 = 0;
}
info::~info(){}
void info::display() {
	
	char b = 175;
	gotoxy(36, 17); cout << char(198);
	gotoxy(37, 9);
	cout << "Level: " << this->level;
	gotoxy(37, 10);
	cout << "Score: " << this->score;
	gotoxy(37, 11);
	cout << "Next block: ";
	gotoxy(37, 17);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	for (int i = 0; i < this->x2; i++) {
		cout << b;
		gotoxy(37 + i+1, 17);
	}
	if (this->x2 == 3) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		gotoxy(40, 17); cout << "BOM";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		gotoxy(40, 17); cout << "BOM";
	}
}
void info::update( ) {
	this->level++;
	this->speed -= 0.05f;
	this->score = 0;
}
void info::update2(short score) {
	this->score = score;
}
//=====================
str::str() {
	this->color = 0;
	this->s = " ";
	this->x = this->y = 0;
}
str::str(string s, int color, int x, int y) {
	this->color = color;
	this->s = s;
	this->x = x;
	this->y = y;
}
str::~str() {}
void str::show() {
	gotoxy(x, y);
	cout << this->s;
}
void str::delete_str() {
	for (int i = 0; i < this->s.length(); i++) {
		gotoxy(x + i, y);
		cout << " ";
	}
}
void str::update() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), this->color);
	gotoxy(x, y);
	cout << this->s;
}
//========class menu=================
menu::menu() {
	this->x = this->y = 0;
	this->mau = 0;
	this->status = 0;
}
menu::menu(string* p, int sl, int x, int y, int mau) {
	this->mau = mau;
	this->x = x;
	this->y = y;
	this->status = 0;
	for (int i = 0; i < sl; i++) {
		str* tmp = new str(p[i], this->mau, this->x, this->y + i);
		this->a.push_back(*tmp);
		delete tmp;
	}
}
void menu::show() {
	int index = 0;
	for (int i = 0; i < this->a.size(); i++) {
		a[i].show();
	}
	a[index].update();
	while (1) {
		if (_kbhit()) {
			char key = _getch();
			if (key == 's' || key == 'S') {
				if (index < this->a.size() - 1) {
					index++;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
					a[index].delete_str();
					for (int i = 0; i < this->a.size(); i++) {
						a[i].show();
					}

					a[index].update();

				}
			}
			else if (key == 'w' || key == 'W') {
				if (index > 0) {
					index--;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
					a[index].delete_str();
					for (int i = 0; i < this->a.size(); i++) {
						a[i].show();
					}
					a[index].update();
				}
			}
			else if (key == 'j') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				this->status = index;
				for (int i = 0; i < this->a.size(); i++) {
					this->a[i].delete_str();
				}
				//system("cls");

				break;
			}
		}
	}


}
menu::~menu() {}
int menu::return_menu() {
	return this->status;
}