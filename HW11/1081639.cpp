//1081639 ���q�u ���ǰl�ܡB���װl��
# include <iostream>
# include <cstdlib>
# include <iomanip>
using namespace std;

class Stack;
class Queue;
class Node {	//�Nuser��J�����ܦ�node
	friend class BS_tree;  // for tree encapsulation
private:
	int key;	//�s��user��J����
	Node* left, * right;	//node������M�k����СA�s����Lnode
public:
	Node() :left(NULL), right(NULL), key(0) {  }; // constructor
	Node(int a) :left(NULL), right(NULL), key(a) { }; // constructor
	friend class Stack;
	friend class Queue;
};
class BS_tree {
private:
	Node* root;		//���V�G���j�M�𪺮�
public:
	int count = 0;	//�p��ϥΪ̿�J�h�֭ӭ�
	BS_tree() :root(NULL) {}; // constructor
	void inOrder() { inOrder(root); };			//�I�sinOrder(Node*)
	void inOrder(Node* root);					//�N�G���j�M��H���ǰl�ܪ��覡�L�X
	void Level_Order() { Level_Order(root); };	//�I�sLevel_Order(Node*)
	void Level_Order(Node* root);				//�N�G���j�M��H���װl�ܪ��覡�L�X
	Node* insert(int key) { root = insert(root, key);	return 0; }//�N�G���j�M��^�Ǫ�Node���ж�J��root
	Node* insert(Node* root, int key);			//�N�ȴ��J�G���j�M��
};

class Stack {			//�i�椤�ǰl�ܮɥΨӦs��node
	friend class Node;
private:
	int top;			//Stack��e����m
	int capacity;		//Stack���e�q
	Node** ItemAry;		//���V �snode���}�C ������
public:
	Stack() :top(-1), capacity(10) { ItemAry = new Node * [capacity]; }//�غc��
	bool IsEmpty() { return(top == -1); }		//�P�_Stack�O�_����
	bool IsFull() { return(top == capacity); }	//�P�_Stack�O�_����
	void Push(Node* node);		//�Nnode��iStack
	Node* Pop();				//�Nnode�qStack����
};
void Stack::Push(Node* node) {	//�Nnode��iStack
	if (IsFull()) {	//�P�_�O�_Stack�O�_�O����
		//enlarge()
		cout << "Stack is full" << endl;
	}
	ItemAry[++top] = node;	//�Nnode�s�iStack
}
Node* Stack::Pop() {			//�Nnode�qStac����
	Node* temp = ItemAry[top];	//�N��e��node�s�itemp
	top--;			//����Stack��e��node
	return temp;	//�^��temp�̭���node
}
class Queue {		//�i�涥�װl�ܮɡA�ΨӦs��node
private:
	int front;		//�ƶ��̫e�����H�A�ҥH�q�o�̥X�h 
	int rear;		//�ƶ��̫᭱���H�A�ҥH�q�o�̶i�� 
	int size;		//Queue�e�q�j�p 
	Node** queue;	//���V �ΨӦs��node���}�C ������
public:
	Queue() {		//�غc��
		front = 0;
		rear = -1;
		size = 20;
		queue = new Node * [size];
	};
	bool IsFull();				//�P�_Queue�O�_����
	bool IsEmpty();				//�P�_Queue�O�_����
	void EnQueue(Node* node);	//�Nnode��iQueue
	Node* DeQueue();			//�Nnode�qQueue����
	friend class Node;
};
bool Queue::IsFull() {
	//���F�ϧO���P�šA�������p�U�ڭ̷|�Ť@��A�ҥH��+2 
	// �]���i�঳front=1, rear=5�����p �ҥH�|��front+size���ˬd 
	return (front == rear + 2 || front + size == rear + 2);
}

bool Queue::IsEmpty() {
	// �]���i�঳front=0, rear=5 �ҥH�|��front+size���ˬd 
	return (front == rear + 1 || front + size == rear + 1);
}

