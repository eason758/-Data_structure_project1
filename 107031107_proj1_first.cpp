#include <iostream>
#include <string>
#include <fstream>

using namespace std;

ifstream f;
ofstream o("107031107_proj1.final", ios::out);

//大流程
//9/24助教解惑後:
//下落 - 著地or卡到方塊(包含碰到最上層) - 執行橫移 - (下落)-確定位置 - 消去 - 判定有無超出邊界
//最後位置確定後，先消除再看是否還有超出邊界
//橫移卡到算失敗


enum E {
	OUT_OF_RANGE = 1,
	TOO_HIGH,
	HRZT_HIT,
	WRONG_BLOCK,
	CONSTRUCT_ERROR
};
void error(int e);


class Block
{
protected:
	pair<int, int> ref_p;
	int move_s;

	pair<int, int> cell1;
	pair<int, int> cell2;
	pair<int, int> cell3;
	pair<int, int> cell4;
	pair<int, int>& cell(int k) {
		if (k == 1) return cell1;
		else if (k == 2) return cell2;
		else if (k == 3) return cell3;
		else return cell4;
	}

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

class S1 :public Block
{
public:
	S1(int r, int m) {
		set_cells();
		ref_p = make_pair(-1, r);
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
		ref_p = make_pair(-1, r);
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
		ref_p = make_pair(-1, r);
		move_s = m;
	}
private:
	void set_cells() {
		cell1 = make_pair(-1, 0);
		cell2 = make_pair(0, 2);
		cell3 = make_pair(0, 1);
		cell4 = make_pair(-1, 1);
	}
};

class Z2 :public Block
{
public:
	Z2(int r, int m) {
		set_cells();
		ref_p = make_pair(-1, r);
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
		ref_p = make_pair(-1, r);
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
		ref_p = make_pair(-1, r);
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
		ref_p = make_pair(-1, r);
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
		ref_p = make_pair(-1, r);
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
		ref_p = make_pair(-1, r);
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
		ref_p = make_pair(-1, r);
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
		ref_p = make_pair(-1, r);
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
		ref_p = make_pair(-1, r);
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
		ref_p = make_pair(-1, r);
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
		ref_p = make_pair(-1, r);
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
		ref_p = make_pair(-1, r);
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
		ref_p = make_pair(-1, r);
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
		ref_p = make_pair(-1, r);
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
		ref_p = make_pair(-1, r);
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


class Game
{

	int row, col;
	bool **board;
	int height;

public:

	Game();
	~Game();

	void init();

	inline int get_row() const {
		return row;
	}
	inline int get_col() const {
		return col;
	}
	inline bool pos(int r, int c) const {
		return board[r][c];
	}
	inline int get_height() const {
		return height;
	}
	bool& pos(int r, int c) {
		return board[r][c];
	}

	void block_down(Block* b);//block往下掉(大流程/介面)


private:

	bool out_of_range(Block* b);//檢查左右有無超出
	bool occupied(Block*b, int i, int j);
	void hrzt_move(Block*b);


	void show_up(Block*b);
	void fall(Block*b);
	void set(Block*b);
	void set_height(Block* b);
	bool detect_line(Block*b);	//偵測有沒連線 //回傳連線幾條
	void remove(Block*b, int r);		//移除

};


void debug(Game& g);
void play(Game& g);		//收testcase且計算
void game_output(Game& g);	//將結果顯示出來

Block* get_block_type(string op, int r, int m);


int main(int argc, char *argv[]) {

	f.open(argv[1]);

	Game g;
	g.init();	//game init(set row/col)
	play(g);
	game_output(g);
	
	return 0;
}

void play(Game& g) {
	
	
	while (1) {
		string op;
		f >> op;
		if (op == "End") break;

		int r, m;
		f >> r >> m;
		
		Block* b = get_block_type(op,r,m);
		g.block_down(b);
		//debug(g);

	}
}

void game_output(Game& g) {

	for (int i = 0; i < g.get_row(); i++) {
		for (int j = 0; j < g.get_col(); j++) {
			o <<" "<< g.pos(i,j);
		}
		o << " \n";
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
	else {
		error(WRONG_BLOCK);
		return nullptr;
	}
}


pair<int, int> Block::cell_loc(int n) {
	switch (n)
	{
	case 1:
		return make_pair(cell1.first + ref_p.first, cell1.second + ref_p.second);
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


void Game::init() {

	while (1) {
		f >> row >> col;
		if (row <= 15 && col <= 40) break;
		else { cout << "Board too big!\n"; }
	}
	height = row - 1;
	board = new bool*[row];
	if (!board)
		error(CONSTRUCT_ERROR);

	for (int i = 0; i < row; i++) {
		board[i] = new bool[col];
		if (!board[i]) {
			cout << "board col " << i << " establish not complete" << endl;
			error(CONSTRUCT_ERROR);
		}
		for (int j = 0; j < col; j++) {
			board[i][j] = 0;
		}
	}


}

Game::Game()
{}
Game::~Game()
{
	for (int i = 0; i < row; i++) delete[]board[i];
	delete[]board;
}


void Game::block_down(Block* b) {

	//左右out of range
	if (out_of_range(b))
		error(OUT_OF_RANGE);

	//完整的顯示進去board 如果不行就 too high!
	show_up(b);

	//掉下去 直到碰到底後左右移動+再下去
	fall(b);

	//occupy空間
	set(b);

	detect_line(b);

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
		if (occupied(b, 1, 0))	//下一格有撞到
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

				error(TOO_HIGH);	//橫移過/削掉後還是太高
			}
		}

		b->ref_p.first += 1;	//如果能下降就下降
	}
}

//包含碰到要橫移
void Game::fall(Block*b) {

	while (!occupied(b, 1, 0))
	{
		b->ref_p.first += 1;
	}

	if (b->move_s != 0) {
		hrzt_move(b);
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

	//還在show_up的case
	if (b->cell_loc(1).first < 0 || b->cell_loc(2).first < 0 ||
		b->cell_loc(4).first < 0 || b->cell_loc(3).first < 0)
	{
		for (int k = 1; k <= 4; k++) {
			if (b->cell_loc(k).first == 0)
				pos(b->cell_loc(k).first, b->cell_loc(k).second) = 1;
			//該col上面還有未進去的block 讓他降下來
		}
	}
}


void Game::hrzt_move(Block* b) {

	while (b->move_s != 0) {
		b->move();
		if (occupied(b, 0, 0))
			error(HRZT_HIT);
	}
}

// i = offset of y ; j = offset of x
bool Game::occupied(Block*b, int i, int j) {

	if (b->cell_loc(1).first + i >= row || b->cell_loc(2).first + i >= row ||
		b->cell_loc(4).first + i >= row || b->cell_loc(3).first + i >= row)
		return 1;

	if ((b->cell_loc(1).first + i >= 0 && pos(b->cell_loc(1).first + i, b->cell_loc(1).second + j)) ||
		(b->cell_loc(2).first + i >= 0 && pos(b->cell_loc(2).first + i, b->cell_loc(2).second + j)) ||
		(b->cell_loc(3).first + i >= 0 && pos(b->cell_loc(3).first + i, b->cell_loc(3).second + j)) ||
		(b->cell_loc(4).first + i >= 0 && pos(b->cell_loc(4).first + i, b->cell_loc(4).second + j)))
		return 1;
	else return 0;
}




//debug用 顯示每一步的結果
void debug(Game& g) {
	for (int i = 0; i < g.get_row(); i++) {
		for (int j = 0; j < g.get_col(); j++) {
			cout << " " << g.pos(i, j);
		}
		cout << " \n";
	}
}

//error用 顯示哪裡出錯
void error(int e) {

	switch (e)
	{
	case 1:
		cout << "\nOut of range!" << endl;
		break;
	case 2:
		cout << "\nToo high!" << endl;
		break;
	case 3:
		cout << "\nHorizontal move failed!"<< endl;
		break;
	case 4:
		cout << "\nWrong block type" << endl;
		break;
	case 5:
		cout << "\nboard row establish not complete" << endl;
		break;

	default:
		cout << "Other error" << endl;
	}

	exit(1);
}
