#include <iostream>
#include<string.h>
#include<string>
#include <vector>
#include<ctime>
#include <conio.h>
#include<list>
using namespace std;


class Books {
private:
	int ISSN;
	string title;
	string authors[10];
	int noOfcopiesReferencebook;
	int noOfcopiesissuablebook;
public:
	Books() {
		ISSN = 0;
		title = " ";
		noOfcopiesReferencebook = 0;
		noOfcopiesissuablebook = 0;
	}
	Books(int issn, string t, string name[], int size, int reference, int issuable) {
		ISSN = issn;
		title = t;
		string m;
		string k;
		for (int i = 0; i < size; i++) {
			//authors.push_front(name[i]);

			authors[i] = name[i];
		}
		authors[size] = "end";
		noOfcopiesReferencebook = reference;
		noOfcopiesissuablebook = issuable;
	}
	void setTitle(string r) {
		title = r;
	}
	string getTitle() {
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
	void setIssn(int iss) {
		ISSN = iss;
	}
	int getIssn() {
		return ISSN;
	}
	void setAuthor(string name, int i) {
		authors[i] = name;
	}
	friend ostream& operator << (ostream& cout, Books& obj) {

		cout << "\n\t\tISSN :  " << obj.ISSN << endl;
		cout << "\t\tTitle : " << obj.title << endl;

		cout << "\t\tAuthors: ";
		int i = 0;
		while (obj.authors[i] != "end") {
			cout << obj.authors[i++] << "    ";
		}
		cout << endl;
		cout << "\t\tNumber of Refrence books : " << obj.noOfcopiesReferencebook << endl;
		cout << "\t\tNumber of Issuable books : " << obj.noOfcopiesissuablebook << endl;
		return cout;
	}
};

template <typename v>
class HashMap
{
private:
	vector<v> hashVector;
	list<v> obj;
	int currentElements;

public:
	HashMap() : hashVector(10) {
		this->currentElements = 0;
	}
	HashMap(int const capacity) {
		if (capacity < 1)
			cout << endl << "Capacity is less than 0" << endl;

		hashVector.resize(10);
		this->currentElements = 0;
	}
	int universalHash(int const key) {

		srand(key);
		int p = rand() % key + key;                                              //Prime number greater than key
		while (!isPrime(p)) {                                                    //if it is not a prime number

			p = rand() % key + key;
		}

		int a = rand() % key;                                                      //Generates a less than p
		int b = rand() % key;                                                      //Generates a less than p
		while (a >= p || b >= p) {                                                //Generates a and b again if greater than p
			int a = rand() % key;
			int b = rand() % key;
		}

		int index;
		index = (((a * key) + b) % p) % hashVector.size();                         //Universal Hash Function
		return index;
	}

	bool isPrime(int& n) {

		if (n <= 1)  return false;
		if (n <= 3)  return true;

		if (n % 2 == 0 || n % 3 == 0) return false;

		for (int i = 5; i * i <= n; i = i + 6)
			if (n % i == 0 || n % (i + 2) == 0)
				return false;

		return true;
	}
	void insert(Books b) {
		int keyIndex = universalHash(b.getIssn());                                                 //HashFunction		
		hashVector[keyIndex].push_back(b);                                                          //Will put book at the respective index if tht index is filled will put it in list form
		currentElements++;
	}
	bool deleteKey(int issn) {
		int keyIndex = universalHash(issn);

		list<Books> ::iterator i;
		for (i = hashVector[keyIndex].begin(); i != hashVector[keyIndex].end(); ++i) {                     //Iterator will iterate through list of Each HashvectorTable
			Books book = *i;
			if (book.getIssn() == issn) {
				hashVector[keyIndex].erase(i);
				return true;
			}
		}
		return false;

	}
	bool upDateRecord(int issn) {
		int keyIndex = universalHash(issn);

		list<Books> ::iterator i;
		for (i = hashVector[keyIndex].begin(); i != hashVector[keyIndex].end(); ++i) {                        //Iterator will iterate through list of Each HashvectorTable
			Books book = *i;
			if (book.getIssn() == issn) {                                                                     //When key is found it will update
				updaterecord(*i);
				return true;
			}
		}
		return false;
	}
	void updaterecord(Books& data) {
		cout << "Enter \n 1.Title \n 2.Refrencecopies \n 3.Issue copies\n 4.authors ";
		int n;
		cin >> n;
		if (n == 1) {
			cout << "Enter title: ";
			string m;
			cin.ignore();
			getline(cin, m);
			cout << endl;
			data.setTitle(m);
		}
		else if (n == 2) {
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
			int n, temp;
			string name;
			cout << "Enter number of authors you want to add:";
			cin >> n;
			cout << endl;
			for (int i = 0; i < n; i++) {
				cin >> name;
				data.setAuthor(name, i);
				temp = i;
			}
			data.setAuthor("end", temp++);

		}
		cout << data;

	}
	bool ReviewBook(int issn) {
		int keyIndex = universalHash(issn);
		list<Books> ::iterator i;
		for (i = hashVector[keyIndex].begin(); i != hashVector[keyIndex].end(); ++i) {                   //Iterator will iterate through list of Each HashvectorTable
			Books book = *i;
			if (book.getIssn() == issn) {
				cout << *i;
				return true;
			}
		}
		return false;
	}
	void display() {

		list<Books> ::iterator it;
		for (int index = 0; index < hashVector.size(); index++) {
			cout << "Index - " << index << "  : ";
			for (it = hashVector[index].begin(); it != hashVector[index].end(); ++it) {                    //Iterator will iterate through list of Each HashvectorTable
				cout << *it;
			}
			cout << endl;
		}

	}


};

class implement {
private:

	Books book;

	HashMap<list<Books>> obj;
public:

	void create(int ISSN, int ref, int iss, string* author, int s, string t) {    //Insert new book
		Books b(ISSN, t, author, s, ref, iss);
		obj.insert(b);

	}
	void display() {
		obj.display();
	}
	void review(int ISSN) {
		if (!obj.ReviewBook(ISSN)) {
			cout << "\nBOOK DOESNOT EXISTS\n ";
		}
		else {
			cout << "\nBOOKS IS FOUND\n";
		}
	}
	void update(int ISSN) {
		if (!obj.upDateRecord(ISSN)) {
			cout << "\nBOOK DOESNOT EXISTS\n ";
		}
		else {
			cout << "\nBOOKS IS FOUND\n";
		}

	}
	void deleteh(int ISSN) {
		obj.deleteKey(ISSN);
	}

	void createbbok() {
		int issn, iss, ref, n;
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

			cout << "Enter title:";
			string title;
			cin.ignore();
			getline(cin, title);
			cout << endl;
			int size;
			cout << "Enter number of authors";
			cin >> size;
			string authors[10];
			for (int i = 0; i < size; i++)
			{
				cout << "Author " << i + 1 << ": ";
				cin >> authors[i];
			}
			authors[size++] = "stop";

			create(issn, ref, iss, authors, 3, title);
		}
	}
};


int main()
{
	implement  imp;
	bool run = true;

	string name[] = { "ayesha","eman","Saad" };
	string name1[] = { "Tooba","Auroob","Hadia" };
	string name2[] = { "ayeza","emanat","Suleiman" };
	string name3[] = { "Zainab","Hareem","Tayyyab" };

	imp.create(7, 0, 9, name, 3, "Narnia");
	imp.create(77, 9, 8, name1, 3, "c++");
	imp.create(3, 8, 7, name2, 3, "The tale of two cities");
	imp.create(4, 7, 6, name3, 3, "Prisoner of Azkaban");
	imp.create(5, 7, 6, name2, 3, "Ok");
	imp.create(6, 7, 6, name1, 3, "He who must not be named");
	imp.create(88, 7, 6, name, 3, "e");
	imp.display();

	while (run == true)
	{
		cout << "----------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\n\n\t\t     1.Insert \n\t\t     2.Review \n\t\t     3.Update \n\t\t     4.Delete \n";
		int n;
		cout << "Enter:";
		cin >> n;
		cout << endl;
		if (n == 1) {
			imp.createbbok();                                                                     //We can insert value but i hardcoded the book for easier use	
		}
		else if (n == 2) {
			int issn;
			cout << "Enter the book number you want to review: ";
			cin >> issn;
			cout << endl;
			imp.review(issn);
		}
		else if (n == 3) {
			int issn;
			cout << "Enter the book number you want to Update: ";
			cin >> issn;
			cout << endl;
			imp.update(issn);
		}
		else if (n == 4) {
			int issn;
			cout << "Enter the book number you want to Delete: ";
			cin >> issn;
			cout << endl;
			imp.deleteh(issn);
			cout << "\n HASHTABLE AFTER DELETION::\n ";
			imp.display();
		}

	}

	system("pause");
	return 0;
}
