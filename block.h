#pragma once
#ifndef _BLOCK_
#define _BLOCK_
#include <iostream>
using namespace std;

class Block
{
protected:
	pair<int,int> ref_p;
	int move_s;

	pair<int, int> cell1;
	pair<int, int> cell2;
	pair<int, int> cell3;
	pair<int, int> cell4;


public:
	pair<int, int> cell_loc(int n);
	pair<int, int> highest_cell_loc();
	friend class Game;
	virtual void set_cells() = 0;
	void move() {

		if (move_s > 0) {
			move_s--;
			cell1.second += 1;
			cell2.second += 1;
			cell3.second += 1;
			cell4.second += 1;
		}
		else if (move_s < 0)
		{
			move_s++;
			cell1.second -= 1;
			cell2.second -= 1;
			cell3.second -= 1;
			cell4.second -= 1;
		}
	};

};

pair<int, int> Block::cell_loc(int n) {
	switch (n)
	{
	case 1:
		return make_pair(cell1.first + ref_p.first, cell1.second+ ref_p.second);
	case 2:
		return make_pair(cell2.first + ref_p.first, cell2.second + ref_p.second);
	case 3:
		return make_pair(cell3.first + ref_p.first, cell3.second + ref_p.second);
	case 4:
		return make_pair(cell4.first + ref_p.first, cell4.second + ref_p.second);
	default:
		cout << "not that many cells" << endl;
		exit(1);
	}
}

pair<int, int> Block::highest_cell_loc() {
	if (cell1.first <= cell2.first && cell1.first <= cell3.first && cell1.first <= cell4.first)
		return make_pair(cell1.first + ref_p.first, cell1.second + ref_p.second);
	else if (cell2.first <= cell1.first && cell2.first <= cell3.first && cell2.first <= cell4.first)
		return make_pair(cell2.first + ref_p.first, cell2.second + ref_p.second);
	else if (cell3.first <= cell1.first && cell3.first <= cell2.first && cell3.first <= cell4.first)
		return make_pair(cell3.first + ref_p.first, cell3.second + ref_p.second);
	else if (cell4.first <= cell1.first && cell4.first <= cell2.first && cell4.first <= cell3.first)
		return make_pair(cell4.first + ref_p.first, cell4.second + ref_p.second);
	else {
		cout << "no highest cell???" << endl;
		exit(1);
	}
}

