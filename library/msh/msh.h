#ifndef MSH_H
#define MSH_H

#include <stdio.h>
#include "../datastructures/hashMap.h"
#include "../datastructures/list.h"
#include "../string/string.h"

#define TOKEN_BUFFER_SIZE 32


// initialise data structures, set non canonical buffering for terminal and program
void msh_start(char* envp[]);
void msh_initTerminal();
// initialise builtin hashmap
static void msh_init_builtins();
// initialise aliases hashmap
static void msh_init_aliases();
// initialise environments hashmap
static void msh_init_environments(char* envp[]);
// gets user input and executes until user exits
void msh_loop();
// redraw terminal line if user adds or erases character from input buffer
static void msh_redraw(char* line);
// readline from user input essentially until return key pressed
char* msh_readinput();
int msh_handleKey(struct string* input, char c, int* cursorIndex, int* cursorBoundary);
// prints prompt to tell user to type
static void msh_printPrompt();
// Extracts token from delimited line
static char* msh_extractToken(char** line);
// Create token list from line (uses the extractToken function)
static char** msh_parse(char* line);
static void msh_execvpe(char* execFile, char* argv[], char* evnp[]);
// executes the command stored in the first token, with the remainders given as arguments
static void msh_execute(char** tokens);
void msh_clean();

struct list_list* msh_generateEnvironmentTokens();

#endif
