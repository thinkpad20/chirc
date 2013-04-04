#ifndef __LIST_H_
#define __LIST_H_

#include "irc.h"

typedef struct list {
	void *head;
	struct list *tail;
} List;

void list_destroy(List *l, void (*) (List *));
List *list_add(List *l, void *data);
#endif