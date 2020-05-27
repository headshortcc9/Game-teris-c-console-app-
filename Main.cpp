#include"block.h"
#include<time.h>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#pragma warning(disable : 4244)
int Loai()
{
	srand(time(NULL));
	int x = rand() % 7;
	switch (x)
	{
	case 0:
		return 15;
		break;
	case 1:
		return 31;
		break;
	case 2:
		return 51;
		break;
	case 3:
		return 30;
		break;
	case 4:
		return 58;
		break;
	case 5:
		return 57;
		break;
	case 6:
		return 60; break;
	default: return 0; break;
	}
	
}
int free_row(map *m) {
	for (int i = 5; i < Hight - 1; i++) {
		for (int j = 0; j < Widght; j++) {
			if (m->main_map[i][j] == 1) return i;
		}
	}
	return 1;
}
void Draw_block(block*gach) {
	gach->draw_block();
}
block* create(int id) {
	block* g = new block(id);
	return g;
}
int rise(map* m) {
	for (int i = 0; i < Widght; i++) {
		if (m->main_map[5][i] == 1) return 1;
	}
	for (int i =5; i <int(Hight)-1 ; i++) {
		for (int j = 0; j < Widght; j++) {
			m->main_map[i][j] = m->main_map[i + 1][j];
		}
	}
	for (int i= 0; i < Widght; i++) {
		int x = rand() % 2;
		m->main_map[29][i] = x;
	}
	return 0;
}
void Draw_next(int id) {
	block* p = new block(id);
	char a = 1;
	int ii = int(hoanhdo) + Widght + 7;
	for (int i = 0; i < p->row; i++) {
		for (int j = 0; j < p->colum; j++) {
			if (p->arr[i][j] == 1)
			{
				gotoxy(ii + j, int(tungdo) + i + 9);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << a;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			}
		}
	}
}
void delete_tmp() {
	int ii = int(hoanhdo) + Widght + 7;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			gotoxy(ii + j, int(tungdo) + i + 9);
			cout << " ";
		}
	}
}
int check(block* p,map* m,info* i4) {
	if (i4->x2 >= 3) {
		block* p = new block(100);
		do {
			p->draw_block();
			Sleep(400);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			m->update_block();
			p->cls();
			
			if (_kbhit()) {
				char k = _getch();
				if (k == 'w' || k == 'W') {
					int k1 = 2;
					do {
						m->xoahang(p->yMap + k1);
						k1--;
					} while (k1 >= 0);
					i4->x2 = 0;
					gotoxy(37, 17);
					cout << "           ";
					m->status = 0;
					break;
				}
				else if (k == 'p' || k == 'P') {
					p->draw_block();
					gotoxy(40, 31);
					system("pause");
				}
				else if (k == 'x') m->status = 10;
			}
			p->yMap++;
		} while (p->yMap<28);
		if (p->yMap == 28) {
			int l =2;
			do {
				m->xoahang(29);
				l--;
			} while (l >= 0);
			gotoxy(37, 17);
			cout << "           ";
			m->status = 0;
			i4->x2 = 0;
		}
	}
	else {
		int status2 = 0;
		static int dem = 0;
		int dem1 = 0;
		if (i4->level > 1) {
			dem++;
		}
		int count = 0;
		if (p->yMap <= 6||m->status==10) return 1;
		if ((dem == 4 && i4->level == 2) || (dem == 3 && i4->level == 3) || (dem == 2 && i4->level == 4) || (dem == 1 && i4->level == 5)) {
			int i = p->row - 1;
			do {
				count = 0;
				for (int j = 0; j < Widght; j++) {
					if (m->main_map[p->yMap + i][j] == 1) count++;
				}
				if (count == Widght) {
					if (i4->score >= 900) {
						i4->update();
						dem = 0;
						goto go2;
					}
					i4->update2(i4->score += 100);
				go2:
					m->xoahang(p->yMap + i);
					m->update_block();
					dem1++;
				}
				else {
					i--;
				}
			} while (i >= 0);
			int aaa = rise(m);
			if (aaa == 1) return 1;
			status2 = 1;
		}
		if ((dem == 4&&i4->level==2)|| (dem == 3 && i4->level == 3)|| (dem == 2 && i4->level == 4)||(dem == 1 && i4->level == 5)) dem = 0;
		if (status2 == 0) {
			int i = p->row - 1;
			do {
				count = 0;
				for (int j = 0; j < Widght; j++) {
					if (m->main_map[p->yMap + i][j] == 1) count++;
				}
				if (count == Widght) {
					if (i4->score >= 900) {
						i4->update();
						goto go1;
					}
					i4->update2(i4->score += 100);
				go1:
					m->xoahang(p->yMap + i);
					m->update_block();
					dem1++;
				}
				else {
					i--;
				}
			} while (i >= 0);
			status2 = 0;
		}
		if (dem1 >= 2) {
			i4->x2++;
		}
	}
	return -1;
}
int main() {
	int lc3;
	while (1) {
		system("cls");
		gotoxy(34, 12);
		cout << "WELCOM TO TETRIS GAME";
		gotoxy(18, 18);
		cout << "Press 'S' to move down,'W' ot move up and 'J' to choose";
		string a[] = { "Start game","Guide play","   Exit" };
		menu* me = new menu(a, 3, 39, 14, 21);
		me->show();
		lc3 = me->status+1;
		if (lc3 == 1) {
			system("cls");
			int LC = 1;
			do {
				clock_t start, end;
				map* p = new map();
				info* inf = new info();
				p->draw_map();
				block* tmp = new block(Loai());
				int idnext = Loai();
				while (1) {
					if (p->status == 0) {
						inf->display();
						tmp->draw_block();
						delete_tmp();
						Draw_next(idnext);
						start = clock();
						do {
							if (_kbhit()) {
								tmp->cls();
								char key = _getch();
								if (key == 'w' || key == 'W') {
									if (tmp->yMap > 3) {
										tmp->xoay();
									}
								}
								else if (key == 'a' || key == 'A') {
									tmp->move_left(p->main_map);
								}
								else if (key == 'd' || key == 'D') {
									tmp->move_right(p->main_map);
								}
								else if (key == 's' || key == 'S') {
									tmp->move(p->main_map);
								}
								else if (key == 'p' || key == 'P') {
									tmp->draw_block();
									gotoxy(40, 31);
									system("pause");
								}
								else if (key == 'x') p->status = 10;
								tmp->draw_block();
								//break;
							}
							end = clock();
						} while (float(end - start) / CLK_TCK < inf->speed);
						tmp->cls();
					}
					if (tmp->move(p->main_map) == 0) {
						int idtmp = idnext;
						if (p->status == 0) {
							tmp->update(p->main_map);
						}
						int kq = check(tmp, p, inf);
						if (inf->x2 >= 4) {
							p->status = 1;
							inf->display();
						}
						if (kq == 1 || kq == 0 || (inf->score >= 1000 && inf->level == 5)) {
							if (inf->score >= 100 && inf->level == 1) {
								inf->display();
							}
							delete_tmp();
							gotoxy(37, 18);
							if (kq == 1) {
								cout << "Game over!!!";
							}
							else {
								cout << "You win!!!";
							}
							int lc7;
							string ss[] = { "Restart","Exit" };
							menu* mn = new menu(ss, 2, 37, 19, 22);
							mn->show();
							lc7 = mn->status;
							if (lc7 == 0) {
								gotoxy(37, 18);
								cout << "            ";
								gotoxy(37, 19); cout << "            ";
								gotoxy(37, 20); cout << "          ";
								for (int i = 0; i<int(Hight); i++) {
									for (int j = 0; j<int(Widght); j++) {
										p->main_map[i][j] = 0;
									}
								}
								p->update_block();
								inf->level = 1;
								inf->score = 0;
								inf->speed = 0.4f;
								p->status = 0;
								inf->x2 = 0;
								gotoxy(37, 17);
								cout << "          ";
							}
							else {
								LC = 0;
								break;
							}
						}
						tmp = create(idnext);
						if (idtmp == 15) {
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
						}
						else if (idtmp == 31) {
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
						}
						else {
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
						}
						p->update_block();
						idnext = Loai();

					}
				}
			} while (LC == 1);
		}
		else if (lc3 == 2) {
		system("cls");
		gotoxy(25, 12);
		cout << "Press 'A' to move left";
		gotoxy(25, 13);
		cout << "Press 'D' to move right";
		gotoxy(25, 14);
		cout << "Press 'S' to move down";
		gotoxy(25, 15);
		cout << "Press 'W' to move up or Rotate blocks of bricks or Stop the BOM";
		gotoxy(25, 16);
		cout << "Press 'X' to exit the game while playing and 'P' to pause the game";
		gotoxy(0, 17);
		cout << "Every time you cancel two consecutive lines, you will receive a charge of energy.";
		gotoxy(0, 18);
		cout << "If all 3 are accumulated you will get a bomb (the bomb will erase three rows in its place) ";
		system("Pause");
		}
		else { system("cls"); break; }
	}
	
	gotoxy(50, 30);
	return 0;
}