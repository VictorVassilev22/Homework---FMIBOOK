#include "Administrator.hpp"

Administrator::Administrator(const char* n, unsigned a) : User(n, a)
{
}

void Administrator::addUser(User& u, User** arr, size_t pos)
{
	//TODO: if not alredy there but on the next level
	if (typeid(u) != typeid(Administrator))
		arr[pos] = &u;
	else
		std::cout << "Error! User is not added!" << std::endl;
}

