#pragma once
#ifndef _GAME_
#define _GAME_
#include <iostream>
#include "block.h"
using namespace std;
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
	
	void block_down(Block* b);//block���U��(�j�y�{)

	friend void debug(Game* g,Block*b) ;

private:

	bool out_of_range(Block* b);//�ˬd���k���L�W�X
	void show_up(Block*b);
	void fall(Block*b);
	void set(Block*b);
	void set_height(Block* b);
	void detect_line(Block*b);	//�������S�s�u
	void remove(Block*b,int r);		//����

};

Game::Game()
{
	cout << "game construct" << endl;
	cin >> row >> col;
	height = row;
	board = new bool*[row+1];
	if (!board) {
		cout << "board row establish not complete" << endl;
		exit(1);
	}
	for (int i = 0; i <= row; i++) {
		board[i] = new bool[col+1];
		if (!board[i]) {
			cout << "board col "<< i <<" establish not complete" << endl;
			exit(1);
		}
		for (int j = 0; j <= col ; j++) {
			board[i][j] = 0;
		}
	}
}

Game::~Game()
{
	cout << "game delete" << endl;
	for (int i = 0; i <= row; i++) delete[]board[i];
	delete []board;
}


//�j�y�{
void Game::block_down(Block* b) {
	
	//���kout of range
	if (out_of_range(b)) 
	{
		cout << "out of range!" << endl;
		debug(this, b);
		exit(1);
	}
	
	//���㪺��{�X�� �p�G����N too high!
	show_up(b);
	
	//���U�h ����I�쩳
	fall(b);
	
	//occupy�Ŷ�
	set(b);

	detect_line(b);

	debug(this, b);

	//���i�H�g�������U�h �p�G�̫ᵲ�G�W�Xboard ���Nexit
}


//���k�O�_�W�X�ɽu(�]�t�w�����ʫ�)
bool Game::out_of_range(Block* b) {
	if (b->cell_loc(1).second + b->move_s <= 0 || b->cell_loc(1).second + b->move_s > col ||
		b->cell_loc(2).second + b->move_s <= 0 || b->cell_loc(2).second + b->move_s > col ||
		b->cell_loc(3).second + b->move_s <= 0 || b->cell_loc(3).second + b->move_s > col ||
		b->cell_loc(4).second + b->move_s <= 0 || b->cell_loc(4).second + b->move_s > col)
		return 1;
	else
		return 0;
}

//�]�t�I��n�(�]�t�����W�X��ɨ̵M�I��]�)
void Game::show_up(Block*b) {

	while (b->cell_loc(1).first <= 0 || b->cell_loc(2).first <= 0 ||
		b->cell_loc(4).first <= 0 || b->cell_loc(3).first <= 0)
	{

		if ((b->cell_loc(1).first > 0 && pos(b->cell_loc(1).first + 1, b->cell_loc(1).second)) ||
			(b->cell_loc(2).first > 0 && pos(b->cell_loc(2).first + 1, b->cell_loc(2).second)) ||
			(b->cell_loc(3).first > 0 && pos(b->cell_loc(3).first + 1, b->cell_loc(3).second)) ||
			(b->cell_loc(4).first > 0 && pos(b->cell_loc(4).first + 1, b->cell_loc(4).second)))
		{
			if (b->move_s != 0) {

				while (b->move_s != 0) {
					b->move();
					if ((b->cell_loc(1).first > 0 && pos(b->cell_loc(1).first, b->cell_loc(1).second)) ||
						(b->cell_loc(2).first > 0 && pos(b->cell_loc(2).first, b->cell_loc(2).second)) ||
						(b->cell_loc(3).first > 0 && pos(b->cell_loc(3).first, b->cell_loc(3).second)) ||
						(b->cell_loc(4).first > 0 && pos(b->cell_loc(4).first, b->cell_loc(4).second)))
					{
						cout << "too high1!" << endl;
						set(b);
						debug(this, b);
						exit(1);
					}
				}
				continue;
			}
			else{
				cout << "too high2!" << endl;
				set(b);
				debug(this, b);
				exit(1);
			}
		}
		b->ref_p.first += 1;
	}

}

//�]�t�I��n�
void Game::fall(Block*b) {

	while (b->cell_loc(1).first + 1 <= row && b->cell_loc(2).first + 1 <= row &&
		b->cell_loc(4).first + 1 <= row && b->cell_loc(3).first + 1 <= row &&
		!pos(b->cell_loc(1).first + 1, b->cell_loc(1).second) &&
		!pos(b->cell_loc(2).first + 1, b->cell_loc(2).second) &&
		!pos(b->cell_loc(3).first + 1, b->cell_loc(3).second) &&
		!pos(b->cell_loc(4).first + 1, b->cell_loc(4).second))
	{
		b->ref_p.first += 1;
	}
	if (b->move_s != 0) {

		while (b->move_s != 0) {
			b->move();
			if ((b->cell_loc(1).first > 0 && pos(b->cell_loc(1).first, b->cell_loc(1).second)) ||
				(b->cell_loc(2).first > 0 && pos(b->cell_loc(2).first, b->cell_loc(2).second)) ||
				(b->cell_loc(3).first > 0 && pos(b->cell_loc(3).first, b->cell_loc(3).second)) ||
				(b->cell_loc(4).first > 0 && pos(b->cell_loc(4).first, b->cell_loc(4).second)))
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

//�]�ߤ���íp�Ⱚ��
void Game::set(Block*b) {

	pos(b->cell_loc(1).first, b->cell_loc(1).second) = 1;
	pos(b->cell_loc(2).first, b->cell_loc(2).second) = 1;
	pos(b->cell_loc(3).first, b->cell_loc(3).second) = 1;
	pos(b->cell_loc(4).first, b->cell_loc(4).second) = 1;

	set_height(b);

}
void Game::set_height(Block*b) {
	if (b->cell_loc(4).first < height) height = b->cell_loc(4).first;
}

//�����O�_���s�u�B����
void Game::detect_line(Block*b) {

	for (int i = height; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			if (!pos(i, j)) break;
			if(j == col) remove(b, i);
		}
	}

}
void Game::remove(Block*b, int r) {

	for (int i = r; i >= height; i--) {
		for (int j = 1; j <= col; j++) {
			pos(i, j) = pos(i-1, j);
		}
	}

}

#endif 