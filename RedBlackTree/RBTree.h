#pragma once
/***
难点主要在删除节点后的调整
*/
enum class Color
{
	RED,BLACK
};
class Node {
public:  
	int val;
	Color color;
	Node* left, * right, *parent;
	Node(int v) :val(v),color(Color::RED), left(nullptr), right(nullptr), parent(nullptr) {};
};
class RBTree {
protected: 

	Color getColor(Node* node);

	Node* findNode(int num);
	Node* findMaxNode(Node* node);			//找到该节点下（包括此节点）的最大节点

	void rotateLeft(Node* node);
	void rotateRight(Node* node);
	 
	void rebalanceAfterDelete(Node* node);
	void rebalanceAfterInsert(Node* node);
	 

	void inOrder(Node* node);				//中序显示
public:
	Node* root;
	int size;

	RBTree():root(nullptr),size(0){}
	bool insert(int num);
	bool remove(int num);

	void printByInOrder();


	//int getBlackHeight(Node* node);
	//int getBlackHeightByRandom(Node* node); 
	//bool checkRule1(); //首节点为黑
	//bool checkRule2(Node* node); //没有双红
	//bool checkRule3(Node* node);//等高
};


