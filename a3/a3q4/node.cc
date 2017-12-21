#include "node.h"
#include <iostream>
Node::Node(int data, Node* next, bool ownsSuccessor):
	data{data}, next{next}, ownsSuccessor{ownsSuccessor}{}

// Picks a head node to print out, wrapper function
void printNodes(std::ostream &out, Node **headArray, int head){
	printNextNode(out,headArray[head]);
	out << std::endl;
}

// Helper function for printNodes that helps prints the nodes
void printNextNode(std::ostream &out, Node *node){
	if (node->next){
		out << node->data << ' ';
		printNextNode(out,node->next);
	}
	else{
		out << node->data;
	}
}
// Pick a given node in the head
void attachNode(Node **headArray, int head, int index, int data){
	if (index == 0){
		// Appending to the linkedlist so we don't need to create a new head
		Node *newHead = new Node{data,headArray[head],true};
		headArray[head] = newHead;
	}
	else{
		// We have to create a new head to point at the new fork.
		// Cycle through the linkedlist until index, with pointer p.
		Node *p = headArray[head];
		for(int i = 0; i<index; ++i){
			p = p->next;
		}
		// Set a new headArray to the Node of whatever pointer p was pointing at.
		// NOTE: the attached node does not own the linkedlist attached to.
		int available = 0;
		while(headArray[available]){
			++available;
		}
		headArray[available] = new Node{data,&(*p)};
	}
}


void mutateNode(Node **headArray, int head, int index, int newValue){
	// Cycle through the linkedlist until index, with pointer p.
	Node *p = headArray[head];
	for(int i = 0; i < index; ++i){
		p = p->next;
	}
	// Mutate p->data to the newValue.
	p->data = newValue;
}

// Wrapper function for freeNode
void freeLists(Node **headArray){
	for(int i = 0; i < 10; ++i){
		freeNode(headArray[i]);
	}
}

void freeNode(Node *node){
	// Recursively checks if the node owns its successors or not
	// If it does delete the next node, then delete itself.
	// If it isn't, just delete itself.
	if (node == nullptr);
	else if (!(node->ownsSuccessor)) delete node;
	else {
		freeNode(node->next);
		delete node;
	}
}


