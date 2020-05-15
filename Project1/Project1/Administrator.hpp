#ifndef ADMIN_H
#define ADMIN_H
#include "Moderator.hpp"

class Administrator : virtual public Moderator {
public:
	Administrator(const char*, unsigned);
	void addUser(User& u, User** arr, size_t pos);
};

#endif