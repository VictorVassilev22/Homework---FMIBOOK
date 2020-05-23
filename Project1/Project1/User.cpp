#include "User.hpp"
#include <cstring>

User::User(SocialNetwork*& sn, char const* n, unsigned a, bool ib) : name(nullptr) ,age(a), isBlocked(ib) {
	snetwork = sn;
	setName(n);
}

User::User() : snetwork(new SocialNetwork()), name(nullptr), age(18), isBlocked(false)
{
	setName("anonymous");
}

void User::setName(char const* str) {
	delete[] name;
	name = new(std::nothrow) char[strlen(str) + 1];
	strcpy(name, str);
}

User::~User() {
	if (name) {
		delete[] name;
		name = nullptr;
	}
}

User::User(User const& other) {
	copy(other);
}

void User::copy(User const& other) {
	age = other.age;
	snetwork = other.snetwork;
	setName(other.name);
}

void User::deletePublication(unsigned serial)
{
	int index = snetwork->searchPublication(serial);
	if (index < 0) {
		std::cout << "Sorry, you have such publication!" << std::endl;
		return;
	}
	Publication& p = snetwork->getPublication(index);
	if (strcmp(p.getPosterName(), name) != 0) {
		std::cout << "Sorry, you have such publication!" << std::endl;
		return;
	}

	snetwork->deletePublication(index);
}

void User::postPublication(const char* content, const char type[])
{
	if (isBlocked) {
		std::cout << "This user is currently blocked and cannot make any posts!" << std::endl;
		return;
	}

	snetwork->addPublication(name, content, type);
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

void User::viewPublication(unsigned serial) const
{
	//std::ofstream myfile;
	snetwork->getPublication(serial).showPublication(true/*, myfile*/);
}

