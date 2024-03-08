#include "item.h"
#include <string.h>
#include <stdio.h>

// implementation of the cmp() function on items, for when items are ints
bool cmp(item *i1, item *i2) {
	char * i1_char = (*i1).key;
	char * i2_char = (*i2).key;
	
	return strcmp(i1_char, i2_char) == 0;
}
