#include "SocialNetwork.hpp"

void SocialNetwork::clearPublications()
{
	if (publics) {
		for (size_t i = 0; i < capacity; i++)
		{
			if (publics[i]) {
				delete publics[i];
			}
		}
		delete[] publics;
		publics = nullptr;
	}
}

void SocialNetwork::leftShift(size_t index)
{
	for (size_t i = index; i < size - 1; i++)
	{
		publics[i] = publics[i + 1];
	}
	publics[size - 1] = new Publication;
}

void memoryError() {
	std::cout << "Could not locate memory for social network!" << std::endl;
}

void SocialNetwork::resizePublications(bool c)
{
	size_t new_capacity = capacity;
	if (c)
		new_capacity *= 2;
	else
		new_capacity /= 2;

	Publication** new_data = new(std::nothrow) Publication * [new_capacity];
	initPublications(new_data, new_capacity);
	copyPublications(new_data, publics);
	clearPublications();
	publics = new_data;
	capacity = new_capacity;
}

bool SocialNetwork::checkThreshold(bool c) const
{
	if (c) {
		if (size >= (size_t)(capacity * THRESHOLD_MAX)) {
			return true;
		}
		return false;
	}
	else {
		if (size <= (size_t)(capacity * THRESHOLD_MIN) && capacity > INIT_CAP) {
			return true;
		}
		return false;
	}
}

SocialNetwork::SocialNetwork() : size(size_initializer_s), capacity(capacity_initializer_s)
{
	std::ofstream myfile(NETWORK_PAGE_NAME, std::ios::trunc);
	myfile << "<p>Nothing to show currently!</p>";

	publics = new(std::nothrow) Publication * [capacity];
	if (!publics) {
		memoryError();
		clearPublications();
	}
	else {
		initPublications(publics, capacity);
	}
}

SocialNetwork::SocialNetwork(SocialNetwork const& other) : size(other.size),
	capacity(other.capacity)
{
	publics = other.publics;
	/*publics = new(std::nothrow) Publication * [capacity];
	initPublications(publics);
	copyPublications(publics, other.publics);*/
}

SocialNetwork& SocialNetwork::operator=(SocialNetwork const& other)
{
	if (this != &other) {
		size = other.size;
		capacity = other.capacity;
		publics = other.publics;
		/*publics = new(std::nothrow) Publication * [capacity];
		initPublications(publics);
		copyPublications(publics, other.publics);*/
	}
	return *this;
}


SocialNetwork::~SocialNetwork()
{
	clearPublications();
}

void SocialNetwork::addPublication(char const* poster_name, char const* content, const char type[])
{
	if (checkThreshold(true))
		resizePublications(true);

	if(strcmp(type, TXT_TYPE)==0)
		publics[size] = new TextPublication(content, poster_name);
	else if (strcmp(type, IMG_TYPE) == 0)
		publics[size] = new ImagePublication(content, poster_name);
	else if (strcmp(type, URL_TYPE) == 0)
		publics[size] = new LinkPublication(content, poster_name);
	else {
		std::cout << "Invalid post type, try again!" << std::endl;
		return;
	}

	size++;
	std::cout << poster_name <<" successfuly posted a publication!" << std::endl;
}

void SocialNetwork::deletePublication(int index)
{
	if (index >= 0) {
		std::cout << "Deleting publication " << publics[index]->getSerial() << "..." << std::endl;
		leftShift(index);
		size--;
	}
	else
		std::cout << "Publication does not exist..." << std::endl;

	if (checkThreshold(false))
		resizePublications(false);
}

void SocialNetwork::deleteAllUserPublications(const char name[])
{
	Publication* p;
	size_t i = 0;
	while(i<size)
	{
		p = publics[i];
		if (strcmp(p->getPosterName(), name) == 0)
			deletePublication(i);

		p = publics[i];
		if (strcmp(p->getPosterName(), name) != 0) {
			i++;
		}
	}
}

void SocialNetwork::initPublications(Publication** data, size_t cap)
{
	for (size_t i = 0; i < cap; i++)
	{
		data[i] = new Publication();
	}
}

void SocialNetwork::copyPublications(Publication** dest, Publication** origin)
{
	//TODO: OVERLOAD OTHER TWO AND MAKE SAME STRUCTURE FOR USERS RESIZING! TEST!
	Publication* p;
	for (size_t i = 0; i < size; i++)
	{
		p = origin[i];
		if(strcmp(typeid(*p).name(), typeid(TextPublication).name()) == 0)
			dest[i] = new TextPublication(p->getContent(), p->getPosterName(), p->getSerial());
		else if(strcmp(typeid(*p).name(), typeid(LinkPublication).name()) == 0)
			dest[i] = new LinkPublication(p->getContent(), p->getPosterName(), p->getSerial());
		else {
			dest[i] = new ImagePublication(p->getContent(), p->getPosterName(), p->getSerial());
		}
	}
}


Publication& SocialNetwork::getPublication(unsigned serial) const
{
	int index = searchPublication(serial);
	if (index < 0) {
		std::cout << "This publication does not exist, returning default publication.." << std::endl;
		Publication* p = new Publication();
		return *p;
	}
	return *publics[index];
}

void SocialNetwork::viewAllUserPublications(char const name[]) const
{
	std::ofstream myfile;
	myfile.open(NETWORK_PAGE_NAME, std::ios::out | std::ios::trunc);
	myfile << "<p>"<< name << "\'s publications: " << " </p> ";
	myfile.close();
	Publication* p;
	for (size_t i = 0; i < size; i++)
	{
		p = publics[i];
		if (strcmp(p->getPosterName(), name) == 0) {
			p->showPublication(false, myfile);
		}
	}
}

int SocialNetwork::searchPublication(unsigned serial) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (publics[i]->getSerial() == serial)
			return i;
	}
	return -1;
}