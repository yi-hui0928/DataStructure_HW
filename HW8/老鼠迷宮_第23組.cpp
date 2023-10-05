//�ѹ��g�c 
// ��23�� 1081639 ���q�u  1081611  ����t
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
	int X, Y, Dir;  //�p�ѹ���e�Ҧb��m�H�ΤU�@�B����V
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
	void Enlarge();  //�p�GStack�����j�A���[�j
	~Stack() { delete[]ItemArray; cout << endl << "�w���\�Ѻcstack" << endl; }
};
void Stack::Push(int x, int y, int d) {
	if (IsFull())	//�p�GStack�O�����N��capacity�[�j
		Enlarge();
	++top;
	ItemArray[top].X = x;	//�s�ѹ�����e��m�M�U�@�ӫe�i����V
	ItemArray[top].Y = y;
	ItemArray[top].Dir = d;
	//cout << "Push is : " << ItemArray[top].X << "," << ItemArray[top].Y << "," << ItemArray[top].Dir << endl;
}
void Stack::Pop(int& x, int& y, int& d) {
	if (IsEmpty()) { cout << "The Stack is empty" << endl; }	//�P�_Stack�O�_�O�Ū�
	else {
		//cout << "Pop is : " << ItemArray[top].X << "," << ItemArray[top].Y << "," << ItemArray[top].Dir << endl;
		x = ItemArray[top].X;		//���ѹ�����m����pop�X�Ӫ��ȡA�]�N�O���ѹ��^���m
		y = ItemArray[top].Y;
		d = ItemArray[top].Dir;
		top--;
	}
}
void Stack::Enlarge() {
	capacity *= 2;		//�[�jcapacity���Ŷ�
	StackItem* temp = new StackItem[capacity];
	for (int i = 0; i < capacity; i++) {	//�N�ª��ʺA�}�Ccopy��s���ʺA�}�C
		temp[i] = ItemArray[i];		
	}
	ItemArray = temp;
}
class offset {	//�ѹ��e�i
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
	int** maze = new int* [row];	//�Τ@�ӷs���G���ʺA�}�C
	for (int i = 0; i < row; i++) {
		maze[i] = new int[col];
	}
	for (int i = 0; i < row; i++) {		//�N�Ѯv���@���}�C�s�i�ʺA�G���}�C
		for (int j = 0; j < col; j++) {
			maze[i][j] = MAP(i, j)-48;
		}
	}
	RowLen = row;	//�������X�C�A�X��
	ColLen = col;
	return maze;	//�^�ǰʺA�G���}�C
}
int main() {

	ifstream infile("map1.txt");  // open file "map1.txt" for read
	string str;
	if (!infile) //   if (infile.fail() )
	{
		cout << "test1.txt" << "�ɮ׵L�k�}��!\n";
		exit(1); //exit(1)�禡�@�ά��j�������{��
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
	int**maze=m1.printMap(RowLen,ColLen);   // print map for testing�A�B��maze�����^�Ǫ��G���}�C
	
//  if( m1.searchPath() )
//       m1.printPath();
//  else
//      cout << "no path found!\n";
	infile.clear();  infile.close();

	int N = 4;  
	offset offs[4];						//�p�ѹ����|�Ӥ�V
	offs[0].x = 0; offs[0].y = 1;
	offs[1].x = 1; offs[1].y = 0;
	offs[2].x = 0; offs[2].y = -1;
	offs[3].x = -1; offs[3].y = 0;

	Stack stack;
	int x = 1, y = 1, d = -1;
	stack.Push(x, y, d);
	do {
		stack.Pop(x, y, d);				//�p�G���O�����h�^��W�@�Ӧ�m
		for (int i = d + 1; i < N; i++) {
			if (maze[y + offs[i].y][x + offs[i].x] == 1) {	//�P�_�e�i��V���S����
				stack.Push(x, y, i);	//�p�G�����i���N���e��m�Ϋe�i��V�s�iStack
				maze[y][x] = 0;			//�⨫�L�����]0�A�H�K������
				x = x + offs[i].x;		
				y = y + offs[i].y;
				d = -1;
				i = d;
			}
			if (x == ColLen-2 && y == RowLen -2) {	//�P�_�O���O���I
				cout << endl << " Find The Way Out !!" << endl;
				stack.Push(x, y, i);
				i = N;
			}
		}
	} while (!(x == 20 && y == 20) && !(stack.IsEmpty())); //�٨S�����I��}�C���O�Ū��N�~����

	if (stack.IsEmpty()) { cout << "�䤣��X�f" << endl; }

		while (!stack.IsEmpty()) //�p�Gstack�٨S�� �N�@������
	{
		stack.Pop(x, y, d);
		maze[y][x] = 6; 
	}
	for (int i = 0; i < RowLen; i++) {   //��g�L�����L�X��
		for (int j = 0; j < ColLen; j++) {
			if (maze[i][j] == 6)  cout << "X";
			else  cout << " ";
		}
		cout << endl;
	}
	stack.~Stack();
	system("pause");
}



