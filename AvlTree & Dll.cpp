#include<iostream>
#include<string>
#include <algorithm>
using namespace std;


template<class T>
class dlist {                                                                            //Doubly linklist
public:
	struct Node {
	public:
		Node() {
			data = 0;
			next = NULL;
			prev = NULL;
		}
		Node(T d, Node* p, Node* n) {
			data = d;
			next = n;
			prev = p;
		}
	
		friend class avl;
		T data;
		Node* next;
		Node* prev;
		
	};
private:
	Node* head, * tail;
	class iterator {
	private:
		Node* current;
	public:
		iterator() {
			current = NULL;
		}
		iterator(Node* cur = NULL) {
			current = cur;
		}
		iterator& operator ++() {			//prefix ++
			if (current) {
				current = current->next;
			}
			return *this;
		}
		iterator& operator++(int) { //postfix
			iterator old = *this;
			++(*this);
			return old;
		}
		T& operator *() {                   //derefrence
			return current->data;
		}
		bool operator ==(const iterator& obj) {
			return current == obj.current;
		}
		bool operator !=(const iterator& obj) {
			return current != obj.current;
		}

	};
public:
	typedef iterator ite;
	ite begin() {
		return head;
	}
	ite end() {
		return tail->next;
	}
	dlist() {
		head = NULL;
		tail = NULL;
	}
	Node* insertAtHead(T value) {       /////////////////////
		//dNode * p;
		if (head != NULL) {

			Node* temp = new Node(value, NULL, head);
			head->prev = temp;
			head = temp;
		}
		else {
			head = tail = new Node(value, NULL, NULL);
		}
		return head;
		//ptr = &(head->data);
	//	cout << ptr;
		//ptr = p;
	}
	Node* insertAtTail(T value) {
		if (tail != NULL) {
			Node* temp = new Node(value, tail, NULL);
			tail->next = temp;
			tail = temp;
		}
		else {
			head = tail = new Node(value, NULL, NULL);
		}
		return tail;
	}
	void deleteFromHead() {
		if (head != NULL) {
			if (head == tail) {
				delete head;
				head = tail = 0;
			}
			else {
				Node* temp = head;
				head = temp->next;
				delete temp;
				head->prev = NULL;
			}
		}
		else {
			head = tail = NULL;
		}
	}
	void deleteFromTail() {
		if (tail != NULL) {
			if (head == tail) {
				delete head;
				head = tail = 0;
			}
			else {
				Node* temp = tail;
				tail = temp->prev;
				delete temp;
				tail->next = NULL;
			}
		}
	}

	void printForward() {
		Node* temp = head;
		while (temp != NULL){
			cout << temp->data << " ";
			temp = temp->next;
		}
	}
	void printReverse() {
		Node* temp = tail;
		while (temp != NULL) {
			cout << temp->data << " ";
			temp = temp->prev;
		}
	}
	T size() {
		Node* temp = head;
		T count = 0;
		while (temp != NULL) {
			count++;
			temp = temp->next;
		}
		return count;
	}
	T returnMiddle() {
		Node* temp = head;
		T count = 0;
		while (temp != NULL)
		{
			count++;
			temp = temp->next;
		}
		count = count / 2;
		Node* temp1 = head;
		for (int i = 0; i < count; i++) {
			temp1 = temp1->next;
		}
		return temp1->data;
	}
	bool isEmpty() {
		if (head == NULL && tail == NULL) {
			return true;
		}
		else
			return false;
	}
	T findMax() {
		Node* temp = head;
		T max = 0;

		while (temp != NULL) {
			if (temp->data > max) {
				max = temp->data;
			}
			temp = temp->next;
		}
		return max;
	}
	void InsertAfter(T val, T key) {
		Node* temp = head;
		bool found = false;
		while (temp != NULL) {
			if (temp->data == val) {
				found = true;
				break;
			}
			temp = temp->next;
		}
		if (found) {
			Node* temp2 = new Node(key, temp, temp->next);
			temp->next = temp2;
			temp->next->prev = temp2;
		}
		else {
			insertAtTail(key);
		}
	}
	void InsertBefore(T val, T key) {
		Node* temp = head;
		bool found = false;
		while (temp != NULL) {
			if (temp->data == val) {
				found = true;
				break;
			}
			temp = temp->next;
		}
		if (found) {
			Node* temp2 = new Node(key, temp->prev, temp);
			temp->prev->next = temp2;
			temp->prev = temp2;
		}
		else {
			insertAtTail(key);
		}
	}

