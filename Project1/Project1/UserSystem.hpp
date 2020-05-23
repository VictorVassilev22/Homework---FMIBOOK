#ifndef USERSYST_H
#define USERSYST_H
//#include "User.hpp"
#include "Moderator.hpp"

const size_t ADMIN_NAME_SIZE = 10;
const size_t ADMIN_AGE = 20;

static size_t size_initializer_u = INIT_SIZE;
static size_t capacity_initializer_u = INIT_CAP;
//const double THRESHOLD_MAX = 8.0 / 10.0;
//const double THRESHOLD_MIN = 4.0 / 10.0;



class UserSystem {
	friend class Administrator;

	User** users;

	size_t size;
	size_t capacity;

	bool hasAdmin;

	void clearUsers();
	void deleteUsers();
	void resizeUsers(bool);

	void leftShift(size_t i);
	bool checkThreshold(bool c) const;
	void addUser(User*);
	void removeUser(char const*);
	void initUsers(User**, size_t);
	void copyUsers(User**, User**);
	void removeUserPosts(int index);
public:
	//void reallocUsers();
	UserSystem();
	UserSystem(UserSystem const& other);
	UserSystem& operator=(UserSystem const& other);
	~UserSystem();
	size_t getSize() const { return capacity; }
	size_t getCapacity() const { return capacity; }
	int searchUser(char const*) const;
	User* getUser(size_t i) const { return users[i]; }
};

#endif
