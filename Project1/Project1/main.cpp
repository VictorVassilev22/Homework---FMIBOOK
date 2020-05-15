#include <iostream>
#include "Administrator.hpp"
using namespace std;
const size_t SIZE = 100;

void testAdding() {
	User** arr = new(nothrow) User * [SIZE];
	Administrator a("Sentinel", 20);
	User p("Pesho", 18);
	Moderator m("mitko", 18);
	a.addUser(p, arr, 0);
	cout << typeid(*arr[0]).name() << endl;
	// not adding a.addUser(a, arr, 1);
	//error cout << typeid(*arr[1]).name() << endl;
	// error Administrator* c = dynamic_cast<Administrator *>(arr[1]);
	//c->addUser(p, arr, 2);
	cout << typeid(*arr[2]).name() << endl;
	//c->addUser(m, arr, 3);
	cout << typeid(*arr[0]).name() << endl;
	Moderator* m2 = dynamic_cast<Moderator*>(arr[3]);
	m2->blockUser(p);
}

void testBlocks() {
	Administrator a("Sentinel", 20);
	cout << a.getName() << "->" << a.getIsBlocked() << endl;

	User u("Pesho Slepia", 22);
	cout << u.getName() << "->" << u.getIsBlocked() << endl;

	Moderator m("Shefa", 33);
	cout << m.getName() << "->" << m.getIsBlocked() << endl;

	m.blockUser(u);
	cout << u.getName() << "->" << u.getIsBlocked() << endl;

	Moderator m2("Drugiq Shef", 33);
	m2.blockUser(m);
	cout << m.getName() << "->" << m.getIsBlocked() << endl;

	m.unblockUser(m);
	cout << m.getName() << "->" << m.getIsBlocked() << endl;

	a.blockUser(m);
	cout << m.getName() << "->" << m.getIsBlocked() << endl;

	m.blockUser(a);
	cout << a.getName() << "->" << a.getIsBlocked() << endl;
}

int main() {
	testAdding();
	testBlocks();
	return 0;
}