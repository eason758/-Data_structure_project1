#pragma once
#ifndef _FUNC_
#define _FUNC_
#include "game.h"

//debug¥Î
void debug(Game* g, Block*b) {
	for (int i = 0; i < g->row; i++) {
		for (int j = 0; j < g->col; j++) {
			cout << " " << g->pos(i, j);
		}
		cout << " \n";
	}
}
#endif 