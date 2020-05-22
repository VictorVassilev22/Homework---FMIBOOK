#include "ImagePublication.hpp"

ImagePublication::ImagePublication(const char* content, const char* pName) : Publication(content, pName)
{
}

ImagePublication::ImagePublication(const char* c , const char* un, unsigned s) : Publication(c, un, s)
{
}

void ImagePublication::showPublication(bool isOnly, std::ofstream& myfile) const
{

	if (isOnly)
		Publication::showPublication(isOnly, myfile);

	myfile.open(NETWORK_PAGE_NAME, std::ios::out | std::ios::app);

	if(!isOnly)	myfile << "<p>";


	myfile << " image publication:</p> ";
	myfile << "<img src=\"" << getContent() << "\" alt=\""<<getPosterName()<<" posted an image\">";
	myfile.close();
}
