#include "list.h"

void list_destroy(List *l, void (*del) (List *)) {
	if (!l)
		return;
	List *temp = l->tail;
	if (del) {
		del(l);
	} else {
		free(l);
	}
	list_destroy(temp, del);
}

List *list_add(List *l, void *data) {
	List *newL = malloc(sizeof(List));
	if (newL) {
		newL->head = data;
		newL->tail = l;
	}
	return newL;
}