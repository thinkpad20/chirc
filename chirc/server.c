#include "server.h"

void addUser(Server *server, const char *nick, int socketfd);
void sendError(Server *server, int errorCode);
void writeToSocket(Server *server, const char *message);

Server *server_make(int socketfd) {
	Server *newServer = malloc(sizeof(Server));
	if (newServer) {
		newServer->socketfd = socketfd;
		newServer->channels = newServer->users = NULL;
	}
	return newServer;
}

void server_handleRequest(Server *server, const char *req, int socketfd) {
	if (strstr(req, "NICK") == req) {
		char nick[MAX_NAME_LENGTH+1];// nickname
		strcpy(nick, req + 6);
		addUser(server, nick, socketfd);
	} 
}

void sendError(Server *server, int errorCode) {
	switch(errorCode) {
		case TOO_LONG:
			printf("Error: username is too long.");
			// writeToSocket(server, "Error: username is too long.");
			break;
		case INVALID_CHAR:
			printf("Error: username contains invalid characters.");
			// writeToSocket(server, "Error: username contains invalid characters.");
			break;
		case IN_USE:
			printf("Error: username is already in use.");
			// writeToSocket(server, "Error: username is already in use.");
			break;
		default:
			break;
	}	
}

void addUser(Server *server, const char *nick, int socketfd) {
	int valid = user_isValidName(nick, server);
	if (valid == 0) {
		// create user object
		User *newUser = user_make(nick, socketfd);
		// add user to list
		server->users = list_add(server->users, newUser);
	} 
	else {
		sendError(server, valid);
		return;
	}
}

User *server_findUser(Server *server, const char *nick) {
	List *track = server->users;
	while (track) {
		if (!strcmp(((User *)track->head)->nick, nick))
			return track->head;
		track = track->tail;
	}
	return NULL;
}

void writeToSocket(Server *server, const char *message) {
	size_t len = strlen(message);
	int bytesWritten = 0;
	while (true) {
		bytesWritten += send(server->socketfd, message + bytesWritten, len, 0);
		if (bytesWritten-len == 0)
			break;
	}
}

void server_delete(Server *server) {
	list_destroy(server->users, NULL);
	list_destroy(server->channels, NULL);
	free(server);
}