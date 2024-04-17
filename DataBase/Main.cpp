#include <iostream>
#include "Gun.h"

using namespace std;

int main() {
	setlocale(LC_ALL,"Ru");
	bool w = true;
	int n;
	List lst;
	while (w) {
		cout << "1-create 2-read 3-edit 4-delete 5-search 6-add 7-exit" << endl;
		cout << "Key=";
		int k;
		cin >> k;
		switch (k) {
		case 1: {
			base::clear(&lst);
			cout << "Введите число элементов:" << endl;
			cout << "n=";
			cin >> n;
			if (n <= 0) {
				cout << "Invalid n";
				break;
			}
			base::create(&lst, n);
		}
			break;
		case 2: {
			base::clear(&lst);
			base::read(&lst, &n);
			lst.print();
		}
			break;
		case 3: {
			if (!lst.at(0))
				base::read(&lst, &n);
			base::edit(&lst, &n);
		}
			break;
		case 4: {
			if (!lst.at(0))
				base::read(&lst, &n);
			base::del(&lst, &n);
		}
			break;
		case 5: {
			if (!lst.at(0))
				base::read(&lst, &n);
			base::search(&lst, &n);
		}
			  break;
		case 6: {
			if (!lst.at(0))
				base::read(&lst, &n);
			base::add(&lst, &n);
		}
			  break;
		case 7:
			w = false;
			break;
		}
	}
}