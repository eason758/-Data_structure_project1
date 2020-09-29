#pragma once
#ifndef _GAME_
#define _GAME_
#include <iostream>
#include "block.h"

using namespace std;

enum Error {
	OUT_OF_RANGE = 1,
	TOO_HIGH,
	STILL_TOO_HIGH,
	HRZT_HIT,

	CONSTRUCT_ERROR




};

class Game
{

	int row, col;
	bool **board;
	int height;

public:

	Game();
	~Game();
	inline int get_row() const {
		return row;
	}
	inline int get_col() const {
		return col;
	}
	inline bool pos(int r,int c) const{
		return board[r][c];
	}
	inline int get_height() const{
		return height;
	}
	bool& pos(int r, int c) {
		return board[r][c];
	}
	
	void block_down(Block* b);//block往下掉(大流程/介面)

	friend void debug(Game* g,Block*b) ;
	friend void error(Error e,Game* g, Block*b);

private:

	bool out_of_range(Block* b);//檢查左右有無超出
	bool occupied(Block*b,int i,int j);
	void hrzt_move(Block*b);


	void show_up(Block*b);
	void fall(Block*b);
	void set(Block*b);
	void set_height(Block* b);
	bool detect_line(Block*b);	//偵測有沒連線 //回傳連線幾條
	void remove(Block*b,int r);		//移除

};


Game::Game()
{
	cout << "game construct" << endl;
	cin >> row >> col;
	height = row-1;
	board = new bool*[row];
	if (!board) {
		cout << "board row establish not complete" << endl;
	}
	for (int i = 0; i < row; i++) {
		board[i] = new bool[col];
		if (!board[i]) {
			cout << "board col "<< i <<" establish not complete" << endl;
		}
		for (int j = 0; j < col ; j++) {
			board[i][j] = 0;
		}
	}
}

Game::~Game()
{
	cout << "game delete" << endl;
	for (int i = 0; i < row; i++) delete[]board[i];
	delete []board;
}


//大流程

//9/24助教解惑後:
//下落 - 著地or卡到方塊(包含碰到最上層) - 執行橫移 - (下落)-確定位置 - 消去 - 判定有無超出邊界
//最後位置確定後，先消除再看是否還有超出邊界
//橫移卡到算失敗
void Game::block_down(Block* b) {
	
	//左右out of range
	if (out_of_range(b)) 
		error(OUT_OF_RANGE, this, b);
	
	//完整的顯示進去board 如果不行就 too high!
	show_up(b);
	
	//掉下去 直到碰到底後左右移動+再下去
	fall(b);
	
	//occupy空間
	set(b);

	detect_line(b);

	debug(this, b);

	//其實可以寫直接撞下去 如果最後結果超出board 那就exit
}


//左右是否超出界線(包含預測橫移後)
bool Game::out_of_range(Block* b) {
	if (b->cell_loc(1).second + b->move_s < 0 || b->cell_loc(1).second + b->move_s >= col ||
		b->cell_loc(2).second + b->move_s < 0 || b->cell_loc(2).second + b->move_s >= col ||
		b->cell_loc(3).second + b->move_s < 0 || b->cell_loc(3).second + b->move_s >= col ||
		b->cell_loc(4).second + b->move_s < 0 || b->cell_loc(4).second + b->move_s >= col)
		return 1;
	else
		return 0;
}

//包含碰到要橫移(包含全部超出邊界依然碰到也橫移)
void Game::show_up(Block*b) {

	while (b->cell_loc(1).first < 0 || b->cell_loc(2).first < 0 ||
		b->cell_loc(4).first < 0 || b->cell_loc(3).first < 0)
	{
		if (occupied(b,1,0))	//下一格有撞到
		{

			if (b->move_s != 0) //還沒橫移過
			{
				hrzt_move(b);	//完成橫移
				continue;
			}
			else {				//已經橫移過
				height = 0;
				for (int k = 1; k <= 4; k++) {
					if (b->cell_loc(k).first >= 0)
						pos(b->cell_loc(k).first, b->cell_loc(k).second) = 1;
				}
				if (detect_line(b)) continue;//削掉後再判定一次

				error(STILL_TOO_HIGH, this, b);	//橫移過/削掉後還是太高
			}
		}

		b->ref_p.first += 1;	//如果能下降就下降
	}
}

