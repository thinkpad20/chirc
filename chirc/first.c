#include <stdlib.h>
#define MAX_NAME 9 
/* this is the max according to RFC2812-1.2.1 but can be 
changed by the implementor if desired*/
struct user {
	int socketfd;
	char nick[MAX_NAME+1];
	char *mode;
};

struct list {
	void *head;
	struct list *tail;
};

void list_destroy(struct list *l) {
	if (!l)
		return;
	struct list *temp = l->tail;
	free(l);
	list_destroy(temp);
}

struct channel {
	char *name;
	struct list *users;
};

struct serverManager {
	struct list *channels;
	/* channel list descruction function */
	/* add channel function */
	/* add user to channel function */
	/* parse instruction */
};

/* channel x: bob, jane, tom, bill 

JOIN terrence x

channel x: bob, jane, tom, bill, terrence

EXIT jane x

channel x: bob, tom, bill, terrence

*/