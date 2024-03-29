#ifndef BUILTINS_H
#define BUILTINS_H


#include <stdbool.h>

// Functions provided for hash map / linked list
int index_builtin(void* key);
bool compare_builtin(void* k1, void* k2);
void output_builtin(void* key, void* value);


// builtin functions
int builtin_cd(char** tokens);
int builtin_alias(char** tokens);
int builtin_exit(char** tokens);

#endif
