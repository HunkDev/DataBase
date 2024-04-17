#include <iostream>
#include <string>
#include "Gun.h"
#include <fstream>

using namespace std;

istream& operator >>(istream& in, Gun& g) {
	//cout << "name=";
	in >> g.name;
	//cout << "range=";
	in >> g.range;
	//cout << "caliber=";
	in >> g.caliber;
	//cout << "country=";
	in >> g.country;
	return in;
}
ostream& operator <<(ostream& out, Gun& g) {
	out << g.id << " " << g.name << " " << g.range << " " << g.caliber << " " << g.country << endl;
	return out;
}

List::~List() {
	if (!_first)
		return;
	ListItem* current = _first;
	do {
		ListItem* temp = current;
		current = temp->next;
		delete temp;
	} while (current);
}

int List::count() {
	int count = 0;
	auto current = _first;
	while (current) {
		count++;
		current = current->next;
	}
	return count;
}

ListItem* List::at(int index) {
	if (!_first || index < 0 || index >= count())
		return nullptr;
	auto item = _first;
	for (int i = 0; i < index; i++)
		item = item->next;
	return item;
}

void List::print() {
	auto current = _first;
	while (current) {
		cout << current->data << endl;
		current = current->next;
	}
}

void List::PushFront(Gun data) {
	auto item = new ListItem;
	item->data = data;
	item->next = _first;
	_first = item;
}

void List::pushBack(Gun data) {
	auto item = new ListItem;
	item->data = data;
	if (!_first) {
		_first = item;
		return;
	}
	auto last = at(count() - 1);
	if (!last) {
		delete item;
		return;
	}
	last->next = item;

}
void List::popFront() {
	if (!_first)
		return;
	auto item = _first;
	_first = item->next;
	delete item;
}


void List::popBack() {
	if (!_first)
		return;
	if (!_first->next) {
		delete _first;
		_first = nullptr;
		return;
	}
	auto prev = at(count() - 2);
	if (!prev)
		return;
	delete prev->next;
	prev->next = nullptr;
}


void List::remove(int index) {
	int n = count();
	if (!_first || index < 0 || index >= n)
		return;
	if (index == 0) {
		popFront();
		return;
	}
	if (index == n - 1) {
		popBack();
		return;
	}
	auto prev = at(index - 1);
	auto removed = prev->next;
	auto next = removed->next;
	prev->next = next;
	delete removed;
}

void List::insert(int index, Gun data) {
	int n = count();
	if (!_first || index < 0 || index >= n)
		return;
	if (index == 0) {
		PushFront(data);
		return;
	}
	if (index == n - 1) {
		pushBack(data);
		return;
	}
	auto item = at(index - 1);
	auto next = item->next;
	auto newItem = new ListItem;
	newItem->data = data;
	newItem->next = next;
	item->next = newItem;
}

List& List::operator<<(Gun data) {
	pushBack(data);
	return *this;
}

void Gun::setId(int i) {
	id = i;
}

int Gun::getId() {
	return id;
}

string Gun::getName() {
	return name;
}

void Gun::setName(string str) {
	name = str;
}

void Gun::setRange(int rn) {
	range = rn;
}

void Gun::setCal(string cal) {
	caliber = cal;
}

void Gun::setCou(string cou) {
	country = cou;
}

namespace base {

	void clear(List* lst) {
		int m = lst->count();
		for (int i = 0; i < m; i++)
			lst->popBack();
	}

	void wrt(List* lst, int* g) {
		ofstream out;
		out.open("Base.txt");
		if (!out.is_open()) {
			cout << "error" << std::endl;
			return;
		}
		out << *g << endl;
		for (int i = 0; i < *g; i++) {
			out << lst->at(i)->data << endl;
		}
		out.close();
	}

	void read(List* lst, int* g) {
		ifstream in;
		in.open("Base.txt");
		if (!in.is_open()) {
			cout << "error" << std::endl;
			return;
		}
		in >> *g;
		for (int i = 0; i < *g; i++) {
			Gun temp;
			int id;
			in >> id;
			temp.setId(id);
			in >> temp;
			lst->pushBack(temp);
		}
		in.close();
		return;
	}
	void create(List* lst, int g) {
		ofstream out;
		out.open("Base.txt");
		if (!out.is_open()) {
			cout << "error" << std::endl;
			return;
		}
		out << g << endl;
		for (int i = 0; i < g; i++) {
			Gun temp;
			cout << "Name=";
			string par;
			cin >> par;
			temp.setName(par);
			cout << "Range=";
			int range;
			cin >> range;
			temp.setRange(range);
			cout << "Caliber=";
			cin >> par;
			temp.setCal(par);
			cout << "Country=";
			cin >> par;
			temp.setCou(par);
			temp.setId(i);
			lst->pushBack(temp);
			out << temp << endl;
		}
		out.close();
		return;
	}

	void edit(List* lst, int* g) {
		int id;
		cout << "Id = ";
		cin >> id;
		for (int i = 0; i < *g; i++) {
			if (lst->at(i)->data.getId() == id) {
				Gun temp;
				temp.setId(id);
				cout << "Name=";
				string par;
				cin >> par;
				temp.setName(par);
				cout << "Range=";
				int range;
				cin >> range;
				temp.setRange(range);
				cout << "Caliber=";
				cin >> par;
				temp.setCal(par);
				cout << "Country=";
				cin >> par;
				temp.setCou(par);
				lst->at(i)->data = temp;
				break;
			}
		}
		wrt(lst, g);
	}

	void del(List* lst, int* g) {
		cout << "Id=";
		int id = 0;
		int k = 0;
		cin >> id;
		for (int i = 0; i < *g; i++) {
			if (lst->at(i)->data.getId() == id) {
				k = i;
				break;
			}
		}
		lst->remove(k);
		*g--;
		wrt(lst, g);
	}

	void search(List* lst, int* g) {
		int n;
		cout << "1-id, 2-name" << endl;
		cout << "n=";
		cin >> n;
		switch (n) {
		case 1: {
			cout << "id=";
			int id;
			cin >> id;
			for (int i = 0; i < *g; i++) {
				if (lst->at(i)->data.getId() == id) {
					cout << lst->at(i)->data << endl;
					break;
				}
			}
		}
			  break;
		case 2: {
			cout << "name=";
			string name;
			cin >> name;
			for (int i = 0; i < *g; i++) {
				if (lst->at(i)->data.getName() == name) {
					cout << lst->at(i)->data << endl;
					break;
				}
			}
		}
			  break;
		}
	}

	void add(List* lst, int* g) {
		Gun temp;
		if ((lst->at(0))!=nullptr)
			temp.setId(lst->at(lst->count() - 1)->data.getId() + 1);
		else
			temp.setId(0);
		cout << "Name=";
		string par;
		cin >> par;
		temp.setName(par);
		cout << "Range=";
		int range;
		cin >> range;
		temp.setRange(range);
		cout << "Caliber=";
		cin >> par;
		temp.setCal(par);
		cout << "Country=";
		cin >> par;
		temp.setCou(par);
		lst->pushBack(temp);
		(*g)++;
		wrt(lst, g);
	}
}