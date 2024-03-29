#ifndef ALIASES_H
#define ALIASES_H

#include <stdbool.h>


// Functions provided for hash map / linked list
int index_alias(void* key);
bool compare_alias(void* k1, void* k2);
void output_alias(void* key, void* value);


#endif
