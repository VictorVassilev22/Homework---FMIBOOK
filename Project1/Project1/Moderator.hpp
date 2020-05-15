#ifndef MODERATOR_H
#define MODERATOR_H
#include"User.hpp"
#include<typeinfo>
class Moderator : virtual public User {
public:
	Moderator(char const* n = "anonymous", unsigned a = 0, bool ib = false);
	void deletePublication(unsigned serial) const;
	virtual void blockUser(User&) const;
	virtual void unblockUser(User&) const ;
};

#endif