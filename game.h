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
	
	void block_down(Block* b);//block���U��(�j�y�{/����)

	friend void debug(Game* g,Block*b) ;
	friend void error(Error e,Game* g, Block*b);

private:

	bool out_of_range(Block* b);//�ˬd���k���L�W�X
	bool occupied(Block*b,int i,int j);
	void hrzt_move(Block*b);


	void show_up(Block*b);
	void fall(Block*b);
	void set(Block*b);
	void set_height(Block* b);
	bool detect_line(Block*b);	//�������S�s�u //�^�ǳs�u�X��
	void remove(Block*b,int r);		//����

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


//�j�y�{

//9/24�U�иѴb��:
//�U�� - �ۦaor�d����(�]�t�I��̤W�h) - ���� - (�U��)-�T�w��m - ���h - �P�w���L�W�X���
//�̫��m�T�w��A�������A�ݬO�_�٦��W�X���
//��d��⥢��
void Game::block_down(Block* b) {
	
	//���kout of range
	if (out_of_range(b)) 
		error(OUT_OF_RANGE, this, b);
	
	//���㪺��ܶi�hboard �p�G����N too high!
	show_up(b);
	
	//���U�h ����I�쩳�ᥪ�k����+�A�U�h
	fall(b);
	
	//occupy�Ŷ�
	set(b);

	detect_line(b);

	debug(this, b);

	//���i�H�g�������U�h �p�G�̫ᵲ�G�W�Xboard ���Nexit
}


//���k�O�_�W�X�ɽu(�]�t�w�����)
bool Game::out_of_range(Block* b) {
	if (b->cell_loc(1).second + b->move_s < 0 || b->cell_loc(1).second + b->move_s >= col ||
		b->cell_loc(2).second + b->move_s < 0 || b->cell_loc(2).second + b->move_s >= col ||
		b->cell_loc(3).second + b->move_s < 0 || b->cell_loc(3).second + b->move_s >= col ||
		b->cell_loc(4).second + b->move_s < 0 || b->cell_loc(4).second + b->move_s >= col)
		return 1;
	else
		return 0;
}

//�]�t�I��n�(�]�t�����W�X��ɨ̵M�I��]�)
void Game::show_up(Block*b) {

	while (b->cell_loc(1).first < 0 || b->cell_loc(2).first < 0 ||
		b->cell_loc(4).first < 0 || b->cell_loc(3).first < 0)
	{
		if (occupied(b,1,0))	//�U�@�榳����
		{

			if (b->move_s != 0) //�٨S��L
			{
				hrzt_move(b);	//�����
				continue;
			}
			else {				//�w�g��L
				height = 0;
				for (int k = 1; k <= 4; k++) {
					if (b->cell_loc(k).first >= 0)
						pos(b->cell_loc(k).first, b->cell_loc(k).second) = 1;
				}
				if (detect_line(b)) continue;//�d����A�P�w�@��

				error(STILL_TOO_HIGH, this, b);	//��L/�d�����٬O�Ӱ�
			}
		}

		b->ref_p.first += 1;	//�p�G��U���N�U��
	}
}

//�]�t�I��n�
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

//�]�ߤ���íp�Ⱚ��
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

//�����O�_���s�u�B����
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
	
	if (b->cell_loc(1).first < 0 || b->cell_loc(2).first < 0 ||		//�٨Sshow_up��case
		b->cell_loc(4).first < 0 || b->cell_loc(3).first < 0) 
	{
		for (int k = 1; k <= 4; k++)
			if (b->cell_loc(k).first < r) b->cell(k).first += 1;	//������P�w�U��

		for (int i = r; i >= height; i--) {
			for (int j = 0; j < col; j++) {
				if (i == 0)  					//�̤W�h
					pos(i, j) = 0;
				else
					pos(i, j) = pos(i - 1, j);
			}
		}

		for (int k = 1; k <= 4; k++) {
			if (b->cell_loc(k).first == 0)
				pos(b->cell_loc(k).first, b->cell_loc(k).second) = 1;		
			//��col�W���٦����i�h��block ���L���U��
		}
	}
	else {											//�w�gfall��case
		for (int i = r; i >= height; i--) {
			for (int j = 0; j < col; j++) {
				if (i == 0)  					//�̤W�h
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