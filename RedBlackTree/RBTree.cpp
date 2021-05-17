#include"RBTree.h"
#include<iostream>
#include<stdlib.h>


bool RBTree::insert(int num) {
	Node* node = new Node(num); 
	if (root == nullptr) {
		node->color = Color::BLACK;
		root = node;
	}
	else {

		//Node* res = insertNode(node);

		Node* cur = root;
		Node* last = cur;
		while (cur)
		{

			last = cur;
			if (cur->val > node->val) {
				cur = cur->left;
				if (!cur) {

					last->left = node;
					node->parent = last;
					break;
				}
			}
			else {
				cur = cur->right;
				if (!cur) {

					last->right = node;
					node->parent = last;
					break;
				}
			}
		}
		 
		rebalanceAfterInsert(node);
	}
	size++;
	return 1;
} 
void RBTree::rotateLeft(Node* node) {
	Node* parent = node->parent;
	Node* oldRight = node->right;
	Node* newRight = oldRight->left;

	node->right = newRight;
	if(newRight)newRight->parent = node;

	oldRight->left = node;
	node->parent = oldRight;

	oldRight->parent = parent;
	if (parent) {
		if (parent->right == node)parent->right = oldRight;
		else parent->left = oldRight;
	}

	if (node == root) {
		root = oldRight;
		root->color = Color::BLACK;
	}
}
void RBTree::rotateRight(Node* node) {
	Node* parent = node->parent;
	Node* oldLeft = node->left;
	Node* newLeft = oldLeft->right;

	node->left = newLeft;
	if(newLeft)newLeft->parent = node;

	oldLeft->right = node;
	node->parent = oldLeft;

	
	oldLeft->parent = parent;
	if (parent) {
		if (parent->left == node)parent->left = oldLeft;
		else parent->right = oldLeft;
	}


	if (node == root) {
		root = oldLeft;
		root->color = Color::BLACK;
	}
}

void RBTree::rebalanceAfterInsert(Node* node) {
	Node* parent = node->parent;
	if (!parent){
		node->color = Color::BLACK; return;
	}
	if (parent->color == Color::BLACK)return;
	Node* pp = parent->parent;
	if (pp->left == parent && getColor(pp->right) == Color::RED) {
		pp->left->color = Color::BLACK; 
		pp->right->color = Color::BLACK; 
		if (pp != root)pp->color = Color::RED;
		rebalanceAfterInsert(pp);
	}
	else if (pp->right == parent && getColor(pp->left) == Color::RED) {
		pp->left->color = Color::BLACK;
		pp->right->color = Color::BLACK;
		if (pp != root)pp->color = Color::RED;
		rebalanceAfterInsert(pp);
	}
	else {
		if (pp->left == parent) {
			if (parent->right == node)rotateLeft(parent);
			rotateRight(pp); 
		}
		else if (pp->right == parent) {
			if (parent->left == node)rotateRight(parent);
			rotateLeft(pp);
		}

		pp->color = Color::RED;
		pp->parent->color = Color::BLACK;
	}

}



