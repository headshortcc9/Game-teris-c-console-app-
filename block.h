#include"map.h"
class block {
public:
	int** arr;
	int colum, row;
	int xMap, yMap;
	block();
	block(int id);
	~block();
	void draw_block();
	void cls();
	void xoay();
	int move_left(int **map);
	int move_right(int **map);
	void update(int **map);
	int move(int **map);
};


