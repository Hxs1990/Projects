#ifndef _TNODE_H_
#define _TNODE_H_
#include <string>
struct TNode {
    // You must use these fields. 
    // Do not change these fields.
    std::string data;
    TNode *left, *right;
    
    // Size of the string represented by this nodes left subtree, 
    // plus it's own string data size.
    size_t size;

    TNode *parent; // you may or may not need this

    //you can add your own helper methods here

    // Returns a duplicate of the called Node
	TNode *duplicate() const;
	// Returns the total length of the current Node and all subNodes.
	unsigned int getLength() const;

};
// deletes the current TNode and all sub TNodes attached to freeTNode
void freeTNode(TNode *n);
#endif

