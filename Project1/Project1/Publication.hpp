#ifndef PUBLICATION_HPP
#define PUBLICATION_HPP
#include<cstring>
#include<iostream>

class Publication {
	char* content;
	unsigned serial;
protected:
	void setContent(char const*);
	virtual void copy(Publication const& other);
public:
	Publication(char const*, unsigned);
	virtual ~Publication();
	unsigned getSerial() const { return serial; }
	char* getContent() const;
	Publication(Publication const& other);
	Publication& operator=(Publication const& other);

};

#endif