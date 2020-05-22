#ifndef USER_HPP
#define USER_HPP
#include<iostream>
#include "Publication.hpp"
#include "SocialNetwork.hpp"


class User{
	friend class Moderator;

	char* name;
	unsigned age;
	bool isBlocked;
	void setName(char const*);
	void copy(User const&);

protected:
	//make this a pointer, change destructors and constructors, hide the pointer well
	SocialNetwork* snetwork;
public:
	User(SocialNetwork*& sn, char const* n = "anonymous", unsigned a = 18, bool ib = false);
	User();
	virtual ~User();
	User(User const& other);
	User& operator=(User const& other);
	virtual void deletePublication(unsigned serial);
	void postPublication(const char* content, const char type[]);
	bool getIsBlocked() { return isBlocked; }
	char* getName() const;
	unsigned getAge() const { return age; }
	SocialNetwork*& getSocialNetwork()  { return snetwork; }
	void viewPublication(unsigned) const;
};

#endif