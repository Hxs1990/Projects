#include "tstring.h"
#include "tnode.h"
#include <iostream>

//Constructor for a TString given a string
TString::TString(const std::string &str):
	root{new TNode{str,nullptr,nullptr,str.length(),nullptr}},
		length{str.length()}{}

		//Copy constructor
		TString::TString(const TString &other):
			root{other.root->duplicate()},
				length{other.length}{}

				//Constructor for a TString given a TNode
				TString::TString(TNode *root):
					root{root->duplicate()},
						length{root->getLength()}{}

						//Destructor for a TString
						TString::~TString(){
							freeTNode(root);
							}

							//Concatenate method
							TString TString::operator+(const TString &rhs) const{
								// create a copy of *this and rhs to be the respective left and right
									TNode *left = root->duplicate();
										TNode *right = rhs.root->duplicate();
											// create a new mid empty node
												TNode *mid = new TNode{"",left,right,length,nullptr};
													// attach left and right to mid
														left->parent = mid;
															right->parent = mid;
																// Create a new TString by copying mid
																	TString toReturn = {mid};
																		freeTNode(mid);
																			return toReturn;
																			}

																			char &TString::operator[](const unsigned int index){
																				TNode *n = root;
																					bool found = false;
																						unsigned int updatedIndex = n->size-1;
																							//This while loop compares the updatedIndex with index
																								//NOTE: updatedIndex is treated as the last index in the string based
																									// on the current node. index is then compared with index of the string
																										// based on the start of the substring and then at the end of the substring
																											while(!found && n != nullptr){
																													if ( n->left && (index <= (updatedIndex - n->data.length()))){
																																updatedIndex -= n->data.length();
																																			n = n->left;
																																						if (n->right != nullptr) updatedIndex -= n->right->getLength();
																																								}
																																										else if (n->right && (index > updatedIndex)){
																																													n = n->right;
																																																updatedIndex += n->size; 
																																																		}
																																																				else{
																																																							found = true;
																																																									}
																																																										}
																																																											int relativeIndex = index - (updatedIndex - n->data.length()) - 1; 
																																																												return (n->data)[relativeIndex];
																																																												}


																																																												void TString::insert(const std::string &s, const unsigned int index){	
																																																													TNode *n = root;
																																																														unsigned int sLen = s.length();
																																																															unsigned int updatedIndex = n->size-1;
																																																																// mutate the node if the node is to be an empty node.
																																																																	if (length == 0){
																																																																			n->size = sLen;
																																																																					n->data = s;
																																																																							length += sLen;
																																																																								}
																																																																									// append the node on the far right side of the TString
																																																																										else if (index >= length){
																																																																												while(n->right){ n = n->right;}
																																																																														n->right = new TNode{s,nullptr,nullptr,sLen,n};
																																																																																length += sLen;
																																																																																	}
																																																																																		
																																																																																			else{
																																																																																					//This while loop compares the updatedIndex with index
																																																																																							//NOTE: updatedIndex is treated as the last index in the string based
																																																																																									// on the current node. index is then compared with index of the string
																																																																																											// based on the start of the substring and then at the end of the substring
																																																																																													bool found = false;
																																																																																														 	while(!found && n != nullptr){
																																																																																																		if ( n->left && (index <= (updatedIndex - n->data.length()))){
																																																																																																						updatedIndex -= n->data.length();
																																																																																																										n->size += sLen;
																																																																																																														n = n->left;
																																																																																																																		if (n->right != nullptr) updatedIndex -= n->right->getLength();
																																																																																																																					}
																																																																																																																								else if (n->right && (index > updatedIndex)){
																																																																																																																												n = n->right;
																																																																																																																																updatedIndex += n->size;
																																																																																																																																			}
																																																																																																																																						else{
																																																																																																																																										found = true;
																																																																																																																																													}
																																																																																																																																															}
																																																																																																																																																	// relativeIndex is the index referring to the index for n->data
																																																																																																																																																			int relativeIndex = index - (updatedIndex - n->data.length()) - 1;
																																																																																																																																																					// if relativeIndex not 0, then we split n->data into two sub TNodes
																																																																																																																																																							// and attach n accordingly with the new two sub TNodes.
																																																																																																																																																									// Finally mutating n to the desired node to insert.
																																																																																																																																																											if (relativeIndex){
																																																																																																																																																														std::string left = n->data.substr(0,relativeIndex);
																																																																																																																																																																	std::string right = n->data.substr(relativeIndex);
																																																																																																																																																																				TNode *splitLeft = new TNode{left,n->left,nullptr,
																																																																																																																																																																														(left.length()+(n->left == nullptr ? 0 : n->left->getLength())),n};
																																																																																																																																																																																	TNode *splitRight = new TNode{right,nullptr,n->right,right.length(),n};
																																																																																																																																																																																				n->left = splitLeft;
																																																																																																																																																																																							n->right = splitRight;
																																																																																																																																																																																										n->size = n->size - n->data.length() + splitLeft->size;
																																																																																																																																																																																													n->data = s;
																																																																																																																																																																																																n->size += sLen;
																																																																																																																																																																																																		}
																																																																																																																																																																																																				// Insert to the left if there is nothing there.
																																																																																																																																																																																																						else if(n->left == nullptr){
																																																																																																																																																																																																									TNode *newLeft = new TNode{s,n->left,nullptr,sLen,n};
																																																																																																																																																																																																												n->size += sLen;
																																																																																																																																																																																																															n->left = newLeft;
																																																																																																																																																																																																																	}
																																																																																																																																																																																																																			// Move to the left TNode and then immediately move to the right as much
																																																																																																																																																																																																																					// as possible until n->right == nullptr and then attach the node on 
																																																																																																																																																																																																																							// the right side.
																																																																																																																																																																																																																									else {
																																																																																																																																																																																																																												n->size +=sLen;
																																																																																																																																																																																																																															n = n->left;
																																																																																																																																																																																																																																		while(n->right){
																																																																																																																																																																																																																																						n = n->right;
																																																																																																																																																																																																																																									}
																																																																																																																																																																																																																																												TNode *newRight = new TNode{s,nullptr,nullptr,sLen,n};
																																																																																																																																																																																																																																															n->right = newRight;
																																																																																																																																																																																																																																																	}
																																																																																																																																																																																																																																																		length += sLen;
																																																																																																																																																																																																																																																			}
																																																																																																																																																																																																																																																			}


																																																																																																																																																																																																																																																			// Prints the data in the Node and its subnodes in order.
																																																																																																																																																																																																																																																			std::ostream& printInOrder(std::ostream& out, const TNode *n){
																																																																																																																																																																																																																																																				if(n == nullptr) return out;
																																																																																																																																																																																																																																																					printInOrder(out,n->left);
																																																																																																																																																																																																																																																						out << n->data;
																																																																																																																																																																																																																																																							printInOrder(out,n->right);
																																																																																																																																																																																																																																																								return out;
																																																																																																																																																																																																																																																								}

																																																																																																																																																																																																																																																								// Wrapper function for printInOrder
																																																																																																																																																																																																																																																								std::ostream& operator<<(std::ostream& out, const TString &t){
																																																																																																																																																																																																																																																									return printInOrder(out,t.root);
																																																																																																																																																																																																																																																									}


















