#include "ImagePublication.hpp"

ImagePublication::ImagePublication(const char* content, const char* pName) : Publication(content, pName)
{
}

ImagePublication::ImagePublication(const char* c , const char* un, unsigned s) : Publication(c, un, s)
{
}

void ImagePublication::showPublication(bool isOnly/*, std::ofstream& myfile*/) const
{

	if (isOnly)
		Publication::showPublication(isOnly/*, myfile*/);

	std::ofstream myfile;
	myfile.open(my_page, std::ios::out | std::ios::app);
	if(myfile.is_open()){
		if (!isOnly)	
			myfile << "<p>";
		myfile << " image publication:</p> ";
		myfile << "<img src=\"" << getContent() << "\">";
		myfile.close();
	}
}
