#ifndef ADMIN_H
#define ADMIN_H
#include "Moderator.hpp"
#include "SocialNetwork.hpp"
#include "UserSystem.hpp"

class Administrator : virtual public Moderator {
public:
	Administrator(SocialNetwork*& sn, UserSystem*& us, const char* name = "admin", unsigned a = 18, bool ib = false);
	void addUser(User* u);
	void removeUser(const char* name);
};

#endif


