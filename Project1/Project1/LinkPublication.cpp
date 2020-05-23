#include "LinkPublication.hpp"

LinkPublication::LinkPublication(const char* content, const char* pName) : Publication(content, pName)
{
}

LinkPublication::LinkPublication(const char* c, const char* un, unsigned s) :Publication(c,un,s)
{
}

void LinkPublication::showPublication(bool isOnly/*, std::ofstream& myfile*/) const
{
	if (isOnly)
		Publication::showPublication(isOnly/*, myfile*/);

	std::ofstream myfile;
	myfile.open(my_page, std::ios::out | std::ios::app);
	if (myfile.is_open()) {

		if (!isOnly)
			myfile << "<p>";


		myfile << " link publication:</p> ";
		myfile << "<a href=\"" << getContent() << "\">  View " << getPosterName() << "\'s shared link </a>";
		myfile.close();
	}
}