	friend ostream& operator << (ostream& cout, dlist& obj) {
		iterator start = obj.begin();
		iterator end = obj.end();

		while (start != end) {
			cout << *start << " ";
			start++;
		}
		return cout;
	}
	T& operator *() {                   //derefrence
		return head->data;
	}
	void deleteb(Node* &temp,Node*  &temp1,Node* &b) {
		if (temp == NULL) {
			b = NULL;
			temp1->prev = NULL;
			head=temp1;
		}
		else if (temp1 == NULL) {
			b = NULL;
			temp->next = NULL;
			//head = temp;
		}
		else {
			temp->next = temp1;
			//head = temp;
			b = NULL;
		}
	}

	/*~dlist()
	{
		dNode* temp = NULL;
		while (head != NULL) {
			temp = head;
			head = head->next;
			temp=NULL;
		}
	}*/
};

class Books {
private:
	int ISSN;
	string title;
	dlist<string> authors;
	int noOfcopiesReferencebook;
	int noOfcopiesissuablebook;
public:
	Books() {
		ISSN = 0;
		title = " ";
		noOfcopiesReferencebook = 0;
		noOfcopiesissuablebook = 0;
	}
	Books(int issn, string t, string name[],int size, int reference, int issuable) {
		ISSN = issn;
		title = t;
		string m;
		string k;
		for (int i = 0; i < size; i++) {
			authors.insertAtHead(name[i]);
		}
		noOfcopiesReferencebook = reference;
		noOfcopiesissuablebook = issuable;
	}
	void setTitle(string r) {
		title = r;
	}
	string getTitle(){
		return title;
	}
	void setRef(int ref) {
		noOfcopiesReferencebook = ref;
	}
	int getRef() {
		return noOfcopiesReferencebook;
	}
	void setIss(int iss) {
		noOfcopiesissuablebook = iss;
	}
	int getIss() {
		return noOfcopiesissuablebook;
	}
	void setAuthor(string name) {
		authors.insertAtHead(name);
	}
	friend ostream& operator << (ostream& cout, Books& obj) {

		cout << " ISSN:  " << obj.ISSN << endl;
		cout << "Title: " << obj.title << endl;
		cout << "Authors: " << obj.authors << endl;
		cout << "Number of Refrence books: " << obj.noOfcopiesReferencebook << endl;
		cout << "Number of Issuable books: " << obj.noOfcopiesissuablebook << endl;
		return cout;
	}
};

template<class T>
class AVL {                                                                          // AVL
private:
	struct Node {
		T data;
		int height;
		Node* left;
		Node* right;
		dlist<Books>::Node* pointer;
		Node() {
			data = 0;
			left = NULL;
			right = NULL;
			height = 0;
		}
		Node(T d) {
			data = d;
			left = NULL;
			right = NULL;

		}
	};
	Node* root;
public:
	AVL() {
		root = NULL;
	}
	void  rightRotation(Node*& x) {
		Node* orphan = x->left->right;
		Node* y = x->left;
		y->right = x;
		x->left = orphan;
		x->height = height(x);
		y->height = height(y);
		x = y;
	}
	void leftRotation(Node*& x) {
		Node* orphan = x->right->left;
		Node* y = x->right;
		y->left = x;
		x->right = orphan;
		x->height = height(x);
		y->height = height(y);
		x = y;
	}

	void doubleLeftRightRotation(Node*& x) {
		leftRotation(x->left);
		rightRotation(x);
	}

	void doubleRightLeftRotation(Node*& x) {
		rightRotation(x->right);
		leftRotation(x);
	}
	void balance(Node*& t){
		if (t == NULL)
			return;
		int m = height(t->left) - height(t->right);
		int  n = height(t->right) - height(t->left);
		if (height(t->left) - height(t->right) == 2)                            // negative -> right rotation
			if (height(t->left->left) >= height(t->left->right))
				rightRotation(t);
			else
				doubleLeftRightRotation(t);

		else if (height(t->right) - height(t->left) == 2)                      // positive -> left rotation
			if (height(t->right->right) >= height(t->right->left))
				leftRotation(t);
			else
				doubleRightLeftRotation(t);
	}
	int height(Node* nptr){
		if (nptr == NULL){
			return -1;
		}
		else{
			int left_height = height(nptr->left);
			int right_height = height(nptr->right);
			if (left_height > right_height){
				return left_height + 1;
			}
			else{
				return right_height + 1;
			}
		}
	}
	T find_max(Node*& leaf){
		if (leaf == NULL){
			return -1;
		}
		else if (leaf->right == NULL){
			return leaf->data;
		}
		else{
			return find_max(leaf->right);
		}
	}
	void insertR(T n, int pt, dlist<Books> &d, Books b) {
		insertREC(n, root, d, b);
	}
	void insertREC(T n, Node*& current, dlist<Books> &d, Books b) {                 
		if (current == NULL) {
		
			current = new Node(n);
			current->pointer = d.insertAtHead(b);                  //Avl pointer points toward ddl containing same ISSN
		}
		if (current->data > n) {
			if (current->left == NULL) {
				current->left = new Node(n);
				current->left->pointer =d.insertAtHead(b);       //Avl pointer points toward ddl containing same ISSN
			}
			else {
				insertREC(n, current->left, d, b);
			}
		}
		else if (current->data < n) {
			if (current->right == NULL) {
				current->right = new Node(n);
				current->right->pointer = d.insertAtTail(b);     //Avl pointer points toward ddl containing same ISSN
			}
			else {
				insertREC(n, current->right, d, b);
			}
		}
		balance(current);
	}

