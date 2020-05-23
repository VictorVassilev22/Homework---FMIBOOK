#include "Publication.hpp"

Publication::Publication()
{
	serial = 0;
	setPosterName("UNKNOWN");
	setContent("UNKNOWN");
}

Publication::Publication(char const* c, char const* un){
	setPosterName(un);
	serial = serialHolder++;
	setContent(c);
}

Publication::Publication(char const* c, char const* un, unsigned s)
{
	setPosterName(un);
	serial = s;
	setContent(c);
}

void Publication::showPublication(bool isOnly/*, std::ofstream& myfile*/) const
{
	std::ofstream myfile;
	myfile.open(my_page, std::ios::out | std::ios::trunc);
	if (myfile.is_open()) {
		if (strcmp("UNKNOWN", poster_name) == 0)
			myfile << "<p>" << "Nothing to show here!" << " </p> ";
		else
			myfile << "<p>" << poster_name << " posted ";
		myfile.close();
	}

}

void Publication::setContent(char const* str) {
	delete[] content;
	content = new(std::nothrow) char[strlen(str) + 1];
	strcpy(content, str);
}

void Publication::setPosterName(char const* str)
{
	delete[] poster_name;
	poster_name = new(std::nothrow) char[strlen(str) + 1];
	strcpy(poster_name, str);

}

Publication::~Publication() {
	delete[] content;
	delete[] poster_name;
}

void Publication::copy(Publication const& other) {
	serial = other.serial;
	setContent(other.content);
	setPosterName(other.poster_name);
}

char* Publication::copyStr(char const* str) const
{
	if (str) {
		char* strcopy = new(std::nothrow) char[strlen(str) + 1];
		if (!strcopy) {
			std::cout << "Memory location failed!" << std::endl;
			return nullptr;
		}
		strcpy(strcopy, str);
		return strcopy;
	}

	return nullptr;
}

Publication::Publication(Publication const& other) {
	copy(other);
}

Publication& Publication::operator=(Publication const& other)
{
	if (this != &other) {
		copy(other);
	}
	return *this;
}

char* Publication::getContent() const
{
	return copyStr(content);
}

char* Publication::getPosterName() const
{
	return copyStr(poster_name);
}
