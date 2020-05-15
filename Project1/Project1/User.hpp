#ifndef USER_HPP
#define USER_HPP
#include"Publication.hpp"
#include<iostream>

class User{
	friend class Moderator;
	char* name;
	unsigned age;
	bool isBlocked;
	void setName(char const*);
	void copy(User const&);
public:
	User(char const* n = "anonymous", unsigned a = 0, bool ib = false);
	virtual ~User();
	User(User const& other);
	User& operator=(User const& other);
	bool getIsBlocked() { return isBlocked; }
	char* getName() const;
	unsigned getAge() const { return age; }
	void addPublication(Publication const&) const;
	virtual void deletePublication(unsigned serial) const;
};

#endif