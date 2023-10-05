// ��23�� 1081639 ���q�u  1081611  ����t
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
	ifstream inf("hw.txt");		//�}�ɮ�
	if (!inf) {
		cout << "�ɮ׵L�k�}��" << endl;	//�p�G�ɮ׵L�k�}�ҫh���X�h
		exit(1);
	}
	int ar, ac;		//�s�h����������
	int i, j;		//���ɮת���Ƭy�J
	inf >> ar >> ac;
	for (int k = 0; k < ar; k++) {
		inf >> i >> j;
		Aptr = A_list.Insert(i, j);		//��iA��list �B Aptr ���oA��head
	}

	for (int k = 0; k < ac; k++) {
		inf >> i >> j;
		Bptr = B_list.Insert(i, j);		//��iB��list �B Bptr ���oB��head
	}
	cout << "A polynomial is : " << endl;	//�L�XA list������
	A_list.PrintList(Aptr);
	cout << endl;

	cout << "B polynomial is : " << endl;	//�L�XB list������
	A_list.PrintList(Bptr);
	cout << endl;

	A_list.Add(Aptr, Bptr);
}

Polynomial_node* Polynomial_LinkList::Insert(int i, int j) {
	Polynomial_node* newNode = new Polynomial_node(i, j);   // �t�m�s���O����

	if (head == NULL) {                      // �Ylist�S��node, �OnewNode��head
		head = newNode;
		return head;
	}

	Polynomial_node* current = head;

	if (current->exp < j) {			//�p�Gcurrent���쪺�����s�W������p���ܡA�s�W��node=head 
		newNode->next = head;
		head = newNode;
		return head;
	}

	while (current->next != NULL && current->next->exp > j) {           // Traversal �B �U�@�Ӫ�����>�ثe�n���J������� 
		current = current->next;
	}

	newNode->next = current->next;
	current->next = newNode;

	return head;
}

void Polynomial_LinkList::PrintList(Polynomial_node* ptr) {

	if (ptr == NULL) {                      // �p�G ptr ���VNULL, ���list�S�����
		cout << "List is empty.\n";
		return;
	}
	
	Polynomial_node* current = ptr;             // ��pointer *current�blist������
	while (current != NULL) {                 // Traversal	

		if (current == ptr) {					//current�����`�I���h�������Ĥ@�Ӫ����p
			if (current->coe == 1) {
				cout << "X^" << current->exp;
			}
			else {
				cout << current->coe << "X^" << current->exp;
			}
		}

		else if (current->coe == 1) {		//�Y�Ƭ� 1 �����p
			cout << " + X^" << current->exp;
		}

		else if (current->coe == -1) {		//�Y�Ƭ� 1 �����p
			if (current->exp == 0) {
				cout << current->coe;
			}
			else {
				cout << " - X^" << current->coe;
			}
		}

		else if (current->exp == 0) {		//���謰 0 (�`��) �����p
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
	Polynomial_LinkList A_list, B_list;		 //A�h�������쵲�MB�h�������쵲
	Polynomial_node* Aptr = 0, * Bptr = 0;	 //A��head�MB��head
	Getfile(A_list, B_list, Aptr, Bptr);	//���o�ɮ�

	return 0;
}

void Polynomial_LinkList::Add(Polynomial_node* Aptr, Polynomial_node* Bptr) {
	
	Polynomial_LinkList C_list;		//C�h�������쵲
	
	Polynomial_node* Atemp = Aptr;
	Polynomial_node* Btemp = Bptr;
	Polynomial_node* Cptr = 0;

	while (Atemp != NULL || Btemp != NULL) {	
		if (Atemp->exp > Btemp->exp) {				//�p�GA������j��B������A�NA���Y�ƩM�����iC��list
			Cptr = C_list.Insert(Atemp->coe, Atemp->exp);
			Atemp = Atemp->next;
		}
		else if (Atemp->exp < Btemp->exp) {			//�p�GA������p��B������A�NB���Y�ƩM�����iC��list
			Cptr = C_list.Insert(Btemp->coe, Btemp->exp);
			Btemp = Btemp->next;
		}
		else if (Atemp->exp == Btemp->exp) {		//�p�GA������j��B������A�NA���Y�ƩMB���Y�Ƭۥ[�A�A�N�ۥ[���G�M�����iC��list
			Cptr = C_list.Insert(Atemp->coe + Btemp->coe, Atemp->exp);
			Atemp = Atemp->next;
			Btemp = Btemp->next;
		}
	}
	while (Atemp!=NULL)		//�p�GA�٨S�맹
	{
		Cptr = C_list.Insert(Atemp->coe, Atemp->exp);
		Atemp = Atemp->next;
	}
	while (Btemp != NULL)	//�p�GB�٨S�맹
	{
		Cptr = C_list.Insert(Btemp->coe, Btemp->exp);
		Btemp = Btemp->next;
	}

	cout << "C polynomial is : " <<endl;  //�L�XC
	C_list.PrintList(Cptr);
	cout << endl;

	cout << "�Ы����@��Ѻc" << endl;
	cout << endl;

	system("pause");
	C_list.clear(Aptr, Bptr, Cptr);		//�Ѻc
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
	cout << endl << "�w���\�Ѻc" << endl;
}