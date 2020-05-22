#include "Administrator.hpp"

Administrator::Administrator(SocialNetwork*& sn, UserSystem*& us, const char* n, unsigned a, bool ib) : User(sn, n, a, ib),
	Moderator(sn, us, n, a, ib)
{
	uSystem->hasAdmin = true;
}


void Administrator::addUser(User* u)
{
	uSystem->addUser(u);
}

void Administrator::removeUser(const char* name)
{
	uSystem->removeUser(name);
}



