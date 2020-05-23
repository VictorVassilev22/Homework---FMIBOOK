#ifndef IMG_PUB
#define IMG_PUB
#include "Publication.hpp"

class ImagePublication : virtual public Publication {
public:
	ImagePublication(const char* pName = "UNKNOWN", const char* content = "UNKNOWN");
	ImagePublication(const char*, const char* , unsigned);
	void showPublication(bool/*, std::ofstream&*/) const;
};

#endif