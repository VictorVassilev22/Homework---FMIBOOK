#ifndef LINKPUB_H
#define LINKPUB_H
#include "Publication.hpp"

class LinkPublication : virtual public Publication {
public:
	LinkPublication(const char* content = "UNKNOWN", const char* pName = "UNKNOWN");
	LinkPublication(const char* , const char* ,unsigned);
	void showPublication(bool/*, std::ofstream&*/) const;
};


#endif