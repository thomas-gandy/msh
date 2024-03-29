#ifndef TERMINAL_HANDLER_H
#define TERMINAL_HANDLER_H

#include <stdio.h>
#include <termios.h>
#include <stdbool.h>


#define TERM_ESCAPE_CHAR 0x1b

#define TERM_CTRL_C 3
#define TERM_KEY_EOF 4
#define TERM_KEY_TAB 9
#define TERM_KEY_DELETE 127
#define TERM_KEY_ENTER 13

#define term_cursor_up(x) printf("\x1b[%dA", x)
#define term_cursor_down(x) printf("\x1b[%dB", x)
#define term_cursor_right(x) printf("\x1b[%dC", x)
#define term_cursor_left(x) printf("\x1b[%dD", x)
#define term_erase_line() printf("\x1b[K")
#define term_get_cursor_pos() printf("\x1b[6n")
#define term_set_cursor_pos(row, col) printf("\x1b[%d;%dH", row, col)
#define term_cursor_hide() printf("\x1b[?25l")
#define term_cursor_show() printf("\x1b[?25h")

typedef struct term_terminalState {
	int width, height;
} term_terminalState;

typedef struct term_position {
	int row, column;
} term_position;

enum keys {TERM_ARROW_UP, TERM_ARROW_RIGHT, TERM_ARROW_DOWN, TERM_ARROW_LEFT, TERM_UNKNOWN};
static struct termios savedTerminal;


// Used to exit program if error occurs in any terminal functions
void term_error(char* errmsg);
// Ensure shell is connected to a terminal device file
void term_ensureTerminalDevice();
// Enable terminal flag for local termios member
void term_enableLocalFlag(tcflag_t flags);
// Disable terminal flag for local termios member
void term_disableLocalFlag(tcflag_t flags);
// Puts current terminal info
struct termios term_getTerm();
// Set current terminal info from struct provided
void term_setTerm(struct termios term);
// Used at beginning before modifying terminal
void term_saveTerm(struct termios term);
// Used for when exiting or launching another process
void term_restoreTerm();
void term_getCursorPosition(struct term_position* pos);
void term_getWindowSize(struct term_position* winSize);


// Returns an enum int value depending on key pressed or ANSI ASCII escape sequence entered
int term_getEscapeKey(char c);

#endif
