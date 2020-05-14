#ifndef USER_HPP
#define USER_HPP
#include"Publication.hpp"
#include<iostream>


class User{
	char* name;
	unsigned age;
protected:
	void setName(char const*);
	virtual void copy(User const&);
public:
	User(char const*, unsigned);
	virtual ~User();
	User(User const& other);
	User& operator=(User const& other);
	char* getName() const;
	unsigned getAge() const { return age; }
	virtual void addPublication(Publication const&) const;
	virtual void deletePublication(unsigned serial) const;
	virtual void changeName(char const*);
};

#endif