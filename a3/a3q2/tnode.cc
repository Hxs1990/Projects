#include "tnode.h"

// Deletes the TNode and all subnodes
void freeTNode(TNode *n){
	if (n != nullptr){
		freeTNode(n->left);
		freeTNode(n->right);
		delete n;
	}
}

// Returns a duplicate of the called Node
TNode *TNode::duplicate()const{
	TNode* leftCopy = (!left) ? nullptr : left->duplicate();
	TNode* rightCopy = (!right) ? nullptr : right->duplicate();
	TNode *toReturn = new TNode{data,leftCopy,rightCopy,size,parent};
	return toReturn;
}


// Returns the total length of the current Node and all subNodes.
unsigned int TNode::getLength()const{
	if (!right) return size;
	return size + right->getLength();
}


