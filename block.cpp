#include "block.h"
#include<cstdlib>
#include<ctime>
#pragma warning(disable : 6386)
block::block() {
	this->arr = new int* [this->row];
	for (int i = 0; i < this->row; i++) {
		arr[i] = new int[this->colum];
	}
	this->colum = 0;
	this->row = 0;
	this->xMap = 0;
	this->yMap = 0;
}
block::block(int id) {
	if (id == 31) {
		this->colum = this->row = 2;
		this->xMap = 6;
		this->yMap = 6;
	}
	else if (id == 15) {
		this->row = 4;
		this->colum = 1;
		this->xMap = 6;
		this->yMap = 5;
	}
	else if (id==100) {
		this->row = 3;
		this->colum = 3;
		this->xMap = 6;
		this->yMap = 5;
	}
	else {
		this->row = 2;
		this->colum = 3;
		this->xMap = 6;
		this->yMap = 6;
	}
	if (id == 100) {
		this->arr = new int* [this->row];
		for (int i = 0; i < this->row; i++) {
			arr[i] = new int[this->colum];
		}
		this->arr[0][0] = 0;
		this->arr[0][1] = 1;
		this->arr[0][2] = 0;
		this->arr[1][0] = 1;
		this->arr[1][1] = 1;
		this->arr[1][2] = 1;
		this->arr[2][0] = 0;
		this->arr[2][1] = 1;
		this->arr[2][2] = 0;
	}
	else {
		this->arr = new int* [this->row];
		for (int i = 0; i < this->row; i++) {
			arr[i] = new int[this->colum];
		}
		for (int k = 0; k < this->colum * this->row; k++)
		{
			this->arr[k / this->colum][k % this->colum] = (id >> (this->colum * this->row - 1 - k)) & 1;
		}
	}
}
block::~block(){}
void block::draw_block() {
	char a = 2;
	for (int i = 0; i < this->row; i++)
		for (int j = 0; j < this->colum; j++)
			if (this->arr[i][j] == 1 && (this->yMap + i) > 7)
			{
				gotoxy(int(hoanhdo) + this->xMap + j+1 , int(tungdo) + this->yMap + i -3);
				if ((this->colum == 2 && this->row == 3)|| (this->colum == 3 && this->row == 2)) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					cout << a;
				}
				else if (this->colum == 2 && this->row == 2) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
					cout << a;
				}
				else if (this->colum == 3 && this->row == 3) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout << a;
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << a;
				}
			}
}
void block::cls() {
	char a = ' ';
	int i;
	int j;
	for (i = 0; i < this->row; i++)
		for (j = 0; j < this->colum; j++)
			if (this->arr[i][j] == 1 && (this->yMap + i) > 7)
			{
				gotoxy(int(hoanhdo) + this->xMap + j+ 1, int(tungdo) + this->yMap + i - 3);
				cout << a;

			}
}
void block::xoay() {
	int a = this->colum;
	int b = this->row;
	if (this->xMap <= 13) {
		int** kq = new int* [a];
		for (int i = 0; i < a; i++) {
			kq[i] = new int[b];
		}
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < b; j++) {
				kq[i][j] = this->arr[b - 1 - j][i];
			}
		}

		this->colum = b;
		this->row = a;
		this->arr = kq;
	}
	else {
		if (this->colum == 2) {
			this->xMap -= 1;
			int** kq = new int* [a];
			for (int i = 0; i < a; i++) {
				kq[i] = new int[b];
			}
			for (int i = 0; i < a; i++) {
				for (int j = 0; j < b; j++) {
					kq[i][j] = this->arr[b - 1 - j][i];
				}
			}
			this->colum = b;
			this->row = a;
			this->arr = kq;
		}
		else if (this->colum == 3) {
			int** kq = new int* [a];
			for (int i = 0; i < a; i++) {
				kq[i] = new int[b];
			}
			for (int i = 0; i < a; i++) {
				for (int j = 0; j < b; j++) {
					kq[i][j] = this->arr[b - 1 - j][i];
				}
			}
			this->colum = b;
			this->row = a;
			this->arr = kq;
		}
		else if (this->colum == 1) {
			this->xMap -= 3;
			int** kq = new int* [a];
			for (int i = 0; i < a; i++) {
				kq[i] = new int[b];
			}
			for (int i = 0; i < a; i++) {
				for (int j = 0; j < b; j++) {
					kq[i][j] = this->arr[b - 1 - j][i];
				}
			}
			this->colum = b;
			this->row = a;
			this->arr = kq;
		}
		
		
	}
}
void block::update(int **map) {
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->colum; j++) {
			if (this->arr[i][j] == 1) {
				map[this->yMap + i][this->xMap + j] = 1;
			}
		}
	}
	
}
int is_inside(int i, int j) {
	return (i>=0 && i < int(Hight)&& j >=0 && j < int(Widght));
}
int is_down(int i, int j,int **map) {
	if (i<int(Hight)-1&&is_inside(i, j)==1 && map[i+1][j] == 0) return 1;
	else return 0;
}
int is_left(int i, int j, int** map) {
	if (j>0&&is_inside(i, j) && map[i][j-1] == 0) return 1;
	else return 0;
}
int is_right(int i, int j, int** map) {
	if (j<Widght&&is_inside(i, j) && map[i][j + 1] == 0) return 1;
	else return 0;
}
int block::move(int **map) {
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->colum; j++) {
			if (this->arr[i][j] == 1) {
				if (is_down(this->yMap + i, this->xMap + j, map) == 0) {
					return 0;
				}
			}
		}
	}
	this->yMap++;
	return 1;
}
int block::move_left(int** map) {
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->colum; j++) {
			if (this->arr[i][j] == 1) {
				if (is_left(this->yMap + i , this->xMap + j, map) == 0 || this->yMap <= 3) {
					return 0;
				}
			}
		}
	}
	this->xMap--;
	return 1;
}
int block::move_right(int** map) {
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->colum; j++) {
			if (this->arr[i][j] == 1) {
				if (is_right(this->yMap + i, this->xMap + j, map) == 0||this->yMap<=3) {
					return 0;
				}
			}
		}
	}
	this->xMap++;
	return 1;
}