class S1 :public Block
	{
	public:
		S1(int r, int m) {
			set_cells();
			ref_p = make_pair(0,r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(0, 0);
			cell2 = make_pair(0, 1);
			cell3 = make_pair(-1, 1);
			cell4 = make_pair(-1, 2);
		}
	};

class S2 :public Block
	{
	public:
		S2(int r, int m) {
			set_cells();
			ref_p = make_pair(0, r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(-1, 1);
			cell2 = make_pair(0, 1);
			cell3 = make_pair(-1, 0);
			cell4 = make_pair(-2, 0);
		}
	};

class Z1 :public Block
	{
	public:
		Z1(int r, int m) {
			set_cells();
			ref_p = make_pair(0, r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(-1, 0);
			cell2 = make_pair(0, 2);
			cell3 = make_pair(0, 1);
			cell4 =  make_pair(-1, 1);
		}
	};

class Z2 :public Block
	{
	public:
		Z2(int r, int m) {
			set_cells();
			ref_p = make_pair(0, r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(0, 0);
			cell2 = make_pair(-1, 0);
			cell3 = make_pair(-1, 1);
			cell4 = make_pair(-2, 1);
		}
	};

class L1 :public Block
	{
	public:
		L1(int r, int m) {
			set_cells();
			ref_p = make_pair(0, r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(0, 0);
			cell2 = make_pair(0, 1);
			cell3 = make_pair(-1, 0);
			cell4 = make_pair(-2, 0);
		}
	};

class L2 :public Block
	{
	public:
		L2(int r, int m) {
			set_cells();
			ref_p = make_pair(0, r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(0, 0);
			cell2 = make_pair(-1, 0);
			cell3 = make_pair(-1, 1);
			cell4 = make_pair(-1, 2);
		}
	};

class L3 :public Block
	{
	public:
		L3(int r, int m) {
			set_cells();
			ref_p = make_pair(0, r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(-2, 0);
			cell2 = make_pair(0, 1);
			cell3 = make_pair(-1, 1);
			cell4 = make_pair(-2, 1);
		}
	};

class L4 :public Block
	{
	public:
		L4(int r, int m) {
			set_cells();
			ref_p = make_pair(0, r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(0, 0);
			cell2 = make_pair(0, 1);
			cell3 = make_pair(0, 2);
			cell4 = make_pair(-1, 2);
		}
	};

class J1 :public Block
	{
	public:
		J1(int r, int m) {
			set_cells();
			ref_p = make_pair(0, r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(0, 1);
			cell2 = make_pair(-1, 1);
			cell3 = make_pair(0, 0);
			cell4 = make_pair(-2, 1);
		}
	};

class J2 :public Block
	{
	public:
		J2(int r, int m) {
			set_cells();
			ref_p = make_pair(0, r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(0, 0);
			cell2 = make_pair(0, 1);
			cell3 = make_pair(0, 2);
			cell4 = make_pair(-1, 0);
		}
	};

class J3 :public Block
	{
	public:
		J3(int r, int m) {
			set_cells();
			ref_p = make_pair(0, r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(0, 0);
			cell2 = make_pair(-1, 0);
			cell3 = make_pair(-2, 0);
			cell4 = make_pair(-2, 1);
		}
	};

class J4 :public Block
	{
	public:
		J4(int r, int m) {
			set_cells();
			ref_p = make_pair(0, r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(-1, 0);
			cell2 = make_pair(0, 2);
			cell3 = make_pair(-1, 1);
			cell4 = make_pair(-1, 2);
		}
	};

class T1 :public Block
	{
	public:
		T1(int r, int m) {
			set_cells();
			ref_p = make_pair(0, r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(0, 1);
			cell2 = make_pair(-1, 1);
			cell3 = make_pair(-1, 2);
			cell4 = make_pair(-1, 0);
		}
	};

class T2 :public Block
	{
	public:
		T2(int r, int m) {
			set_cells();
			ref_p = make_pair(0, r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(0, 1);
			cell2 = make_pair(-1, 1);
			cell3 = make_pair(-1, 0);
			cell4 = make_pair(-2, 1);
		}
	};

class T3 :public Block
	{
	public:
		T3(int r, int m) {
			set_cells();
			ref_p = make_pair(0, r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(0, 0);
			cell2 = make_pair(0, 2);
			cell3 = make_pair(0, 1);
			cell4 = make_pair(-1, 1);
		}
	};

class T4 :public Block
	{
	public:
		T4(int r, int m) {
			set_cells();
			ref_p = make_pair(0, r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(0, 0);
			cell2 = make_pair(-1, 0);
			cell3 = make_pair(-1, 1);
			cell4 = make_pair(-2, 0);
		}
	};

class I1 :public Block
	{
	public:
		I1(int r, int m) {
			set_cells();
			ref_p = make_pair(0, r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(0, 0);
			cell2 = make_pair(-1, 0);
			cell3 = make_pair(-2, 0);
			cell4 = make_pair(-3, 0);
		}
	};

class I2 :public Block
	{
	public:
		I2(int r, int m) {
			set_cells();
			ref_p = make_pair(0, r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(0, 0);
			cell2 = make_pair(0, 1);
			cell3 = make_pair(0, 2);
			cell4 = make_pair(0, 3);
		}
	};

class O :public Block
	{
	public:
		O(int r, int m) {
			set_cells();
			ref_p = make_pair(0, r);
			move_s = m;
		}
	private:
		void set_cells() {
			cell1 = make_pair(0, 0);
			cell2 = make_pair(0, 1);
			cell3 = make_pair(-1, 1);
			cell4 = make_pair(-1, 0);
		}
	};

#endif
