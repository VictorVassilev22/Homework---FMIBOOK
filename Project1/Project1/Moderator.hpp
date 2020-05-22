#ifndef MODERATOR_H
#define MODERATOR_H
#include"User.hpp"
#include"UserSystem.hpp"
#include<typeinfo>

class Moderator : virtual public User {
protected:
	UserSystem* uSystem;
public:
	Moderator(SocialNetwork*& sn, UserSystem*& us, char const* n = "anonymous", unsigned a = 0, bool ib = false);
	Moderator& operator=(Moderator const&);
	void deletePublication(unsigned serial);
	void blockUser(char const*) const;
	void unblockUser(char const*) const ;
	UserSystem*& getUserSystem() { return uSystem; }

};

#endif