#include "TextPublication.hpp"

TextPublication::TextPublication(const char* content, const char* pName) : Publication(content, pName)
{
}

TextPublication::TextPublication(const char* c , const char* un, unsigned s):Publication(c,un,s)
{
}

void TextPublication::showPublication(bool isOnly/*, std::ofstream& myfile*/) const
{
	if (isOnly)
		Publication::showPublication(isOnly/*, myfile*/);

	std::ofstream myfile;
	myfile.open(my_page, std::ios::out | std::ios::app);
	if (myfile.is_open()) {
		if (!isOnly)
			myfile << "<p>";

		myfile << " text publication:</p> ";
		myfile << "<p>" << getContent() << "</p>";
		myfile.close();
	}
}
