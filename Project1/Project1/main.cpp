#include <iostream>
#include "Administrator.hpp"
#include "UserSystem.hpp"
//#include "SocialNetwork.hpp"
using namespace std;
const size_t SIZE = 100;
const size_t MAX_COMMAND = 20;
const size_t MAX_LINE = 2000;
const size_t MAX_USERTYPE_NAME = 10;
const size_t MAX_POST = 1000;
const char STOP_CMD[MAX_COMMAND] = "quit";
const char INFO_CMD[MAX_COMMAND] = "info";
const char ADD_USER_CMD[MAX_COMMAND] = "add_user";
const char ADD_MODER_CMD[MAX_COMMAND] = "add_moderator";
const char REMOVE_USER_CMD[MAX_COMMAND] = "remove_user";
const char POST_CMD[MAX_COMMAND] = "post";
const char DEL_POST_CMD[MAX_COMMAND] = "delete_post";
const char VIEW_POST_CMD[MAX_COMMAND] = "view_post";
const char VIEW_ALL_POST_CMD[MAX_COMMAND] = "view_all_posts";
const char BLOCK_CMD[MAX_COMMAND] = "block";
const char UNBLOCK_CMD[MAX_COMMAND] = "unblock";
const char USER_TYPE[MAX_USERTYPE_NAME] = "user";
const char MODER_TYPE[MAX_USERTYPE_NAME] = "moderator";

void testAdding() {
	//User** arr = new(nothrow) User * [SIZE];
	//Administrator a("Sentinel", 20);
	//User p("Pesho", 18);
	//Moderator m("mitko", 18);
	//a.addUser(p, arr, 0);
	//cout << typeid(*arr[0]).name() << endl;
	//// not adding a.addUser(a, arr, 1);
	////error cout << typeid(*arr[1]).name() << endl;
	//// error Administrator* c = dynamic_cast<Administrator *>(arr[1]);
	////c->addUser(p, arr, 2);
	//cout << typeid(*arr[2]).name() << endl;
	////c->addUser(m, arr, 3);
	//cout << typeid(*arr[0]).name() << endl;
	//Moderator* m2 = dynamic_cast<Moderator*>(arr[3]);
	//m2->blockUser(p);
}

void readStr(char*& str, const size_t max_chars, bool getSpaces) {
	char ch;
	size_t i = 0;

	if (cin.peek() == ' ')
		cin.ignore();

	while (i<max_chars) {
		ch = cin.peek();

		if (ch == '\n' || ch == '\r' || ch == '\0' || (ch==' ' && !getSpaces)) {
			cin.get();
			str[i] = '\0';
			return;
		}

		cin.get(ch);
		str[i] = ch;

		i++;
	}
	cout << "Maximum symbols reached!" << endl;
}

char* getStr(const size_t max_chars, bool getSpaces) {
	//getSpaces indicates if we get the spaces or not
	char* str = new(nothrow) char[MAX_USERNAME_SIZE];
	if (!str)
		return nullptr;
	readStr(str, max_chars, getSpaces);
	return str;
}

void addUser(Administrator& admin, const char user_type[]) {
	char* name = getStr(MAX_USERNAME_SIZE, false);
	unsigned age;
	cin >> age;
	cin.ignore();
	User* u;
	if(strcmp(user_type, USER_TYPE)==0)
		u = new User(admin.getSocialNetwork(), name, age);
	else if(strcmp(user_type, MODER_TYPE) == 0)
		u = new Moderator(admin.getSocialNetwork(), admin.getUserSystem(), name, age);
	else {
		cout << "User type not valid! User not added!" << endl;
		return;
	}
	admin.addUser(u);

}

void showInfo(Administrator& admin) {
	cout << "showing information..." << endl;
	admin.getUserSystem()->printInfo();
}

void removeUser(Administrator& admin, int index) {
	if (index<0) {
		char* name = getStr(MAX_USERNAME_SIZE, false);
		admin.removeUser(name);
	}
	else {
		cout << "User with that name does not exist or is not authorized to remove users! Try again!" << endl;
	}
}

void block_unblock_user(Administrator& admin, int index, bool c) {
	UserSystem* us = admin.getUserSystem();
	char* name = getStr(MAX_USERNAME_SIZE, false);
	if (index<0) {
		if(c)
			admin.blockUser(name);
		else
			admin.unblockUser(name);
	}
	else {

		User* u = us->getUser(index);

		if (strcmp(typeid(*u).name(), typeid(Moderator).name()) == 0) {
			Moderator* m = dynamic_cast<Moderator*>(u);
			if (c)
				m->blockUser(name);
			else
				m->unblockUser(name);
		}
		else {
			cout << u->getName() << " is not authorized to block/unblock users!" << endl;
		}
	}
}

