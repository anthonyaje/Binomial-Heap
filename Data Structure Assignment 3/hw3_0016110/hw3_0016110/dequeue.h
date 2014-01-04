template<typename T>
class deque { 
public:
// types
	typedef T value_type;
	typedef size_t size_type;
	typedef T& reference;
	typedef const T& const_reference;
// ctor/copy ctor/dtor
	deque();
	deque(const deque&);
	deque(deque&&);
	~deque();
// capacity
	size_type size() const;
	bool empty() const;
// modifiers 
	void push_front(const T&); 
	void push_front(T&&); 
	void push_back(const T&);
	void push_back(T&&); 
	void pop_front(); 
	void pop_back();
// element access
	reference front(); 
	const_reference front() const; 
	reference back(); 
	const_reference back() const;
private:
	struct node;
	node *head;
	size_type _size;
};

template<typename T>
struct deque<T>::node {
	node(const T&,node*,node*);
	node(T&&,node*,node*);
	T datum;
	node *pred,*succ;
};

template<typename T>
deque<T>::node::node(const T& d,node* p,node* s) 
: datum(d), pred(p), succ(s) 
{}

template<typename T>
deque<T>::node::node(T&& d,node* p,node* s) 
: datum(std::move(d)), pred(p), succ(s) 
{}

template<typename T>    
deque<T>::deque()
: head((node*)operator new(sizeof(node))), _size(0)
{ 
	head->pred=head->succ=head; 
}

template<typename T>
deque<T>::~deque() 
{
	while (!empty()) pop_back();
	operator delete(head);
}

template<typename T>
void deque<T>::push_front(const T& d)
{
	head->succ=new node(d,head,head->succ);
	head->succ->succ->pred=head->succ;
	_size++;
}

template<typename T>
void deque<T>::push_front(T&& d)
{
	head->succ=new node(std::move(d),head,head->succ);
	head->succ->succ->pred=head->succ;
	_size++;
}

template<typename T>
void deque<T>::push_back(const T& d)
{
	head->pred->succ=new node(d,head->pred,head);
	head->pred=head->pred->succ;
	_size++;
}

template<typename T>
void deque<T>::push_back(T&& d)
{
	head->pred->succ=new node(std::move(d),head->pred,head);
	head->pred=head->pred->succ;
	_size++;
}

template<typename T>
void deque<T>::pop_front()
{
	head->succ=head->succ->succ;
	delete head->succ->pred;
	head->succ->pred=head;
	_size--; 
}

template<typename T>
void deque<T>::pop_back()
{
	head->pred=head->pred->pred;
	delete head->pred->succ;
	head->pred->succ=head;
	_size--;
}

template<typename T>
deque<T>::deque(const deque<T>& rhs)
: head((node*)operator new(sizeof(node))), _size(0)  // 1
{ 
	head->pred=head->succ=head;  // This and line 1 may be replaced by a delegating ctor in GNU C++.
	node* p=rhs.head->succ;
	while (p!=rhs.head) {
		push_back(p->datum); p=p->succ;
	}
}

template<typename T>
deque<T>::deque(deque<T>&& rhs)
: head((node*)operator new(sizeof(node))), _size(0)  // 2
{ 
	head->pred=head->succ=head;   // This and line 2 may be replaced by a delegating ctor in GNU C++.
	if (!rhs.empty()) {
		head->pred=rhs.head->pred;
		head->pred->succ=head;
		head->succ=rhs.head->succ;
		head->succ->pred=head;
		rhs.head->pred=rhs.head->succ=rhs.head;
		_size=rhs._size;
		rhs._size=0;
	}
}

template<typename T>
typename deque<T>::size_type deque<T>::size() const { return _size; }

template<typename T>
bool deque<T>::empty() const { return _size==0; }

template<typename T>
typename deque<T>::reference deque<T>::front() { return head->succ->datum; }

template<typename T>
typename deque<T>::const_reference deque<T>::front() const { return head->succ->datum; }

template<typename T>
typename deque<T>::reference deque<T>::back() { return head->pred->datum; }   

template<typename T> 
typename deque<T>::const_reference deque<T>::back() const { return head->pred->datum; }