bool RBTree::remove(int num) {
	Node* node = findNode(num);
	if (!node)return false;
	rebalanceAfterDelete(node);
	size--;
	return 1;

}
void RBTree::rebalanceAfterDelete(Node* node)
{
	Node* tmp = findMaxNode(node->left);
	if (tmp) {
		std::swap(tmp->val, node->val);
		node = tmp;
	}//这一段交换代码，主要是让待删除节点尽量是叶子节点，也就是让它最多有一个儿子

	Node* parent = node->parent;
	 
	if (!parent) {//根节点单独处理
		if (root->right) {
			rotateLeft(root);
			delete root->left;
			root->left = nullptr;
		}
		else if (root->left) {
			rotateRight(root);
			delete root->right;
			root->right = nullptr;
		}
		else {
			delete root;
			root = nullptr;
		}
		return;
	}

	if (node->color == Color::RED) {
		if (node == parent->left)parent->left = nullptr;
		else parent->right = nullptr;
		delete node;
	}
	else if (getColor(node->left) == Color::RED) {
		node->val = node->left->val;
		delete node->left;
		node->left = nullptr;
	}
	else if (getColor(node->right) == Color::RED) {
		node->val = node->right->val;
		delete node->right;
		node->right = nullptr;
	} //前半段 只要自己或者儿子是红色的相对好处理一些

	else {//儿子为黑，且儿子没有儿子的情况
		tmp = node;
		bool flag = 1;
		while (flag && parent) {
			flag = 0;
			if (parent->color == Color::RED) {//父红
				 
				if (parent->left == node) {
					rotateLeft(parent); 

					if (getColor(parent->right) == Color::RED)rebalanceAfterInsert(parent->right);
				}
				else {
					rotateRight(parent); 
					if (getColor(parent->left) == Color::RED)rebalanceAfterInsert(parent->left);
				}

			}
			else if (getColor(parent->left) == Color::RED) {//左兄弟红
				parent->left->color = Color::BLACK;
				rotateRight(parent);  
				Node* cur = parent->left;
				if (getColor(cur->right) == Color::RED && getColor(cur->left) == Color::BLACK) {
					rotateLeft(cur);
					cur->color = Color::RED;
					cur->parent->color = Color::BLACK;
					cur = cur->parent;
				}
				rotateRight(parent);
				if (getColor(cur->left) == Color::RED) {
					cur->color = Color::RED;
					cur->left->color = Color::BLACK;
				}
				else {
					parent->color = Color::RED;
				}
			}
			else if (getColor(parent->right) == Color::RED) {//右兄弟红
				parent->right->color = Color::BLACK;
				rotateLeft(parent);   
				Node* cur = parent->right;
				if (getColor(cur->left) == Color::RED && getColor(cur->right) == Color::BLACK) {
					rotateRight(cur);
					cur->color = Color::RED;
					cur->parent->color = Color::BLACK;
					cur = cur->parent;
				}
				rotateLeft(parent);
				if (getColor(cur->right) == Color::RED) {
					cur->color = Color::RED;
					cur->right->color = Color::BLACK;
				}
				else {
					parent->color = Color::RED;
				}
			}
			else {//同辈及父亲都为黑
				if (parent->left == node) {
					Node* sibbing = parent->right;
					if (getColor(sibbing->left)==Color::BLACK && 
						getColor(sibbing->right) == Color::BLACK) {
						sibbing->color = Color::RED;
						node = parent;
						parent = parent->parent;
						flag = 1;
					}
					else {
						if (getColor(sibbing->right) == Color::BLACK) {
							sibbing->left->color = Color::BLACK;
							rotateRight(sibbing);
						}
						else {
							sibbing->right->color = Color::BLACK;
						}
						rotateLeft(parent);
					}
				}
				else if (parent->right == node) {
					Node* sibbing = parent->left;
					if (getColor(sibbing->left) == Color::BLACK &&
						getColor(sibbing->right) == Color::BLACK) {
						sibbing->color = Color::RED;
						node = parent;
						parent = parent->parent;
						flag = 1;
					}
					else {
						if (getColor(sibbing->left) == Color::BLACK) {
							sibbing->right->color = Color::BLACK;
							rotateLeft(sibbing);
						}
						else {
							sibbing->left->color = Color::BLACK;
						}
						rotateRight(parent);
					}
				}
				 
			}
		}

		parent = tmp->parent;
		if (parent->left == tmp)parent->left = nullptr;
		else parent->right = nullptr;
		delete tmp;
	}


	return;
} 
Node* RBTree::findMaxNode(Node* node) {
	if (!node)return nullptr;
	while (node->right)node = node->right;
	return node;
}
Node* RBTree::findNode(int num) {
	Node* cur = root;
	while (cur)
	{
		if (cur->val > num)cur = cur->left;
		else if (cur->val < num)cur = cur->right;
		else return cur;
	}
	return nullptr;
}


void RBTree::inOrder(Node* node) {
	if (node == nullptr)return;
	inOrder(node->left);
	std::cout << node->val << " ";
	inOrder(node->right);
}
void RBTree::printByInOrder() {
	inOrder(root);
	std::cout << std::endl;
}
Color RBTree::getColor(Node* node) {
	if (!node)return Color::BLACK;
	return node->color;
}


//------------test rule code-------------
/*

int RBTree::getBlackHeight(Node* node) {
	if (node == nullptr)return 0;
	return (node->color == Color::BLACK) + getBlackHeight(node->right);
}
int RBTree::getBlackHeightByRandom(Node* node) {
	if (node == nullptr)return 0;
	bool left = rand() & 1;
	bool have = node->color == Color::BLACK;
	if (left)return have + getBlackHeightByRandom(node->left);
	else return have + getBlackHeightByRandom(node->right);
}

bool RBTree::checkRule1() {
	return getColor(root) == Color::BLACK;
}


bool RBTree::checkRule2(Node* node) {
	if (!node)return 1;
	return !((getColor(node->parent) == Color::RED)&& (getColor(node) == Color::RED)) &&
		checkRule2(node->right) && checkRule2(node->left);
}

bool RBTree::checkRule3(Node* node) {
	if (!node)return 1;
	return getBlackHeight(node->left) == getBlackHeight(node->right)
		&& checkRule3(node->left) && checkRule3(node->right);
}
*/