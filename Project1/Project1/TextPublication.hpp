#ifndef TEXTPUB_H
#define TEXTPUB_H
#include "Publication.hpp"

class TextPublication : virtual public Publication {
public:
	TextPublication(const char* pName = "UNKNOWN", const char* content = "UNKNOWN");
	TextPublication(const char*, const char*,unsigned);
	void showPublication(bool/*, std::ofstream&*/) const;
};

#endif