// 第23組 1081639 戴益暉  1081611  謝鎬宇
#include <iostream>
#include <cstdlib>
#include<fstream>
using namespace std;

class Polynomial_LinkList;
class Polynomial_node {
private:
	int coe, exp;
	Polynomial_node* next;
public:
	Polynomial_node() { coe = 0; exp = 0; next = NULL; }
	Polynomial_node(int i, int j) { coe = i; exp = j; next = NULL; }
	friend class Polynomial_LinkList;
};

class Polynomial_LinkList {
private:
	Polynomial_node* head;
public:
	Polynomial_LinkList() { head = NULL; }
	Polynomial_node* Insert(int, int);
	void Add(Polynomial_node*, Polynomial_node*);
	void PrintList(Polynomial_node*);
	void clear(Polynomial_node*, Polynomial_node*, Polynomial_node*);
};

void Getfile(Polynomial_LinkList A_list, Polynomial_LinkList B_list, Polynomial_node* Aptr, Polynomial_node* Bptr) {
	ifstream inf("hw.txt");		//開檔案
	if (!inf) {
		cout << "檔案無法開啟" << endl;	//如果檔案無法開啟則跳出去
		exit(1);
	}
	int ar, ac;		//存多項式的長度
	int i, j;		//讓檔案的資料流入
	inf >> ar >> ac;
	for (int k = 0; k < ar; k++) {
		inf >> i >> j;
		Aptr = A_list.Insert(i, j);		//塞進A的list 且 Aptr 取得A的head
	}

	for (int k = 0; k < ac; k++) {
		inf >> i >> j;
		Bptr = B_list.Insert(i, j);		//塞進B的list 且 Bptr 取得B的head
	}
	cout << "A polynomial is : " << endl;	//印出A list的長度
	A_list.PrintList(Aptr);
	cout << endl;

	cout << "B polynomial is : " << endl;	//印出B list的長度
	A_list.PrintList(Bptr);
	cout << endl;

	A_list.Add(Aptr, Bptr);
}

Polynomial_node* Polynomial_LinkList::Insert(int i, int j) {
	Polynomial_node* newNode = new Polynomial_node(i, j);   // 配置新的記憶體

	if (head == NULL) {                      // 若list沒有node, 令newNode為head
		head = newNode;
		return head;
	}

	Polynomial_node* current = head;

	if (current->exp < j) {			//如果current指到的次方比新增的次方小的話，新增的node=head 
		newNode->next = head;
		head = newNode;
		return head;
	}

	while (current->next != NULL && current->next->exp > j) {           // Traversal 且 下一個的次方>目前要插入的次方時 
		current = current->next;
	}

	newNode->next = current->next;
	current->next = newNode;

	return head;
}

void Polynomial_LinkList::PrintList(Polynomial_node* ptr) {

	if (ptr == NULL) {                      // 如果 ptr 指向NULL, 表示list沒有資料
		cout << "List is empty.\n";
		return;
	}
	
	Polynomial_node* current = ptr;             // 用pointer *current在list中移動
	while (current != NULL) {                 // Traversal	

		if (current == ptr) {					//current指的節點為多項式的第一個的狀況
			if (current->coe == 1) {
				cout << "X^" << current->exp;
			}
			else {
				cout << current->coe << "X^" << current->exp;
			}
		}

		else if (current->coe == 1) {		//係數為 1 的狀況
			cout << " + X^" << current->exp;
		}

		else if (current->coe == -1) {		//係數為 1 的狀況
			if (current->exp == 0) {
				cout << current->coe;
			}
			else {
				cout << " - X^" << current->coe;
			}
		}

		else if (current->exp == 0) {		//次方為 0 (常數) 的狀況
			if (current->coe > 0) {
				cout << " + " << current->coe;
			}
			else if (current->coe < 0) {
				cout << "  " << current->coe;
			}
			else if (current->coe == 0) { continue; }
		}
		
		else {
			if(current->coe > 0){
				cout << " + " << current->coe << "X^" << current->exp;
			}
			else if (current->coe < 0) {
				cout <<"  "<< current->coe << "X^" << current->exp;
			}						
		}

		current = current->next;
	}
	cout << endl;

}

int main() {
	Polynomial_LinkList A_list, B_list;		 //A多項式的鏈結和B多項式的鏈結
	Polynomial_node* Aptr = 0, * Bptr = 0;	 //A的head和B的head
	Getfile(A_list, B_list, Aptr, Bptr);	//取得檔案

	return 0;
}

void Polynomial_LinkList::Add(Polynomial_node* Aptr, Polynomial_node* Bptr) {
	
	Polynomial_LinkList C_list;		//C多項式的鏈結
	
	Polynomial_node* Atemp = Aptr;
	Polynomial_node* Btemp = Bptr;
	Polynomial_node* Cptr = 0;

	while (Atemp != NULL || Btemp != NULL) {	
		if (Atemp->exp > Btemp->exp) {				//如果A的次方大於B的次方，將A的係數和次方塞進C的list
			Cptr = C_list.Insert(Atemp->coe, Atemp->exp);
			Atemp = Atemp->next;
		}
		else if (Atemp->exp < Btemp->exp) {			//如果A的次方小於B的次方，將B的係數和次方塞進C的list
			Cptr = C_list.Insert(Btemp->coe, Btemp->exp);
			Btemp = Btemp->next;
		}
		else if (Atemp->exp == Btemp->exp) {		//如果A的次方大於B的次方，將A的係數和B的係數相加，再將相加結果和次方塞進C的list
			Cptr = C_list.Insert(Atemp->coe + Btemp->coe, Atemp->exp);
			Atemp = Atemp->next;
			Btemp = Btemp->next;
		}
	}
	while (Atemp!=NULL)		//如果A還沒塞完
	{
		Cptr = C_list.Insert(Atemp->coe, Atemp->exp);
		Atemp = Atemp->next;
	}
	while (Btemp != NULL)	//如果B還沒塞完
	{
		Cptr = C_list.Insert(Btemp->coe, Btemp->exp);
		Btemp = Btemp->next;
	}

	cout << "C polynomial is : " <<endl;  //印出C
	C_list.PrintList(Cptr);
	cout << endl;

	cout << "請按任一鍵解構" << endl;
	cout << endl;

	system("pause");
	C_list.clear(Aptr, Bptr, Cptr);		//解構
}
void Polynomial_LinkList::clear(Polynomial_node* Aptr, Polynomial_node* Bptr, Polynomial_node* Cptr) {
	
	while (Aptr != 0) {            // Traversal
		Polynomial_node* current = Aptr;
		Aptr = Aptr->next;
		delete current;
		current = 0;
	}
	while (Bptr != 0) {            // Traversal
		Polynomial_node* current = Bptr;
		Bptr = Bptr->next;
		delete current;
		current = 0;
	}
	while (Cptr != 0) {            // Traversal
		Polynomial_node* current = Cptr;
		Cptr = Cptr->next;
		delete current;
		current = 0;
	}
	cout << endl << "已成功解構" << endl;
}