		void deleteIte(T n) {
			Node* current = root;
			Node* prev = NULL;
			while (current != NULL) {
				if (current->data == n) {         //When found
					break;
				}
				else if (current->data > n) {
					prev = current;
					current = current->left;
				}
				else if (current->data < n) {
					prev = current;
					current = current->right;
				}
			}
			if (current->left == NULL && current->right == NULL) { //last node
				if (prev->left == current) {   //parent can have two child 
					prev->left = NULL;
				}
				else if (prev->right == current) {
					prev->right = NULL;
				}
				delete current;
			}

			else if (current->left == NULL) {   //Has only one child && on right side
				if (prev->right == current) {
					prev->right = current->right;
					current->right = NULL;
				}
				else if (prev->left == current) {
					prev->left = current->right;
					current->right = NULL;
				}
				delete current;
			}
			else if (current->right == NULL) {   //Has only one child && on left side
				if (prev->right == current) {
					prev->right = current->left;
					current->left = NULL;
				}
				else if (prev->left == current) {
					prev->left = current->left;
					current->left = NULL;
				}
				delete current;
			}
			else {                                //Two children
				Node* _parent = current;
				Node* max_left = current->left;           // max node 
				while (max_left->right != NULL) {
					_parent = max_left;
					max_left = max_left->right;
				}
				current->data = max_left->data;           // root gets max element from left side

				if (_parent->right == max_left) {          //  if there exists  a child of maximum ... it will be updated to max
					_parent->right = max_left->left;
				}
				else {
					_parent->left = max_left->left;
				}
				delete max_left;                        // max element gets deleted
			}
			balance(root);
		}

		bool find(T n, int num, dlist<Books>& d) {
		Node* current = root;
		bool found = false;
		if (root != NULL) {
			while (current != NULL) {
				if (current->data > n) {
					if (current->left != NULL) {
						if (current->left->data == n) {
							found = true;
							current = current->left;

							if (num == 3) {
								updaterecord(current->pointer->data);                      //if user enter 3 it it will update record
							}
							else if (num == 2) {
								Review (current->pointer->data);                          //if user enter 2 it it will display record of ISSN
							}
							else if (num == 4) {
								delBook(current->pointer,d);
								deleteIte(current->data);
							}
							return true;
						}
						else {
							current = current->left;
						}
					}
					else {
						cout << "ISSN does not exists\n";
						return false;
					}
				}
				else if (current->data < n) {
					if (current->right != NULL) {

						if (current->right->data == n) {
							found = true;
							current = current->right;
							if (num == 3) {                                                 //if user enter 3 it it will update record
								updaterecord(current->pointer->data);
							}
							else if (num == 2) {
								Review(current->pointer->data);                              //if user enter 2 it it will display record of ISSN
							}
							else if (num == 4) {
								delBook(current->pointer,  d);
								deleteIte(current->data);
							}
							return true;
						}
						else {
							current = current->right;
						}
					}
					else {
						cout << "ISSN does not exists\n";
						return false;
					}
				}
			}
		}
		cout << "ISSN does not exists\n";
	}
	void delBook(dlist<Books>::Node*  &b, dlist<Books>& d){


		dlist<Books>::Node* temp = b->prev;
		dlist<Books>::Node* temp1 = b->next;

		d.deleteb(temp, temp1,b);
		int m = 0;
		/*if (temp == NULL) {
			b = NULL;
			temp1->prev = NULL;
			int m=0;
		}
		else if (temp1 == NULL) {
			b = NULL;
			temp->next = NULL;
		}
		else {
			temp->next = temp1;
			b = NULL;
		}*/
		
		}
	void updaterecord(Books data) {
		cout << "Enter \n 1.Title \n 2.Refrencecopies \n 3.Issue copies\n 4.authors ";
		int n;
		cin >> n;
		if (n == 1) {
			cout << "Enter title: ";
			string n;
	//		cin.getline(n);
			cout << endl;
			data.setTitle(n);
		}
		else if (n == 2){
			cout << "Enter Refrence copies: ";
			int m;
			cin >> m;
			cout << endl;
			data.setRef(m);
		}
		else if (n == 3) {
			cout << " Enter Issue copies:";
			int m;
			cin >> m;
			cout << endl;
			data.setIss(m);
		}
		else {
			cout << "Enter number of authors";
			int n;
			string name;
			cout << "Enter number of authors you want to add:";
			cin >> n;
			cout << endl;
			for (int i = 0; i < n; i++) {
				cin >> name;
				data.setAuthor(name);
			}
		}
		cout << data;

	}
	void Review(Books data) {
		cout << "The book record of the given ISSN is: \n" << data << endl;
	}

