//1081639 戴益暉 電子計算機 
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <fstream>
using namespace std;

class OperatorStack {	//存放運算子的堆疊
private:
	int top;		//堆疊當前的位置
	int capacity;	//堆疊的容量
	char* opAry;	//存放東西的陣列
public:
	OperatorStack() {					//建構子
		top = -1;						//堆疊剛開始位置是-1
		capacity = 10;					//容量為10
		opAry = new char[capacity];		//配置動態記憶體空間
	}
	bool IsEmpty() { return (top == -1); }	//判斷堆疊是否為空
	bool IsFull() { return(top == 10); }	//判斷堆疊是否為滿
	void Push(char);						//塞東西進堆疊
	char Pop();								//將當前的值從堆疊移除
	char CurrentOp() { return opAry[top]; }	//能知道堆疊當前的值
};
class NumberStack {		//存放數字的堆疊
private:
	int top;		//堆疊當前的位置
	int capacity;	//堆疊的容量
	int* numAry;	//存放東西的陣列
public:
	NumberStack() {						//建構子
		top = -1;						//堆疊剛開始位置是-1
		capacity = 10;					//容量為10
		numAry = new int[capacity];		//配置動態記憶體空間
	}
	bool IsEmpty() { return (top == -1); }	//判斷堆疊是否為空
	bool IsFull() { return(top == 10); }	//判斷堆疊是否為滿
	void Push(int);							//塞東西進堆疊
	int Pop();								//將當前的值從堆疊移除
	void Print() { cout << numAry[top]; }	//能知道堆疊當前的值
};

int count(string);				//兩個Stack做運算
int Caculate(char, int, int);	//從運算子判斷，並回傳運算結果
int Priority(char);				//判斷運算子的優先度
int main() {
	string formula;		
	cout << "輸入算式 :";		
	cin >> formula;				//使用者輸入字串

	count(formula);
}

int count(string formula) {
	OperatorStack opstk;	//宣告存放運算子的堆疊
	NumberStack numstk;		//宣告存放數字的堆疊
	string data = "";
	for (int i = 0; i < formula.length()+1; i++) {		
		// 如果是數字或負號(減號前面非數字或位於第一個)時存入data字串，否則執行運算 
		if (formula[i] >= '0' && formula[i] <= '9' && formula[i] != ' ' || (formula[i] == '-' && (formula[i - 1] < '0' || formula[i - 1]>'9') && formula[i - 1] != ')') || (i == 0 && formula[i] == '-')) {
			data += formula[i];		//如果是數字就塞進data
			//	cout<<str[i]<<endl;
		}
		else {
			// data不為空時(讀到運算符號的時候data可能為空) 
			if (data != "") {
				int num = atoi(data.c_str());	//將data字串轉為數字
				numstk.Push(num);				//將數字存進存放數字的堆疊
			}
			data = "";							//將data存空字串，讓下個數字可以使用
			if (formula[i] == '(') {			//判斷是'('
				opstk.Push(formula[i]);			//存進運算子堆疊
			}
			else if (formula[i] == ')') {		//判斷是')'
				while (opstk.CurrentOp() != '(') {	//如果當前的運算子不是'('
					int n1 = numstk.Pop();			//將堆疊的最上面兩個數字抽出來運算
					int n2 = numstk.Pop();	
					numstk.Push(Caculate(opstk.Pop(), n1, n2));	//丟進作運算的函式
				}
				opstk.Pop();	//pop掉')'
			}
			else if (formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/') {//判斷是 + - * /
				while (Priority(formula[i]) <= Priority(opstk.CurrentOp())) {	//如果優先度較大就會被彈出來
					int n1 = numstk.Pop();
					int n2 = numstk.Pop();
					numstk.Push(Caculate(opstk.Pop(), n1, n2));
				}
				opstk.Push(formula[i]);		//存進當前的運算子
			}
			else if (formula[i] == '^') {		//判斷是'^'
				while (Priority(formula[i]) < Priority(opstk.CurrentOp())) {	//只能小於該優先度才做
					int n1 = numstk.Pop();
					int n2 = numstk.Pop();
					numstk.Push(Caculate(opstk.Pop(), n1, n2));
				}
				opstk.Push(formula[i]);
			}
			else if (formula[i] >= '0' && formula[i] <= '9') {
				numstk.Push((formula[i] - '0'));	//0~9直接存數字堆疊
			}
		}
		
		
	}
	while (!opstk.IsEmpty()) {		//如果運算子堆疊還有就繼續做
		int n1 = numstk.Pop();
		int n2 = numstk.Pop();
		numstk.Push(Caculate(opstk.Pop(), n1, n2));
	}
	cout << "result is :";
	numstk.Print();
	return 0;
}
int Caculate(char op, int n1, int n2) {		//回傳運算結果
	if (op == '+')  return n2 + n1;
	else if (op == '-')  return n2 - n1;
	else if (op == '*')  return n2 * n1;
	else if (op == '/')  return n2 / n1;
	else if (op == '^')  return pow(n2, n1);
}
int Priority(char op) {		//回傳優先度
	if (op == '^') {
		return 3;
	}
	else if (op == '*' || op == '/') {
		return 2;
	}
	else if (op == '+' || op == '-') {
		return 1;
	}
	else {
		return 0;
	}
}

void OperatorStack::Push(char c) {
	if (IsFull()) {
		//enlarge();
	}
	opAry[++top] = c;
}
char OperatorStack::Pop() {
	if (IsEmpty()) {
		cout << "OperatorStack stack is empty" << endl;
	}
	else {
		char c = opAry[top];
		top--;
		return c;
	}
}
void NumberStack::Push(int num) {
	if (IsFull()) {
		//enlarge()
	}
	else {
		numAry[++top] = num;
	}
}
int NumberStack::Pop() {
	if (IsEmpty()) {
		cout << "NumberStack stack is empty" << endl;
	}
	else {
		int num = numAry[top];
		top--;
		return num;
	}
}