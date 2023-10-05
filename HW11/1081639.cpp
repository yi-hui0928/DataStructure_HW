//1081639 戴益暉 中序追蹤、階度追蹤
# include <iostream>
# include <cstdlib>
# include <iomanip>
using namespace std;

class Stack;
class Queue;
class Node {	//將user輸入的值變成node
	friend class BS_tree;  // for tree encapsulation
private:
	int key;	//存放user輸入的值
	Node* left, * right;	//node的左邊和右邊指標，連接其他node
public:
	Node() :left(NULL), right(NULL), key(0) {  }; // constructor
	Node(int a) :left(NULL), right(NULL), key(a) { }; // constructor
	friend class Stack;
	friend class Queue;
};
class BS_tree {
private:
	Node* root;		//指向二元搜尋樹的根
public:
	int count = 0;	//計算使用者輸入多少個值
	BS_tree() :root(NULL) {}; // constructor
	void inOrder() { inOrder(root); };			//呼叫inOrder(Node*)
	void inOrder(Node* root);					//將二元搜尋樹以中序追蹤的方式印出
	void Level_Order() { Level_Order(root); };	//呼叫Level_Order(Node*)
	void Level_Order(Node* root);				//將二元搜尋樹以階度追蹤的方式印出
	Node* insert(int key) { root = insert(root, key);	return 0; }//將二元搜尋樹回傳的Node指標塞入根root
	Node* insert(Node* root, int key);			//將值插入二元搜尋樹
};

class Stack {			//進行中序追蹤時用來存放node
	friend class Node;
private:
	int top;			//Stack當前的位置
	int capacity;		//Stack的容量
	Node** ItemAry;		//指向 存node的陣列 的指標
public:
	Stack() :top(-1), capacity(10) { ItemAry = new Node * [capacity]; }//建構式
	bool IsEmpty() { return(top == -1); }		//判斷Stack是否為空
	bool IsFull() { return(top == capacity); }	//判斷Stack是否為滿
	void Push(Node* node);		//將node塞進Stack
	Node* Pop();				//將node從Stack移除
};
void Stack::Push(Node* node) {	//將node塞進Stack
	if (IsFull()) {	//判斷是否Stack是否是滿的
		//enlarge()
		cout << "Stack is full" << endl;
	}
	ItemAry[++top] = node;	//將node存進Stack
}
Node* Stack::Pop() {			//將node從Stac移除
	Node* temp = ItemAry[top];	//將當前的node存進temp
	top--;			//移除Stack當前的node
	return temp;	//回傳temp裡面的node
}
class Queue {		//進行階度追蹤時，用來存放node
private:
	int front;		//排隊最前面的人，所以從這裡出去 
	int rear;		//排隊最後面的人，所以從這裡進來 
	int size;		//Queue容量大小 
	Node** queue;	//指向 用來存放node的陣列 的指標
public:
	Queue() {		//建構式
		front = 0;
		rear = -1;
		size = 20;
		queue = new Node * [size];
	};
	bool IsFull();				//判斷Queue是否為滿
	bool IsEmpty();				//判斷Queue是否為空
	void EnQueue(Node* node);	//將node塞進Queue
	Node* DeQueue();			//將node從Queue移除
	friend class Node;
};
bool Queue::IsFull() {
	//為了區別滿與空，滿的狀況下我們會空一格，所以用+2 
	// 因為可能有front=1, rear=5的狀況 所以會做front+size的檢查 
	return (front == rear + 2 || front + size == rear + 2);
}

bool Queue::IsEmpty() {
	// 因為可能有front=0, rear=5 所以會做front+size的檢查 
	return (front == rear + 1 || front + size == rear + 1);
}

void Queue::EnQueue(Node* node) {
	if (IsFull())	//判斷Queue是否為滿
		cout << "Queue is Full!" << endl;
	else {
		rear = (rear + 1) % size;	//將rear+1並除以size確保rear可以重新回到Queue 0 的位置
		queue[rear] = node;			//把node存入Queue
	}
}
Node* Queue::DeQueue() {
	if (IsEmpty())	//判斷Queue是否為空
		cout << "Queue is Empty!" << endl;
	else {
		Node* temp = queue[front];	//將Queue當前的node存入temp
		front = (front + 1) % size;	//depueue Queue 當前的node
		return temp;	//回傳temp裡面的node
	}
}
int main() {
	BS_tree tree;	//宣告一個tree
	int val;		//讓user輸入值
	cout << "請輸入值：(0代表結束)\n";
	do {
		// cout<<"請輸入值：(0代表結束)\n";
		cin >> val;				//user輸入值
		if (val != 0)			//判斷該值是否為0
			tree.insert(val);	// insertion encapsulation
		tree.count++;			//user輸入一次值就+1，計算使用者輸入幾個值
	} while (val != 0);			//如果user輸入0就跳出迴圈

	cout << "\n InOrder: ";
	tree.inOrder();  // inorder encapsulation
	cout << endl;

	cout << "\nLevel Order: ";
	tree.Level_Order();	//印出階度追蹤
	return 0;
}

//根據B.S.T特性，經過中序排序後必定為從小排到大! 
void BS_tree::inOrder(Node* node_p) {
	Stack stack;	//宣告存node的stack
	while (1) {
		while (node_p != NULL) {		//當node不為空值就進入迴圈，只要node的左邊還有node就一直丟進stack
			stack.Push(node_p);			//把node丟進stack
			node_p = node_p->left;		//往node的左邊前進
		}
		node_p = stack.Pop();			//因為node左邊沒有下一個node了，將stack裡的node彈出，為當前的node
		if (count == 1) break;			//count判斷是1表示user輸入的次數已經被扣完了，表示沒有node可跳出迴圈，剩餘1，因為user需輸入0
		cout << node_p->key << "  ";	//印出node的值
		count--;						//user輸入的次數扣一次
		node_p = node_p->right;			//因為左邊沒有下一個node了，所以往node的右邊走
	}
}

void BS_tree::Level_Order(Node* node_p) {
	Queue Q;			//宣告Queue 存 node
	Q.EnQueue(node_p);	//先將一個node存進Q，因為迴圈裡的第一件事會先dequeueu
	while (1) {
		node_p = Q.DeQueue();			//將dequeue的node表示為當前的node
		if (node_p == NULL)  break;		//當node判斷為空值就跳出迴圈
		cout << node_p->key << "  ";	//印出node的值

		if (node_p->left != NULL) {		//如果左邊有node就塞進Q裡，需先判斷左邊
			Q.EnQueue(node_p->left);
		}
		if (node_p->right != NULL) {	//如果右邊有node就塞進Q裡
			Q.EnQueue(node_p->right);
		}
		if (Q.IsEmpty()) {				//如果Q為空，已經沒有node要印了，跳出迴圈
			//cout << "Queue is empty";
			break;
		}
	}
}

//insert a new node with given key in B.S.T. 
Node* BS_tree::insert(Node* node, int key) {
	Node* NewOne = new Node(key);  //建立新的節點

	if (node == NULL) {		//如果沒有node，NewOne成為第一個節點
		return NewOne;
	}
	else {
		if (node->key > key) {		//如果新的節點小於舊的節點，就再用遞迴往下一個節點去判斷
			node->left = insert(node->left, key);
		}
		if (node->key < key) {		//如果新的節點大於舊的節點，就再用遞迴往下一個節點去判斷
			node->right = insert(node->right, key);
		}
	}
	return node;	//回傳整個node到root
}