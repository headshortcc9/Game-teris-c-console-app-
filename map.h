#include<iostream>
using namespace std;
#include<vector>
#include<windows.h>
void gotoxy(int x, int y);
enum thongso {
	tungdo =4,
	hoanhdo=16,
	Hight =30,
	Widght=16
};

class map
{
public:
	int status;
	int** main_map;
	map();
	~map();
	void draw_map();
	void update_block();
	void inmap();
	void xoahang(int hang);
};
class info {
	
	
public:
	short score;
	short level;
	float speed;
	short x2;
	info();
	~info();
	void update( );
	void display();
	void update2(short score);
};
class str {
public:
	string s;
	int color;
	int x, y;
	str();
	str(string s, int color, int x, int y);
	~str();
	void show();
	void delete_str();
	void update();
};
class menu
{

public:
	vector<str> a;
	int status;
	int x, y, mau;
	menu();
	menu(string* p, int sl, int x, int y, int mau);
	~menu();
	void show();
	int return_menu();

};
