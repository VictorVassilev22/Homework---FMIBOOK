#include "Moderator.hpp"
#include"Administrator.hpp"

Moderator::Moderator(char const* n, unsigned a, bool ib) : User(n,a,ib)
{
}

void Moderator::deletePublication(unsigned serial) const
{
}

void Moderator::blockUser(User& u) const
{
	if (!u.getIsBlocked() && typeid(u)!=typeid(Administrator)) {
		std::cout << getName() << " blocks " << u.getName() << std::endl;
		u.isBlocked = true;
	}
}

void Moderator::unblockUser(User& u) const
{
	if (u.getIsBlocked()) {
		std::cout << getName() << " unblocks " << u.getName() << std::endl;
		u.isBlocked = false;
	}
}
