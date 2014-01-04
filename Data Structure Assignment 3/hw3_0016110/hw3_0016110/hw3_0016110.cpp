#include <iostream>
#include <cstdio>
#include "BinoHeap.h"


using namespace std;

void eatline(){
	int x;
	while((x=getchar()) == ' ' ){;}
	ungetc(x,stdin);
}

int main (char argc, char* argv[])
{
	// Initialize myHeap1 
	//BinoHeap* myHeap = new BinoHeap;				// create an objec BinoHeap
	//int arr[5] = {4,10,2,5,7};						// initializers
	//for(int i=0;i<5;i++){
	//	myHeap->insert(myHeap,new BinoNode(arr[i]));	// create a BinoNode object and insert it 1 by 1 to the BinoHeap
	//}
	//   
	// Initialize myHeap2 
	//BinoHeap* myHeap2 = new BinoHeap;				// another Binomial heap
	//int arr2[7] = {12,8,11,6,1,9,3};
	//for(int i=0;i<7;i++){
	//	myHeap2->insert(myHeap2,new BinoNode(arr2[i]));
	//}

	int n;
	int x;
	BinoHeap* myHeap = new BinoHeap;				// create an objec BinoHeap
	BinoHeap* myHeap2 = new BinoHeap;				// another Binomial heap
	
	cout<<"INPUT"<<endl;
	n = getchar() - 48;
 	for(int i=0;i<n;i++){
		eatline();
		int p=0;
		x=getchar();
		while(x != ' ' && x != '\n')
		{
			ungetc(x,stdin);
			x = getchar() - 48;
			p = p*10 + x;
			x=getchar();
		}
		myHeap->insert(myHeap,new BinoNode(p));
	}
	
	cout<<"INPUT"<<endl;
	n = getchar() - 48;
 	for(int i=0;i<n;i++){
		eatline();
		int p=0;
		x=getchar();
		while(x!=' ' && x!='\n' && x!='\r')
		{
			ungetc(x,stdin);
			x = getchar() - 48;
			p = p*10 + x;
			x=getchar();
		}
		myHeap2->insert(myHeap2,new BinoNode(p));
	}

	// myHeap1
	cout<<"\nTest postOrder myHeap1:\t";
	myHeap->postOrder();							// display the BinoHeap by Post-Order Transversal 
 	cout<<"\nTest inOrder myHeap1:\t";
	myHeap->inOrder();								// display the BinoHeap by In-Order Transversal
	cout<<"\nSize: \t"<<myHeap->size()<<endl;

	//myHeap2
	cout<<"\nTest postOrder myHeap2:\t";
	myHeap2->postOrder();
	cout<<"\nTest Inorder myHeap2: \t";
	myHeap2->inOrder();
	cout<<"\nSize: "<<myHeap2->size()<<endl;


	// myHeap 3 union of myHeap and myHeap2
	BinoHeap* myHeap3 = new BinoHeap;							// BinoHeap myHeap3
	myHeap3 = myHeap3->bHeapUnion(myHeap,myHeap2);				// union from the previous Heaps
	cout<<"\nTest postOrder myHeap1 union myHeap: "<<endl;
	myHeap3->postOrder();
	cout<<"\nTest Inorder myHeap1 union myHeap2: "<<endl;
	myHeap3->inOrder();
	cout<<"\nSize: "<<myHeap3->size()<<endl;

	// Get and Delete the minimum
	cout<<"getMin(): "<<myHeap3->getMin()->data<<endl;;
	cout<<"\nAfter delete min:";
	myHeap3->deleteMin();
	cout<<"\nTest myHeap1 union myHeap2 postOrder after delete: "<<endl;
	myHeap3->postOrder();
	cout<<"\nTest myHeap1 union myHeap2 Inorder after delete: "<<endl;
	myHeap3->inOrder();
	cout<<endl;
	cout<<"size: "<<myHeap3->size()<<endl;



	system("pause");
	return 0;
}