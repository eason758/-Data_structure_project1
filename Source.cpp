#include <iostream>
#include <string>
#include "func.h"
#include "game.h"
#include "block.h"
using namespace std;

void play(Game& g);		//收testcase且計算
void game_final(Game& g);	//將結果顯示出來

Block* get_block_type(string op, int r, int m);


int main() {

	Game g;		//including game init(set row/col)
	play(g);
	game_final(g);

	return 0;
}

void play(Game& g) {
	
	
	while (1) {
		string op;
		cin >> op;
		if (op == "End") break;
		
		int r, m;
		cin >> r >> m;
		
		Block* b = get_block_type(op,r,m);
		g.block_down(b);

	}
}

void game_final(Game& g) {

	for (int i = 0; i < g.get_row(); i++) {
		for (int j = 0; j < g.get_col(); j++) {
			cout <<" "<< g.pos(i,j);
		}
		cout << " \n";
	}
}

Block* get_block_type(string op, int r, int m) {
	r--;
	if (op == "I1")
	{
		return new I1(r, m);
	}
	else if (op == "I2")
	{
		return new I2(r, m);
	}
	else if (op == "T1")
	{
		return new T1(r, m);
	}
	else if (op == "T2")
	{
		return new T2(r, m);
	}
	else if (op == "T3")
	{
		return new T3(r, m);
	}
	else if (op == "T4")
	{
		return new T4(r, m);
	}
	else if (op == "L1")
	{
		return new L1(r, m);
	}
	else if (op == "L2")
	{
		return new L2(r, m);
	}
	else if (op == "L3")
	{
		return new L3(r, m);
	}
	else if (op == "L4")
	{
		return new L4(r, m);
	}
	else if (op == "J1")
	{
		return new J1(r, m);
	}
	else if (op == "J2")
	{
		return new J2(r, m);
	}
	else if (op == "J3")
	{
		return new J3(r, m);
	}
	else if (op == "J4")
	{
		return new J4(r, m);
	}
	else if (op == "S1")
	{
		return new S1(r, m);
	}
	else if (op == "S2")
	{
		return new S2(r, m);
	}
	else if (op == "Z1")
	{
		return new Z1(r, m);
	}
	else if (op == "Z2")
	{
		return new Z2(r, m);
	}
	else if (op == "O")
	{
		return new O(r, m);
	}
	else { cout << "wrong block imfo" << endl; exit(1); }
}
