#pragma once
#include <string>
class Gun {
private:
	int id;
	std::string name;
	int range;
	std::string caliber;
	std::string country;
public:
	friend std::istream& operator >>(std::istream& in, Gun& g);
	friend std::ostream& operator <<(std::ostream& out, Gun& g);
	void setId(int i);
	int getId();
	std::string getName();
	void setName(std::string str);
	void setRange(int rn);
	void setCal(std::string cal);
	void setCou(std::string cou);
};

struct ListItem {
	Gun data;
	ListItem* next = nullptr;
};

class List {
	ListItem* _first = nullptr;
public:
	~List();
	int count();
	void print();
	ListItem* at(int index);
	void pushBack(Gun data);
	void PushFront(Gun data);
	void popFront();
	void popBack();
	void insert(int index, Gun data);
	void remove(int index);
	List& operator <<(Gun data);
};


namespace base {
	void create(List* lst, int g);
	void read(List* lst, int* g);
	void del(List* lst, int* g);
	void add(List* lst, int* g);
	void edit(List* lst, int* g);
	void search(List* lst, int* g);
	void clear(List* lst);
}