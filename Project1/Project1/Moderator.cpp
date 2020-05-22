#include "Moderator.hpp"

Moderator::Moderator(SocialNetwork*& sn, UserSystem*& us, char const* n, unsigned a, bool ib) : User(sn, n,a,ib), uSystem(us)
{
}

Moderator& Moderator::operator=(Moderator const& other)
{
	if (this != &other) {
		User::operator=(other);
		uSystem = other.uSystem;
	}
	return *this;
}

void Moderator::deletePublication(unsigned serial)
{
	int index = snetwork->searchPublication(serial);
	if (index >= 0)
		snetwork->deletePublication(index);
	else
		std::cout << "Publication not found!" << std::endl;
}

void Moderator::blockUser(char const* name) const
{
	int index = uSystem->searchUser(name);

	if (index < 0) {
		std::cout << "Invalid user, cannot block!" << std::endl;
		return;
	}

	User* u = uSystem->getUser(index);

	if (!u->getIsBlocked()) {
		std::cout << getName() << " blocks " << u->getName() << std::endl;
		u->isBlocked = true;
	}
}

void Moderator::unblockUser(char const* name) const
{
	int index = uSystem->searchUser(name);


	if (index < 0) {
		std::cout << "Invalid user, cannot unblock!" << std::endl;
		return;
	}

	User* u = uSystem->getUser(index);
	if (u->getIsBlocked()) {
		std::cout << getName() << " unblocks " << u->getName() << std::endl;
		u->isBlocked = false;
	}
}
