#include "TextPublication.hpp"

TextPublication::TextPublication(const char* content, const char* pName) : Publication(content, pName)
{
}

TextPublication::TextPublication(const char* c , const char* un, unsigned s):Publication(c,un,s)
{
}

void TextPublication::showPublication(bool isOnly, std::ofstream& myfile) const
{
	if (isOnly)
		Publication::showPublication(isOnly, myfile);

	myfile.open(NETWORK_PAGE_NAME, std::ios::out | std::ios::app);

	std::cout << myfile.good() << std::endl;

	if (!myfile.good())
	{

		std::cout<<"An error occured!" << std::endl;
		return;
	}
		if (!isOnly)
			myfile << "<p>";

		myfile << " text publication:</p> ";
		myfile << "<p>" << getContent() << "</p>";
		myfile.close();
}
