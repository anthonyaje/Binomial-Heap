#include "BinoHeap.h"
#ifndef BINONODE_H
#define BINONODE_H

class BinoNode{
public:
	BinoNode(int);				// Constructors
	BinoNode();
	~BinoNode();				// Destructors

	int data;					//Data Fields
	int degree;
	BinoNode* parent;
	BinoNode* lChild;
	BinoNode* rSibling;
};

BinoNode::BinoNode(){			// no Heap memory allocation in the class, 
	degree=0;					// So programmer should manage it in the usage of BinoNode
	lChild=nullptr; 
	rSibling=nullptr;
}				

BinoNode::BinoNode(int n){
	data = n;
	degree=0;
	lChild=nullptr; 
	rSibling=nullptr;
}				
			

BinoNode::~BinoNode(){};

#endif