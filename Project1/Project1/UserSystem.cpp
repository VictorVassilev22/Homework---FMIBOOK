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


unsigned UserSystem::getUsersCount() const
{
	unsigned count = 0;
	User* u;
	for (size_t i = 0; i < size; i++)
	{
		u = users[i];
		if (strcmp(typeid(*u).name(), typeid(User).name()) == 0)
			count++;
	}
	return count;
}

unsigned UserSystem::getModeratorsCount() const
{
	unsigned count = 0;
	User* u;
	for (size_t i = 0; i < size; i++)
	{
		u = users[i];
		if (strcmp(typeid(*u).name(), typeid(Moderator).name()) == 0)
			count++;
	}
	return count;
}

char* UserSystem::getUserWithMostPosts(unsigned& count) const
{
	unsigned post_max = 0;
	unsigned curr_count;
	char* name = new(std::nothrow) char[MAX_USERNAME_SIZE];
	if (!name) {
		std::cout << "Error name memory!" << std::endl;
		return nullptr;
	}
	strcpy(name, "nobody");
	for (size_t i = 0; i < size; i++)
	{
		curr_count = users[i]->getPostsCount();
		if (curr_count >= post_max) {
			post_max = curr_count;
			strcpy(name, users[i]->getName());
		}
	}
	count = post_max;
	return name;
}

void UserSystem::getBlockedUsers() const
{
	std::cout << "Blocked users are: " << std::endl;
	unsigned count = 0;
	User* u;
	for (size_t i = 0; i < size; i++)
	{
		u = users[i];
		if (u->getIsBlocked()) {
			std::cout << u->getName() << std::endl;
			count++;
		}
	}
	std::cout << "Total " << count << " users are blocked." << std::endl;
}

char* UserSystem::getYoungest(unsigned& age) const
{
	User* u;
	char* name = new(std::nothrow) char[MAX_USERNAME_SIZE];
	if (!name) {
		std::cout << "Error name memory!" << std::endl;
			return nullptr;
	}
	strcpy(name, "nobody");

	if (size <= 0) {
		return name;
	}

	unsigned curr_age;
	unsigned min_age = UINT_MAX;
	for (size_t i = 0; i < size; i++)
	{
		u = users[i];
		curr_age = u->getAge();
		if (curr_age <= min_age) {
			min_age = curr_age;
			strcpy(name, u->getName());
		}
	}
	age = min_age;
	return name;
}

char* UserSystem::getOldest(unsigned& age) const
{
	User* u;
	char* name = new(std::nothrow) char[MAX_USERNAME_SIZE];
	if (!name) {
		std::cout << "Error name memory!" << std::endl;
		return nullptr;
	}
	strcpy(name, "nobody");

	if (size <= 0) {
		return name;
	}

	unsigned curr_age;
	unsigned max_age = 0;
	for (size_t i = 0; i < size; i++)
	{
		u = users[i];
		curr_age = u->getAge();
		if (curr_age >= max_age) {
			max_age = curr_age;
			strcpy(name, u->getName());
		}
	}
	age = max_age;
	return name;
}


void memory_error() {
	std::cout << "Could not locate memory for user system!" << std::endl;
}


UserSystem::UserSystem() : size(INIT_SIZE), capacity(INIT_CAP), hasAdmin(false)
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

void UserSystem::printInfo() const
{
	std::cout << "Total users: " << getUsersCount() << std::endl;
	std::cout << "Total moderators: " << getModeratorsCount() << std::endl;
	unsigned most_posts = 0;
	char* most_posts_username = getUserWithMostPosts(most_posts);
	std::cout << "User with most posts: " << most_posts_username <<" with "<<most_posts<<" posts!"<< std::endl;
	getBlockedUsers();
	unsigned youngest_age = 0;
	char* name_youngest = getYoungest(youngest_age);
	unsigned oldest_age = 0;
	char* name_oldest = getOldest(oldest_age);
	std::cout << "Youngest user is " << name_youngest << " and is " << youngest_age << " years old!" << std::endl;
	std::cout << "Oldest user is " << name_oldest << " and is " << oldest_age << " years old!" << std::endl;
	
}
