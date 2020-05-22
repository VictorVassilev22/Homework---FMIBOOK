#include "UserSystem.hpp"

void UserSystem::clearUsers()
{
	if (users) {
		for (size_t i = 0; i < capacity; i++)
		{
			if (users[i]) {
				delete users[i];
			}
		}
		deleteUsers();
	}
}

void UserSystem::deleteUsers()
{
	delete[] users;
	users = nullptr;
}

void UserSystem::resizeUsers(bool c)
{
	size_t new_capacity = capacity;
	if (c)
		new_capacity *= 2;
	else
		new_capacity /= 2;

	User** new_data = new(std::nothrow) User * [new_capacity];
	initUsers(new_data, new_capacity);
	copyUsers(new_data, users);
	clearUsers();
	users = new_data;
	capacity = new_capacity;
}

void UserSystem::leftShift(size_t index)
{
	for (size_t i = index; i < size - 1; i++)
	{
		users[i] = users[i + 1];
	}
	users[size - 1] = new User;
}

bool UserSystem::checkThreshold(bool c) const
{
	if (c) {
		if (size >= (size_t)(capacity * THRESHOLD_MAX)) {
			return true;
		}
		return false;
	}
	else {
		if (size <= (size_t)(capacity * THRESHOLD_MIN) && capacity > INIT_CAP) {
			return true;
		}
		return false;
	}
}

void UserSystem::addUser(User* user)
{
	if (checkThreshold(true))
		resizeUsers(true);
	char* name = user->getName();
	if (searchUser(name) < 0) {
		users[size] = user;
		size++;
		std::cout << name<< " successfuly added!" << std::endl;
	}
	else
		std::cout << "Not added! User with this name alredy exists" << std::endl;
}

void UserSystem::removeUser(char const* name)
{
	int index = searchUser(name);
	if (index >= 0) {
		removeUserPosts(index);
		leftShift(index);
		size--;
	}
	else 
		std::cout << "User not found!" << std::endl;

	if (checkThreshold(false))
		resizeUsers(false);
}

void UserSystem::initUsers(User** data, size_t cap)
{
	for (size_t i = 0; i < cap; i++)
	{
		data[i] = new User();
	}
}

void UserSystem::copyUsers(User** dest, User** origin)
{
	User* u;
	for (size_t i = 0; i < size; i++)
	{
		u = origin[i];
		if (strcmp(typeid(*u).name(), typeid(Moderator).name()) == 0)
			dest[i] = new Moderator(*dynamic_cast<Moderator*>(u));
		else
		*dest[i] = *origin[i];
	}
}

void UserSystem::removeUserPosts(int index)
{
	User* u = getUser(index);
	SocialNetwork* sn = u->getSocialNetwork();
	sn->deleteAllUserPublications(u->getName());
	
}

//void UserSystem::reallocUsers()
//{
//	User** new_data = new(std::nothrow) User * [capacity];
//	initUsers(new_data, cap);
//	copyUsers(new_data, users);
//	clearUsers();
//	users = new_data;
//}

void memory_error() {
	std::cout << "Could not locate memory for user system!" << std::endl;
}


UserSystem::UserSystem() : size(size_initializer_u), capacity(capacity_initializer_u), hasAdmin(false)
{
	users = new(std::nothrow) User * [capacity];
	if (!users) {
		memory_error();
		clearUsers();
	}
	else {
		initUsers(users, capacity);
	}
}

UserSystem::UserSystem(UserSystem const& other) : capacity(other.capacity), size(other.size), hasAdmin(other.hasAdmin)
{
	users = other.users;
}

UserSystem& UserSystem::operator=(UserSystem const& other)
{
	if (this != &other) {
		size = other.size;
		capacity = other.capacity;
		hasAdmin = other.hasAdmin;
		users = other.users;
	}
	return *this;
}

UserSystem::~UserSystem()
{
	clearUsers();
}

int UserSystem::searchUser(char const* name) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(users[i]->getName(), name) == 0)
			return i;
	}
	return -1;
}
