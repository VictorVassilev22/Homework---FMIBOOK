#ifndef PUBLICATION_HPP
#define PUBLICATION_HPP
#include<cstring>
#include<iostream>
#include<fstream>
 
static unsigned serialHolder = 1;
const char my_page[10] = "page.html";

class Publication {

	char* poster_name;
	char* content;
	unsigned serial;

	void setContent(char const*);
	void setPosterName(char const*);
	void copy(Publication const& other);
	char* copyStr(char const* str) const;
public:
	Publication();
	Publication(char const*, char const*);
	Publication(char const*, char const*, unsigned);
	virtual ~Publication();
	unsigned getSerial() const { return serial; }
	char* getContent() const;
	char* getPosterName() const;
	Publication(Publication const& other);
	Publication& operator=(Publication const& other);
	virtual void showPublication(bool/*, std::ofstream&*/) const;

};

#endif