void Queue::EnQueue(Node* node) {
	if (IsFull())	//�P�_Queue�O�_����
		cout << "Queue is Full!" << endl;
	else {
		rear = (rear + 1) % size;	//�Nrear+1�ð��Hsize�T�Orear�i�H���s�^��Queue 0 ����m
		queue[rear] = node;			//��node�s�JQueue
	}
}
Node* Queue::DeQueue() {
	if (IsEmpty())	//�P�_Queue�O�_����
		cout << "Queue is Empty!" << endl;
	else {
		Node* temp = queue[front];	//�NQueue��e��node�s�Jtemp
		front = (front + 1) % size;	//depueue Queue ��e��node
		return temp;	//�^��temp�̭���node
	}
}
int main() {
	BS_tree tree;	//�ŧi�@��tree
	int val;		//��user��J��
	cout << "�п�J�ȡG(0�N����)\n";
	do {
		// cout<<"�п�J�ȡG(0�N����)\n";
		cin >> val;				//user��J��
		if (val != 0)			//�P�_�ӭȬO�_��0
			tree.insert(val);	// insertion encapsulation
		tree.count++;			//user��J�@���ȴN+1�A�p��ϥΪ̿�J�X�ӭ�
	} while (val != 0);			//�p�Guser��J0�N���X�j��

	cout << "\n InOrder: ";
	tree.inOrder();  // inorder encapsulation
	cout << endl;

	cout << "\nLevel Order: ";
	tree.Level_Order();	//�L�X���װl��
	return 0;
}

//�ھ�B.S.T�S�ʡA�g�L���ǱƧǫᥲ�w���q�p�ƨ�j! 
void BS_tree::inOrder(Node* node_p) {
	Stack stack;	//�ŧi�snode��stack
	while (1) {
		while (node_p != NULL) {		//��node�����ŭȴN�i�J�j��A�u�nnode�������٦�node�N�@����istack
			stack.Push(node_p);			//��node��istack
			node_p = node_p->left;		//��node������e�i
		}
		node_p = stack.Pop();			//�]��node����S���U�@��node�F�A�Nstack�̪�node�u�X�A����e��node
		if (count == 1) break;			//count�P�_�O1���user��J�����Ƥw�g�Q�����F�A��ܨS��node�i���X�j��A�Ѿl1�A�]��user�ݿ�J0
		cout << node_p->key << "  ";	//�L�Xnode����
		count--;						//user��J�����Ʀ��@��
		node_p = node_p->right;			//�]������S���U�@��node�F�A�ҥH��node���k�䨫
	}
}

void BS_tree::Level_Order(Node* node_p) {
	Queue Q;			//�ŧiQueue �s node
	Q.EnQueue(node_p);	//���N�@��node�s�iQ�A�]���j��̪��Ĥ@��Ʒ|��dequeueu
	while (1) {
		node_p = Q.DeQueue();			//�Ndequeue��node��ܬ���e��node
		if (node_p == NULL)  break;		//��node�P�_���ŭȴN���X�j��
		cout << node_p->key << "  ";	//�L�Xnode����

		if (node_p->left != NULL) {		//�p�G���䦳node�N��iQ�̡A�ݥ��P�_����
			Q.EnQueue(node_p->left);
		}
		if (node_p->right != NULL) {	//�p�G�k�䦳node�N��iQ��
			Q.EnQueue(node_p->right);
		}
		if (Q.IsEmpty()) {				//�p�GQ���šA�w�g�S��node�n�L�F�A���X�j��
			//cout << "Queue is empty";
			break;
		}
	}
}

//insert a new node with given key in B.S.T. 
Node* BS_tree::insert(Node* node, int key) {
	Node* NewOne = new Node(key);  //�إ߷s���`�I

	if (node == NULL) {		//�p�G�S��node�ANewOne�����Ĥ@�Ӹ`�I
		return NewOne;
	}
	else {
		if (node->key > key) {		//�p�G�s���`�I�p���ª��`�I�A�N�A�λ��j���U�@�Ӹ`�I�h�P�_
			node->left = insert(node->left, key);
		}
		if (node->key < key) {		//�p�G�s���`�I�j���ª��`�I�A�N�A�λ��j���U�@�Ӹ`�I�h�P�_
			node->right = insert(node->right, key);
		}
	}
	return node;	//�^�Ǿ��node��root
}