	void indisplay() {
		InOrder(root);
	}
	void postdisplay() {
		postOrder(root);
	}
	void predisplay() {
		preOrder(root);
	}
	void preOrder(Node* t) {
		if (t) {
			visit(t);
			preOrder(t->left);
			preOrder(t->right);
		}
	}
	void postOrder(Node* t) {
		if (t) {	
			postOrder(t->left);
			postOrder(t->right);
			visit(t);
		}
	}
	void InOrder(Node* t) {
		if (t) {
			InOrder(t->left);
			visit(t);
			InOrder(t->right);
		}
	}
	void visit(Node* t) {

		cout << t->data << "  "<<endl; 
		cout << t->pointer->data;
	}
	friend ostream& operator << (ostream& cout, AVL& t) {
		
		cout << t->data << "  " << endl;
		cout << t->pointer->data;
		//cout << t->pointer->data;
		return cout;
	}
};



class implement {
private:
	AVL<int> record;
	dlist<Books> bookrecord;
	Books book;
public:
	
	void create(int ISSN, int ref, int iss, string* author,int s, string t) {    //Insert new book
		Books b(ISSN, t, author,s, ref, iss);
		record.insertR(ISSN, 0, bookrecord, b);

	}
	void display() {
		record.indisplay();
	//	record.predisplay();
	//	record.postdisplay();
		cout << " BOOK LIST:\n";
		bookrecord.printForward();
		cout << endl;
	}
	void review(int ISSN) {
		
		cout << "REVIEW: \n"<< record.find(ISSN, 2, bookrecord);
		cout << endl;
		
	}
	void update(int ISSN) {

		cout << "Update: \n"<< record.find(ISSN, 3, bookrecord);
		cout << endl;
		
	}
	void deleter(int ISSN) {

		cout << "Delete: "<< record.find(ISSN, 4, bookrecord);
		//bookrecord.printForward();
	}
	
	void createbbok() {
		int issn, iss, ref,n;
		string name[] = { "ayesha","eman","Saad" };
	
		cout << "Enter number of books you want to create";
		cin >> n;
		for (int i = 0; i < n; i++) {
			cout << "Enter ISSN: ";
			cin >> issn;
			cout << endl;
			cout << " Enter refrence:";
			cin >> ref;
			cout << endl;
			cout << "Enter Issuedate:";
			cin >> iss;
			cout << endl;
			string book;
			cout << "Enter book:";
			cin >> book;
			cout << endl;
			create(issn, ref, iss, name, 3, book);
		}
	}
	void library() {
		bookrecord.printForward();
	}
};


int main()
{
	implement  imp;
	//imp.createbbok();
	string name[] = { "ayesha","eman","Saad" };
	imp.create(7, 0, 9, name,3, "Narnia");
	imp.create(77, 9, 8, name,3, "c++");
	imp.create(3, 8, 7, name,3, "The tale of two cities");
	imp.create(4, 7, 6, name,3, "Prisoner of Azkaban");
	imp.create(5, 7, 6, name, 3, "Ok");
	imp.create(6, 7, 6, name, 3, "He who must not be named");
	imp.create(4, 7, 6, name, 3, "e");
	imp.display();
	cout << "Enter  \n 2.Review \n 3.Update \n 4.Delete ";
	int n;
	cin >> n;
	if (n == 2) {
		imp.review(225);
	}
	else if (n == 3) {
		imp.update(3);
	}
	else if (n == 4) {  
		imp.deleter(77);
		cout << " DOUBLE LINKLIST AFTER DELETION: \n\n\n\n";
		imp.library();
	}
	


}