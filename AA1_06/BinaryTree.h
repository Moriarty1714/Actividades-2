#pragma once
#include <math.h>
#include <time.h>
#include <stack>

//CLASS TREE
template <class T>
class BinaryTree {
	struct Node {
		T data;

		Node* left;
		Node* right;
		Node(T _data) : data(_data), left(nullptr), right(nullptr) {};
	};

	Node* root;

public:
	BinaryTree() {
		root = nullptr;
	}

	~BinaryTree() {
		DestroyTree(root);	
	}

	void CreateTree() {
		root = new Node(67);
		root->left = new Node(14);
		root->right = new Node(32);
		root->left->left = new Node(1);
		root->left->right = new Node(4);
		root->right->left = new Node(46);
	}
	
	//AA1_06->5)
private:
	int getNumberNodes(Node* _node) {
		if (_node == nullptr) return 0;

		return 1+ getNumberNodes(_node->left)+ getNumberNodes(_node->right);
	}
public:
	int getNumberNodes() {
		return getNumberNodes(root);
	}

	//AA1_06->6)
	int getNumberNodesI() {
		int counter = 0;

		std::stack<Node*> notVisitedNodes;
		notVisitedNodes.push(root);

		if (root->left == nullptr && root->right == nullptr) return 1;
		Node* tmp;
		while (!notVisitedNodes.empty()) {
			tmp = notVisitedNodes.top();
			std::cout << tmp->data << std::endl;
			notVisitedNodes.pop();
			counter++;

			if (tmp->left != nullptr) notVisitedNodes.push(tmp->left);
			if (tmp->right != nullptr) notVisitedNodes.push(tmp->right);

			delete tmp;
		}
		return counter;

	
	}

	void showOrders() {
		std::cout <<"PreOrder: " << std::endl;
		PreOrder(root);
		std::cout << std::endl;
		std::cout << "InOrder: " << std::endl;
		InOrder(root);
		std::cout << std::endl;
		std::cout <<"PostOrder: " << std::endl;
		PostOrder(root);
		std::cout << std::endl << std::endl;
	}

private:
	//AA1_06->2)
	void PreOrder(Node* _root)
	{
		if (_root == nullptr)  return; 
		std::cout << _root->data <<"	";
		PreOrder(_root->left);
		PreOrder(_root->right);
	}

	//AA1_06->3)
	void InOrder(Node* _root) {
		if (_root == nullptr)  return;
		InOrder(_root->left);
		std::cout << _root->data << "	";
		InOrder(_root->right);	
	}

	//AA1_06->4)
	void PostOrder(Node* _root)
	{
		if (_root == nullptr)  return;
		PostOrder(_root->left);
		PostOrder(_root->right);
		std::cout << _root->data <<"	";
	}

	//AA1_06->1)
public:
	void DestroyTree(Node* _node) {
		if (_node->left == nullptr &&_node->right==nullptr) delete _node;
		else {
			if (_node->left != nullptr)
				DestroyTree(_node->left);
			if (_node->right != nullptr)
				DestroyTree(_node->right);
		}
	}

	//AA1_06->8)
private:
	int Height(Node* _node) {
		if (_node == nullptr) return 0;

		int tmp1 = Height(_node->left);
		int tmp2 = Height(_node->right);
		
		if (tmp1 < tmp2) return 1+tmp2;
		else return 1+tmp1;
	}

public:
	int Height() {
		return Height(root);
	}

	//AA1_06->7)
	void PreOrderI() {
		std::stack<Node*> notVisitedNodes;
		notVisitedNodes.push(root);

		if (root->left == nullptr && root->right == nullptr) std::cout << root->data;
		Node* tmp;
		while (!notVisitedNodes.empty()) {
			tmp = notVisitedNodes.top();
			std::cout << tmp->data << std::endl;
			notVisitedNodes.pop();

			if (tmp->right != nullptr) notVisitedNodes.push(tmp->right);
			if (tmp->left != nullptr) notVisitedNodes.push(tmp->left);

		}
	}
};

