#include "user.h"

User *user_make(const char *name, int socketfd) {
	User *newUser = malloc(sizeof(User));
	if (newUser) {
		newUser->socketfd = socketfd;
		strcpy(newUser->nick, name);
		newUser->mode = 0;
		newUser->isOperator = false;
	}
	return newUser;
}

int user_isValidName(const char *name, Server *server) {
	size_t len;
	// begins with &, +, # or !
	if (!name) 
		return -1;
			// length <= 50
	if ((len = strlen(name)) > 9)
		return TOO_LONG;
	// can't contain space, ^G (7), or comma.
	for (int i=0; i<len; ++i) {
		if (name[i] == ' ' || name[i] == 7 || name[i] == ',')
			return INVALID_CHAR;
	}
	if (server_findUser(server, name))
		return IN_USE;
	return 0;
}