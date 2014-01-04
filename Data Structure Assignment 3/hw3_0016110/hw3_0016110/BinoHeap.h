#ifndef BINOHEAP_H
#define BINOHEAP_H
#include "BinoNode.h"
#include "dequeue.h"

using namespace std;

int pow(int n, int x){ if(x<=0)return 1; else return n*pow(n,x-1); }		//compute the n^x recursively

class BinoHeap{								// Binomial Heap Data Structure
public:	
	friend BinoNode;						// friend of class BinoNode defined in other header file
	BinoHeap();								// ctor
	~BinoHeap();							// dtor
	BinoNode* getMin();						// return a pointer to minimum BinoNode
	void insert(BinoHeap*, BinoNode*);		// insert a node to the heap
	void deleteMin();						// delete the min node and reconstruct the heap.
	int size();								// return he number of nodes in the heap
	void postOrder();						// transverse the heap in post-order manner
	void postOrder(BinoNode*);				// recursive function for postorder
	void inOrder();							// transverse the heap in in-order manner
	void inOrder(BinoNode* );				// recursive function for in-order
	bool isEmpty();							// check whether the heap is empty or not
	BinoHeap* bHeapUnion(BinoHeap* H1, BinoHeap* H2);	// return a union of H1,H2  
														// NOTE: after the union of H1,H2. H1 and H2 no longer exist independently
private:
	BinoNode* mergeHeap(BinoHeap* H1, BinoHeap* H2);	// merge the two heaps. the resulting heap has non-decreasing degree of rootlist
 	void bLink(BinoNode* y, BinoNode* z);				// link the two root of binomial tree that has the same degree
	BinoNode* head;
};

BinoHeap::BinoHeap() :head(nullptr){}					// initially head points to null

BinoHeap::~BinoHeap(){}									// destructor

bool BinoHeap::isEmpty(){
return head==nullptr; 
}

BinoNode* BinoHeap::getMin(){
	if(isEmpty()){
		throw "heap is empty";
		return 0;
	}
	else{
		BinoNode* iter = head;							// compare the root list
		BinoNode* y = iter;
		if(head==nullptr){return nullptr;}
		else{
			int bucket=head->data;
			while(iter != nullptr){
				if(iter->data < bucket){ 
					bucket = iter->data;
					y=iter;
				}
				iter = iter->rSibling;
			}
		}
		return y;										// return the pointer to min node
	}
}

BinoNode* BinoHeap::mergeHeap(BinoHeap* H1, BinoHeap* H2)
{
	BinoNode* iter1;
	BinoNode* iter2;
	BinoNode* head;
	
	iter1 = H1->head;
	iter2 = H2->head;
	if(iter1 != nullptr && iter2 != nullptr){
		if(iter1->degree <= iter2->degree) head = H1->head;		// head points to the smallest degree of H1 H2
		else head = H2->head;
		while(iter1 != nullptr && iter2 != nullptr )			// root list pointer manipulation: combine H1 H2
		{							
			while(iter1->degree <= iter2->degree)				// while the degree of one is less than other, do nothing 
			{													// else change the sibling of to the nodes on the other heap
				BinoNode* ftr = iter1->rSibling; 
				if(ftr != nullptr){								// look at the future! to make sure that we do not encounter null->rSibling 
					if(ftr->degree <= iter2->degree){ 
						iter1 = iter1->rSibling;
					}
					else {
						BinoNode* temp = iter1->rSibling;
						iter1->rSibling =iter2;
						iter1=temp;
					}
				}
				else{
					iter1->rSibling = iter2;
					iter1 = nullptr;
				}
				if(iter1 == nullptr || iter2 ==nullptr)			// one of H1, H2 has no more rootlist than we poin to the remaining nodelist of the other 
					break;
			}

			while(iter1 != nullptr && iter2 != nullptr && iter2->degree <= iter1->degree ) // similar as above just in case degree of first root H2 <= degree H1
			{
				BinoNode* ftr = iter2->rSibling; 
				if(ftr != nullptr){
					if(ftr->degree <= iter1->degree){ 
						iter2 = iter2->rSibling;
					}
					else {
						BinoNode* temp = iter2->rSibling;
						iter2->rSibling =iter1;
						iter2=temp;
					}
				}
				else {
					iter2->rSibling = iter1;
					iter2=nullptr;
				}
				if(iter2 == nullptr || iter1 ==nullptr) 
					break;
			}
		}
	return head;									// return the pointer to the beginning
	}

	else if(iter1 == nullptr ) return iter2;		// H1 is empty return pointer H2
	else return iter1;			
	
}

void BinoHeap::bLink(BinoNode* y, BinoNode* z)		// link binomial tree with same degree
{
	y->parent = z;									// make y as child of z 
	y->rSibling = z->lChild;						// make y siblings to leftchild of z 
	z->lChild = y;									// then y is the leftchild of z
	z->degree += 1;									// degree og z incease by 1

}

