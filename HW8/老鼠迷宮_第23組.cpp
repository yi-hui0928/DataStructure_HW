//老鼠迷宮 
// 第23組 1081639 戴益暉  1081611  謝鎬宇
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<fstream>
#include <string>
#define MAP(i,j)  map[i*col+j]  // for easy coding
using namespace std;

class Stack;
class StackItem {
public:
	int X, Y, Dir;  //小老鼠當前所在位置以及下一步的方向
	friend Stack;
};
class Stack {
private:
	int top, capacity;
	StackItem* ItemArray;
public:
	Stack() { top = -1, capacity = 5; ItemArray = new StackItem[capacity]; }
	bool IsEmpty() { return (top == -1); }
	bool IsFull() { return(top == capacity - 1); }
	void Push(int, int, int);
	void Pop(int& x, int& y, int& d);
	void Enlarge();  //如果Stack不夠大，須加大
	~Stack() { delete[]ItemArray; cout << endl << "已成功解構stack" << endl; }
};
void Stack::Push(int x, int y, int d) {
	if (IsFull())	//如果Stack是滿的就把capacity加大
		Enlarge();
	++top;
	ItemArray[top].X = x;	//存老鼠的當前位置和下一個前進的方向
	ItemArray[top].Y = y;
	ItemArray[top].Dir = d;
	//cout << "Push is : " << ItemArray[top].X << "," << ItemArray[top].Y << "," << ItemArray[top].Dir << endl;
}
void Stack::Pop(int& x, int& y, int& d) {
	if (IsEmpty()) { cout << "The Stack is empty" << endl; }	//判斷Stack是否是空的
	else {
		//cout << "Pop is : " << ItemArray[top].X << "," << ItemArray[top].Y << "," << ItemArray[top].Dir << endl;
		x = ItemArray[top].X;		//讓老鼠的位置等於pop出來的值，也就是讓老鼠回到位置
		y = ItemArray[top].Y;
		d = ItemArray[top].Dir;
		top--;
	}
}
void Stack::Enlarge() {
	capacity *= 2;		//加大capacity的空間
	StackItem* temp = new StackItem[capacity];
	for (int i = 0; i < capacity; i++) {	//將舊的動態陣列copy到新的動態陣列
		temp[i] = ItemArray[i];		
	}
	ItemArray = temp;
}
class offset {	//老鼠前進
public:
	int x, y;
};
class Map {
private:
	int col, row;
	int* map;
public:
	Map(int n) :col(n), row(n) {  // constructor
		map = new int[row * col];
	}
	void putInToMap(int i, string str);
	void setRow(int n) { row = n; } //decided by row of input file
	void setBoundary();
	int** printMap(int&,int&);
};
void Map::putInToMap(int i, string str) {
	if (i >= row - 1) {  // if out of space, enlarge
		int* map_temp = new int[row * col * 2];
		for (int k = 0; k < row * col; k++) {
			map_temp[k] = map[k];
		}
		delete[]map;
		map = map_temp;
		row *= 2;
	}
	for (int j = 1; j < col - 1; j++) {
		MAP(i, j) = str[j - 1];
	}
}
void Map::setBoundary() {
	for (int i = 0; i < row; i++) {
		map[i] = map[(row - 1) * col + i] = map[i * col] = map[i * col + (col - 1)] = '0';
	}
}
int** Map::printMap(int&RowLen,int&ColLen) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << MAP(i, j)-48;
		}
		cout << "\n";
	}
	int** maze = new int* [row];	//用一個新的二維動態陣列
	for (int i = 0; i < row; i++) {
		maze[i] = new int[col];
	}
	for (int i = 0; i < row; i++) {		//將老師的一維陣列存進動態二維陣列
		for (int j = 0; j < col; j++) {
			maze[i][j] = MAP(i, j)-48;
		}
	}
	RowLen = row;	//紀錄有幾列，幾行
	ColLen = col;
	return maze;	//回傳動態二維陣列
}
int main() {

	ifstream infile("map1.txt");  // open file "map1.txt" for read
	string str;
	if (!infile) //   if (infile.fail() )
	{
		cout << "test1.txt" << "檔案無法開啟!\n";
		exit(1); //exit(1)函式作用為強迫結束程式
	}

	getline(infile, str);
	Map m1(str.length() + 2); // length() get the number of column

	int i = 1;
	m1.putInToMap(i++, str);
	for (; getline(infile, str) && str.length() != 0; i++) {
		m1.putInToMap(i, str);
	}

	m1.setRow(i + 1);  // set the number of map row
	m1.setBoundary();  // set '0' to map boundary
	int RowLen, ColLen;
	int**maze=m1.printMap(RowLen,ColLen);   // print map for testing，且用maze接收回傳的二維陣列
	
//  if( m1.searchPath() )
//       m1.printPath();
//  else
//      cout << "no path found!\n";
	infile.clear();  infile.close();

	int N = 4;  
	offset offs[4];						//小老鼠的四個方向
	offs[0].x = 0; offs[0].y = 1;
	offs[1].x = 1; offs[1].y = 0;
	offs[2].x = 0; offs[2].y = -1;
	offs[3].x = -1; offs[3].y = 0;

	Stack stack;
	int x = 1, y = 1, d = -1;
	stack.Push(x, y, d);
	do {
		stack.Pop(x, y, d);				//如果都是死路則回到上一個位置
		for (int i = d + 1; i < N; i++) {
			if (maze[y + offs[i].y][x + offs[i].x] == 1) {	//判斷前進方向有沒有路
				stack.Push(x, y, i);	//如果有路可走就把當前位置及前進方向存進Stack
				maze[y][x] = 0;			//把走過的路設0，以免鬼打牆
				x = x + offs[i].x;		
				y = y + offs[i].y;
				d = -1;
				i = d;
			}
			if (x == ColLen-2 && y == RowLen -2) {	//判斷是不是終點
				cout << endl << " Find The Way Out !!" << endl;
				stack.Push(x, y, i);
				i = N;
			}
		}
	} while (!(x == 20 && y == 20) && !(stack.IsEmpty())); //還沒找到終點跟陣列不是空的就繼續找路

	if (stack.IsEmpty()) { cout << "找不到出口" << endl; }

		while (!stack.IsEmpty()) //如果stack還沒空 就一直執行
	{
		stack.Pop(x, y, d);
		maze[y][x] = 6; 
	}
	for (int i = 0; i < RowLen; i++) {   //把經過的路印出來
		for (int j = 0; j < ColLen; j++) {
			if (maze[i][j] == 6)  cout << "X";
			else  cout << " ";
		}
		cout << endl;
	}
	stack.~Stack();
	system("pause");
}