void post(Administrator& admin, int index) {
	UserSystem* us = admin.getUserSystem();
	char* type = getStr(PUB_TYPE_SIZE, false);
	char* content = getStr(MAX_POST, true);
	if (index<0) {
		admin.postPublication(content, type);
	}
	else {
		User* u = us->getUser(index);
		u->postPublication(content, type);
	}
}

void deletePost(Administrator& admin, int index) {
	UserSystem* us = admin.getUserSystem();
	size_t pub_serial;
	cin >> pub_serial;
	if (index < 0) {
		admin.deletePublication(pub_serial);
	}
	else {
		User* u = us->getUser(index);
		u->deletePublication(pub_serial);
	}
}

void viewAllUserPosts(Administrator& admin) {
	char* name = getStr(MAX_USERNAME_SIZE, false);
	admin.getSocialNetwork()->viewAllUserPublications(name);
}

void viewPost(Administrator& admin) {
	//it does not matter who views the publication as long as the user exists 
	unsigned serial;
	cin >> serial;
	admin.viewPublication(serial);
}

void performUserAction(const char user_name[], Administrator& admin) {
	char command[MAX_COMMAND];
	char line[MAX_LINE];

	cin >> command;
	UserSystem* us = admin.getUserSystem();
	int user_index = us->searchUser(user_name);

	if (strcmp(user_name, admin.getName()) != 0 && user_index < 0) {
		cout << "User not found!" << endl;
		cin.getline(line, MAX_LINE);
		return;
	}

	if (strcmp(command, ADD_USER_CMD) == 0) {
		if (strcmp(user_name, admin.getName()) == 0) {
			addUser(admin, USER_TYPE);
		}else {
			cout << "User with that name does not exist or is not authorized to add users! Try again!" << endl;
		}
	} 
	else if (strcmp(command, ADD_MODER_CMD) == 0) {
		if (strcmp(user_name, admin.getName()) == 0) {
			addUser(admin, MODER_TYPE);
		}
		else {
			cout << "User with that name does not exist or is not authorized to add users! Try again!" << endl;
		}
	}
	else if (strcmp(command, REMOVE_USER_CMD) == 0) {
		removeUser(admin, user_index);
	}
	else if (strcmp(command, BLOCK_CMD) == 0) {
		block_unblock_user(admin, user_index, true);
	}
	else if (strcmp(command, UNBLOCK_CMD) == 0) {
		block_unblock_user(admin, user_index, false);
	}
	else if (strcmp(command, POST_CMD) == 0) {
		post(admin, user_index);
	}
	else if (strcmp(command, DEL_POST_CMD) == 0) {
		deletePost(admin, user_index);
	}
	else if (strcmp(command, VIEW_POST_CMD) == 0) {
		viewPost(admin);
	}
	else if (strcmp(command, VIEW_ALL_POST_CMD) == 0) {
		viewAllUserPosts(admin);
	}
	else {
		cout << "Not a valid command, try again!" << endl;
		cin.getline(line, MAX_LINE);
	}
}

bool commandController(char command[MAX_COMMAND], Administrator& admin) {

	char line[MAX_LINE];
	if (strcmp(command, STOP_CMD) == 0)
		return false;
	else if (strcmp(command, INFO_CMD) == 0) {
		showInfo(admin);
		cin.getline(line, MAX_LINE);
	}
	else
		performUserAction(command, admin);

	return true;
}

void openCommandLine(Administrator& admin) {
	std::cout << "Command line is open (add_user, add_moderator, remove_user, block, unblock, post, delete_post, view_post): " << std::endl;
	char command[MAX_COMMAND];

	do {
		std::cout << "Enter your command: ";
		std::cin >> command;
	} while (commandController(command, admin));

}


int main() {
	SocialNetwork* sNetwork = new SocialNetwork();
	UserSystem* uSystem = new UserSystem();
	cout << "Enter Administrator's nickname: " << endl;
	char* admin_name = getStr(MAX_USERNAME_SIZE, false);
	Administrator admin(sNetwork, uSystem, admin_name, 20);

	cout <<"Administrator name: "<<admin.getName() << endl;
	openCommandLine(admin);
	//addUser(admin, MODER_TYPE);
	//addUser(admin, USER_TYPE);

	//User * u = uSystem->getUser(0);
	//Moderator* m = dynamic_cast<Moderator*>(u);
	//m->blockUser(uSystem->getUser(1)->getName());
	//uSystem->reallocUsers();
	////uSystem->getUser(0)->postPublication("https://docs.google.com/document/d/1I3QZKCfwLKUxJ7tAoDmJhvkgbp25kaobI5Q5I1dXjBQ/edit", "url");
	////uSystem->getUser(0)->postPublication("C:\\Users\\VivoBook_X512DA\\Desktop\\success.jpg", "img");
	//uSystem->getUser(0)->postPublication("Hello madafaka", "txt");
	//sNetwork->getPublication(0).showPublication();
	//delete sNetwork;
	//delete uSystem;
	return 0;
}