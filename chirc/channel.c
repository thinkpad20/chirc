#include "channel.h"

_Bool channel_isValidName(const char *name) {
	size_t len;
	// begins with &, +, # or !
	if (!name) 
		return false;
	if (name[0] != '&' && name[0] != '+' && name[0] != '#' && name[0] != '!')
		return false;
	// length <= 50
	if ((len = strlen(name)) > 50)
		return false;
	// can't contain space, ^G (7), or comma.
	for (int i=0; i<len; ++i) {
		if (name[i] == ' ' || name[i] == 7 || name[i] == ',')
			return false;
	}
	return true;
}

_Bool channel_isEqual(const char *name1, const char *name2) {
	int len = strlen(name1);
	if (len < strlen(name2))
		return false;
	for (int i=0; i<len; ++i) {
		char c1 = name1[i], c2 = name2[i];
		if (tolower(c1) != tolower(c2))
			return false;
	}
	return true;
}