#include <iostream>
#include "BinaryTree.h"

int main() {
	BinaryTree<int>* myBinaryTree = new BinaryTree<int>();
	myBinaryTree->CreateTree();
	std::cout <<"Number of Nodes: "<< myBinaryTree->getNumberNodes() <<std::endl << std::endl;
	myBinaryTree->showOrders();
	std::cout << "Height: " << myBinaryTree->Height() << std::endl << std::endl;
	std::cout << "PreOrderI: " << std::endl << std::endl;
	myBinaryTree->PreOrderI();
	std::cout << myBinaryTree->getNumberNodes();
	delete myBinaryTree;

	std::cout << "Deltree done!" << std::endl;
	
	return 0;
	
}