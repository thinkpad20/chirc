#ifndef __CHANNEL_H_
#define __CHANNEL_H_

#include "irc.h"
#define MAX_CHANNEL_NAME 50 // see RFC2812-1.3

typedef struct channel {
	char name[MAX_CHANNEL_NAME+1]; //
	List *users;
} Channel;

Channel *channel_make(const char *name, List *initialUsers);
_Bool channel_isValidName(const char *name);
_Bool channel_isEqual(const char *name1, const char *name2);

#endif