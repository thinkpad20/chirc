#ifndef __SERVER_H_
#define __SERVER_H_

#include "irc.h"
#include "user.h"

typedef struct server {
	int socketfd;
	List *channels;
	List *users;
	/* channel list descruction function */
	/* add channel function */
	/* add user to channel function */
	/* parse instruction */
} Server;

Server *server_make(int socketfd);
void server_handleRequest(Server *server, const char *req, int socketfd);
void server_delete(Server *server);
User *server_findUser(Server *server, const char *name);

#endif