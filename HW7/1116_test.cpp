// Binaary Search tree Building using encapsulation 
// by Julie Liu 2017
#include<stdio.h> 
#include<stdlib.h>
#include<iostream>

using namespace std;

class Node{ 
 friend class BS_tree;  // for tree encapsulation
 private:
    int key; 
    Node *left, *right; 
 public:
    Node():left(NULL),right(NULL),key(0) {  }; // constructor
    Node(int a):left(NULL),right(NULL),key(a) { }; // constructor
 }; 
class BS_tree{	
	private:
		Node * root;
    public:
		BS_tree():root(NULL){}; // constructor
		void inOrder() { inOrder(root);	};
		void inOrder(Node *root);
		Node* insert(int key){ root= insert(root,key);	};
		Node* insert(Node* root, int key);

};

int main(){
    BS_tree tree; 
 	int val;
 	cout<<"請輸入值：(0代表結束)\n";
	do {
		// cout<<"請輸入值：(0代表結束)\n";
		cin>>val;
		if(val!=0)
		  tree.insert(val); // insertion encapsulation
	} while(val!=0);

	cout <<"\n InOrder: ";
	tree.inOrder();  // inorder encapsulation
	return 0;
 } 
 
 //根據B.S.T特性，經過中序排序後必定為從小排到大! 
void BS_tree::inOrder(Node *node_p){ 
 	if (node_p != NULL){ 
  		inOrder(node_p->left); 
  		cout<<node_p->key<<'\t';
  		inOrder(node_p->right); 
 	}
}

//insert a new node with given key in B.S.T. 
Node* BS_tree::insert(Node* node, int key){ 
	
 } 
