#pragma once
#ifndef _FUNC_
#define _FUNC_
#include "game.h"




//debug用 顯示每一步的結果
void debug(Game* g, Block*b) {
	for (int i = 0; i < g->row; i++) {
		for (int j = 0; j < g->col; j++) {
			cout << " " << g->pos(i, j);
		}
		cout << " \n";
	}
}

//error用 顯示哪裡出錯
void error(Error e, Game* g, Block* b) {
	switch (e)
	{
	case 1:
		cout << "\nOut of range!" << endl;
		break;
	case 2:
		cout << "\nToo high!" << endl;
		break;
	case 3:
		cout << "\nAfter horizontally moving or reducing blocks,"
				"still too high!" << endl;
		break;
	case 4:

		break;

	case 5:

		break;

	case 6:

		break;

	default:
		cout << "Other error" << endl;
	}
	debug(g, b);
	exit(1);
}

#endif 