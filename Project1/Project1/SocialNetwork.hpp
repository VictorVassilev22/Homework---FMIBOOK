#ifndef SNETWORK_H
#define SNETWORK_H
#include "TextPublication.hpp"
#include "ImagePublication.hpp"
#include "LinkPublication.hpp"

const size_t INIT_SIZE = 0;
const size_t INIT_CAP = 8;
const size_t PUB_TYPE_SIZE = 4;

static size_t size_initializer_s = INIT_SIZE;
static size_t capacity_initializer_s = INIT_CAP;

const double THRESHOLD_MAX = 8.0 / 10.0;
const double THRESHOLD_MIN = 4.0 / 10.0;

const char IMG_TYPE[PUB_TYPE_SIZE] = "img";
const char TXT_TYPE[PUB_TYPE_SIZE] = "txt";
const char URL_TYPE[PUB_TYPE_SIZE] = "url";


class SocialNetwork {
	friend class User;
	friend class Moderator;
	friend class Administrator;
	friend class UserSystem;

	Publication** publics;

	size_t size;
	size_t capacity;

	void clearPublications();

	void resizePublications(bool);

	void leftShift(size_t i);
	bool checkThreshold(bool c) const;

	void addPublication(char const*, char const*, const char[]);
	void deletePublication(int);
	void deleteAllUserPublications(const char[]);
	void initPublications(Publication**, size_t);
	void copyPublications(Publication**, Publication**);
public:
	SocialNetwork();
	SocialNetwork(SocialNetwork const& other);
	SocialNetwork& operator=(SocialNetwork const&);
	~SocialNetwork();
	size_t getSize() const { return size; }
	size_t geCapacity() const { return capacity; }
	Publication& getPublication(unsigned) const;
	void viewAllUserPublications(char const []) const;
	int searchPublication(unsigned) const;
};

#endif