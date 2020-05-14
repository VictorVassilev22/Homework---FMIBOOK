#include "Publication.hpp"

Publication::Publication(char const* c, unsigned s) : serial(s) {
	setContent(c);
}

void Publication::setContent(char const* str) {
	delete[] content;
	content = new(std::nothrow) char[strlen(str) + 1];
	strcpy(content, str);
}

Publication::~Publication() {
	delete[] content;
}

void Publication::copy(Publication const& other) {
	serial = other.serial;
	setContent(other.content);
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
	if (content) {
		char* cntcpy = new(std::nothrow) char[strlen(content) + 1];
		if (!cntcpy) {
			std::cout << "Memory location failed!" << std::endl;
			return nullptr;
		}
		strcpy(cntcpy, content);
		return cntcpy;
	}

	return nullptr;
}
