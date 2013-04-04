#ifndef __USER_H_
#define __USER_H_

#include "irc.h"
#include "server.h"
#define MAX_NAME_LENGTH 15
/* this is the max according to RFC2812-1.2.1 but can be 
changed by the implementor if desired*/
/* error codes for isValidName */
#define TOO_LONG 1
#define INVALID_CHAR 2
#define IN_USE 3

typedef struct user {
	int socketfd;
	_Bool isOperator; // operators can close a connection
	char nick[MAX_NAME_LENGTH+1];
	char mode;
} User;

User *user_make(const char *nick, int socketfd);
int user_isValidName(const char *name, Server *server);

#endif