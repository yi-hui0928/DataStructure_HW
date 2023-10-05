//1081639 ���q�u �q�l�p��� 
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <fstream>
using namespace std;

class OperatorStack {	//�s��B��l�����|
private:
	int top;		//���|��e����m
	int capacity;	//���|���e�q
	char* opAry;	//�s��F�誺�}�C
public:
	OperatorStack() {					//�غc�l
		top = -1;						//���|��}�l��m�O-1
		capacity = 10;					//�e�q��10
		opAry = new char[capacity];		//�t�m�ʺA�O����Ŷ�
	}
	bool IsEmpty() { return (top == -1); }	//�P�_���|�O�_����
	bool IsFull() { return(top == 10); }	//�P�_���|�O�_����
	void Push(char);						//��F��i���|
	char Pop();								//�N��e���ȱq���|����
	char CurrentOp() { return opAry[top]; }	//�ા�D���|��e����
};
class NumberStack {		//�s��Ʀr�����|
private:
	int top;		//���|��e����m
	int capacity;	//���|���e�q
	int* numAry;	//�s��F�誺�}�C
public:
	NumberStack() {						//�غc�l
		top = -1;						//���|��}�l��m�O-1
		capacity = 10;					//�e�q��10
		numAry = new int[capacity];		//�t�m�ʺA�O����Ŷ�
	}
	bool IsEmpty() { return (top == -1); }	//�P�_���|�O�_����
	bool IsFull() { return(top == 10); }	//�P�_���|�O�_����
	void Push(int);							//��F��i���|
	int Pop();								//�N��e���ȱq���|����
	void Print() { cout << numAry[top]; }	//�ા�D���|��e����
};

int count(string);				//���Stack���B��
int Caculate(char, int, int);	//�q�B��l�P�_�A�æ^�ǹB�⵲�G
int Priority(char);				//�P�_�B��l���u����
int main() {
	string formula;		
	cout << "��J�⦡ :";		
	cin >> formula;				//�ϥΪ̿�J�r��

	count(formula);
}

int count(string formula) {
	OperatorStack opstk;	//�ŧi�s��B��l�����|
	NumberStack numstk;		//�ŧi�s��Ʀr�����|
	string data = "";
	for (int i = 0; i < formula.length()+1; i++) {		
		// �p�G�O�Ʀr�έt��(��e���D�Ʀr�Φ��Ĥ@��)�ɦs�Jdata�r��A�_�h����B�� 
		if (formula[i] >= '0' && formula[i] <= '9' && formula[i] != ' ' || (formula[i] == '-' && (formula[i - 1] < '0' || formula[i - 1]>'9') && formula[i - 1] != ')') || (i == 0 && formula[i] == '-')) {
			data += formula[i];		//�p�G�O�Ʀr�N��idata
			//	cout<<str[i]<<endl;
		}
		else {
			// data�����Ů�(Ū��B��Ÿ����ɭ�data�i�ର��) 
			if (data != "") {
				int num = atoi(data.c_str());	//�Ndata�r���ର�Ʀr
				numstk.Push(num);				//�N�Ʀr�s�i�s��Ʀr�����|
			}
			data = "";							//�Ndata�s�Ŧr��A���U�ӼƦr�i�H�ϥ�
			if (formula[i] == '(') {			//�P�_�O'('
				opstk.Push(formula[i]);			//�s�i�B��l���|
			}
			else if (formula[i] == ')') {		//�P�_�O')'
				while (opstk.CurrentOp() != '(') {	//�p�G��e���B��l���O'('
					int n1 = numstk.Pop();			//�N���|���̤W����ӼƦr��X�ӹB��
					int n2 = numstk.Pop();	
					numstk.Push(Caculate(opstk.Pop(), n1, n2));	//��i�@�B�⪺�禡
				}
				opstk.Pop();	//pop��')'
			}
			else if (formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/') {//�P�_�O + - * /
				while (Priority(formula[i]) <= Priority(opstk.CurrentOp())) {	//�p�G�u���׸��j�N�|�Q�u�X��
					int n1 = numstk.Pop();
					int n2 = numstk.Pop();
					numstk.Push(Caculate(opstk.Pop(), n1, n2));
				}
				opstk.Push(formula[i]);		//�s�i��e���B��l
			}
			else if (formula[i] == '^') {		//�P�_�O'^'
				while (Priority(formula[i]) < Priority(opstk.CurrentOp())) {	//�u��p����u���פ~��
					int n1 = numstk.Pop();
					int n2 = numstk.Pop();
					numstk.Push(Caculate(opstk.Pop(), n1, n2));
				}
				opstk.Push(formula[i]);
			}
			else if (formula[i] >= '0' && formula[i] <= '9') {
				numstk.Push((formula[i] - '0'));	//0~9�����s�Ʀr���|
			}
		}
		
		
	}
	while (!opstk.IsEmpty()) {		//�p�G�B��l���|�٦��N�~��
		int n1 = numstk.Pop();
		int n2 = numstk.Pop();
		numstk.Push(Caculate(opstk.Pop(), n1, n2));
	}
	cout << "result is :";
	numstk.Print();
	return 0;
}
int Caculate(char op, int n1, int n2) {		//�^�ǹB�⵲�G
	if (op == '+')  return n2 + n1;
	else if (op == '-')  return n2 - n1;
	else if (op == '*')  return n2 * n1;
	else if (op == '/')  return n2 / n1;
	else if (op == '^')  return pow(n2, n1);
}
int Priority(char op) {		//�^���u����
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