BinoHeap* BinoHeap::bHeapUnion(BinoHeap* H1, BinoHeap* H2)		// unioin two binomial heaps
{
	BinoHeap* H = new BinoHeap;

	H->head = mergeHeap(H1,H2);				// merge the two heaps
	if(H->head == nullptr) return H;
	BinoNode* prevx = nullptr;
	BinoNode* x = H->head;
	BinoNode* nextx = x->rSibling;
	while(nextx != nullptr)					// do the adjustment on every roots list
	{										// based on the given algorithm
		if((x->degree != nextx->degree) 
			|| (nextx->rSibling != nullptr && nextx->rSibling->degree == x->degree))
		{
			prevx = x;
			x=nextx;
		}
		else{
			if(x->data <= nextx->data){
				x->rSibling = nextx->rSibling;
				bLink(nextx,x);
			}
			else{
				if(prevx == nullptr){
					H->head = nextx;
				}
				else{
					prevx->rSibling =nextx;
				}
				bLink(x,nextx);
				x = nextx;
			}
		}
		nextx = x->rSibling;
	}

	return H;
}

void BinoHeap::insert(BinoHeap* H, BinoNode* n){	// insert a node to the BinoHeap
	BinoHeap* H1 = new BinoHeap;					// make a BinoHeap consist of 1 node
	n->parent = nullptr;							// then union it to the Heap
	n->lChild = nullptr;
	n->rSibling = nullptr;
	n->degree = 0;
	H1->head = n;
	H-> ~BinoHeap();								// destroy the prevous heap
	*H = *bHeapUnion(this, H1);						// return the inserted BinoHeap
}

int BinoHeap::size(){								// computers total nodes in BinoHeap
	BinoNode* it = head;
	int temp = 0;
	while(it != nullptr){							// notice that 2^k is total node in Bk tree
		temp += pow(2,it->degree);
		it=it->rSibling;
	}
return temp;
}

void BinoHeap::inOrder()							// Inorder transversal of the heap 
{
	BinoNode* p = head;
	while( p != nullptr){
		inOrder(p);									// call function overloading (running horse)
		p = p->rSibling;
	}
}

void BinoHeap::inOrder(BinoNode* root)				// recursively transverse the heap
{
	if(root != nullptr ){
		inOrder(root->lChild);						// go to the deepest leftchild
		if(root->lChild != nullptr){
			inOrder(root->lChild->rSibling);		// go to the sibling if any
			BinoNode* ptr=root->lChild->rSibling;
			while(ptr != nullptr){					// transverse further to the right siblings
				inOrder(ptr->rSibling);
				ptr = ptr->rSibling;
			}
		}
		cout<<root->data<<" ";						// display the data od the node
	}
}

void BinoHeap::postOrder()							// post order transversal
{
	BinoNode* p = head;
	while(p != nullptr){
		postOrder(p);								// running horse to pring each binomial tree in the rootlist
	if(p->rSibling != nullptr) p = p->rSibling;
	else break;
	}
}

void BinoHeap::postOrder(BinoNode* root)			// implemented by using dequeue I defined  before
{
	deque<BinoNode*> deq;							// push the node to the deq when transverrsing down to the lChild 
	deque<BinoNode*> deq2;							// and pop it out one by one. Once a node is popped-out, check the right sibling
	BinoNode* p;									// push the right sibling to the other deque (deq2) untill end of right sibling
	BinoNode* q;									// however, if the sibling have a lchild we transverse the post order of leftchild first
	p=root;											// then pop-out and print out the nod?'s data in deq2 (Fist In Last Out)
	while(p != nullptr){ 
		deq.push_front(p);
		if(p->lChild == nullptr){
			break;
		}
		else p = p->lChild;
	}
	while(!deq.empty()){				// p here points to the last lChild (not null)
		q=p;
		while(q!= nullptr){ 
			deq2.push_front(q);
			if(deq.size() == 1 || q->rSibling == nullptr) break;
			else{
				q = q->rSibling;
				if(q->lChild != nullptr ) postOrder(q->lChild);
			}
		}	
		while(!deq2.empty()){ 
			cout<<deq2.front()->data<<" "; 
			deq2.pop_front();
		}
		if(p->parent != nullptr) p = p->parent;
		deq.pop_front();
	}

}

void BinoHeap::deleteMin(){				// delete the min node in the Binomial Heap;
	BinoNode* minPos = getMin();
	if(head != nullptr){
		if(minPos == head){				// if the min element is at the first position
			head = minPos->rSibling;	// pass the head[H] to the next root (lSibling)
		}
		else{
			BinoNode*  p=head;			
			while(p->rSibling != minPos){ p = p->rSibling; }		// p points to the position minPos-1
			p->rSibling = minPos->rSibling;					
		}
	}
	BinoNode* x = minPos->lChild;

	deque<BinoNode*> deq;				// user defined deque to help reverse the order of linkedlist of children x
	while(x != nullptr){
		deq.push_front(x);				// push.front
		x = x->rSibling;
	}
	BinoHeap* H1 = new BinoHeap;		// create another heap to hold the reversed order
	BinoNode* jalan;					// 'jalan' is a variable's name
	jalan = deq.front();				// pop.front
	deq.pop_front();
	H1->head = jalan;
	while(!deq.empty()){    
		jalan->rSibling = deq.front();	
		jalan = jalan->rSibling;
		jalan->parent=nullptr;
		deq.pop_front();
	}
	jalan->rSibling=nullptr;

	*this = *bHeapUnion(this, H1);
	delete H1;
}

#endif