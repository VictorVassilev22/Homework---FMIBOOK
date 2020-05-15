#include "User.hpp"
#include <cstring>

User::User(char const* n, unsigned a, bool ib) :name(nullptr) ,age(a), isBlocked(ib) {
	setName(n);
}

void User::setName(char const* str) {
	delete[] name;
	name = new(std::nothrow) char[strlen(str) + 1];
	strcpy(name, str);
}

User::~User() {
	delete[] name;
}

User::User(User const& other) {
	copy(other);
}

void User::copy(User const& other) {
	age = other.age;
	setName(other.name);
}

void User::addPublication(Publication const&) const
{
}

void User::deletePublication(unsigned serial) const
{
}

User& User::operator=(User const& other) {
	if (this != &other) {
		copy(other);
	}
	return *this;
}

char* User::getName() const
{	
	if (name) {
		char* namecpy = new(std::nothrow) char[strlen(name) + 1];
		if (!namecpy) {
			std::cout << "Memory location failed!" << std::endl;
			return nullptr;
		}
		strcpy(namecpy, name);
		return namecpy;
	}

	return nullptr;
}