//包含碰到要橫移
void Game::fall(Block*b) {

	while (!occupied(b,1,0))
		b->ref_p.first += 1;

	if (b->move_s != 0) {

		while (b->move_s != 0) {
			b->move();
			if (occupied(b,0,0))
			{
				cout << "block occupied!" << endl;
				set(b);
				debug(this, b);
				exit(1);
			}
			
		}
		fall(b);
	}
	

}

//設立方塊並計算高度
void Game::set(Block*b) {

	pos(b->cell_loc(1).first, b->cell_loc(1).second) = 1;
	pos(b->cell_loc(2).first, b->cell_loc(2).second) = 1;
	pos(b->cell_loc(3).first, b->cell_loc(3).second) = 1;
	pos(b->cell_loc(4).first, b->cell_loc(4).second) = 1;

	set_height(b);

}
void Game::set_height(Block*b) {
	if (b->highest_cell_loc().first < height) height = b->highest_cell_loc().first;
}

//偵測是否有連線且消除
bool Game::detect_line(Block*b) {
	bool flag = false;
	for (int i = height; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (!pos(i, j)) break;
			if (j == col - 1) {
				remove(b, i);
				flag = true;
			}
		}
	}
	return flag;
}
void Game::remove(Block* b, int r) {
	
	if (b->cell_loc(1).first < 0 || b->cell_loc(2).first < 0 ||		//還沒show_up的case
		b->cell_loc(4).first < 0 || b->cell_loc(3).first < 0) 
	{
		for (int k = 1; k <= 4; k++)
			if (b->cell_loc(k).first < r) b->cell(k).first += 1;	//讓方塊判定下降

		for (int i = r; i >= height; i--) {
			for (int j = 0; j < col; j++) {
				if (i == 0)  					//最上層
					pos(i, j) = 0;
				else
					pos(i, j) = pos(i - 1, j);
			}
		}

		for (int k = 1; k <= 4; k++) {
			if (b->cell_loc(k).first == 0)
				pos(b->cell_loc(k).first, b->cell_loc(k).second) = 1;		
			//該col上面還有未進去的block 讓他降下來
		}
	}
	else {											//已經fall的case
		for (int i = r; i >= height; i--) {
			for (int j = 0; j < col; j++) {
				if (i == 0)  					//最上層
					pos(i, j) = 0;
				else
					pos(i, j) = pos(i - 1, j);
			}
		}
	}
}



void Game::hrzt_move(Block* b) {

	while (b->move_s != 0) {
		b->move();
		if (occupied(b, 0, 0))
			error(HRZT_HIT,this,b);
	}
}

// i = offset of y ; j = offset of x
bool Game::occupied(Block*b, int i, int j) {

	if (b->cell_loc(1).first+i >= row || b->cell_loc(2).first+i >= row ||
		b->cell_loc(4).first+i >= row || b->cell_loc(3).first+i >= row   )
		return 1;

	if ((b->cell_loc(1).first + i >= 0 && pos(b->cell_loc(1).first + i, b->cell_loc(1).second + j)) ||
		(b->cell_loc(2).first + i >= 0 && pos(b->cell_loc(2).first + i, b->cell_loc(2).second + j)) ||
		(b->cell_loc(3).first + i >= 0 && pos(b->cell_loc(3).first + i, b->cell_loc(3).second + j)) ||
		(b->cell_loc(4).first + i >= 0 && pos(b->cell_loc(4).first + i, b->cell_loc(4).second + j))   )
		return 1;
	else return 0;
}

#endif 