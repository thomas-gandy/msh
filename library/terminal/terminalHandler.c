#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "terminalHandler.h"


void term_error(char* errmsg) {
	printf("%s\n", errmsg);
	exit(EXIT_FAILURE);
}

void term_ensureTerminalDevice() {
	if (!isatty(STDIN_FILENO))
		term_error("Standard input is not connected to a terminal device file");
}

void term_enableLocalFlag(tcflag_t flags) {
	struct termios termSettings;
	int result;

	term_ensureTerminalDevice();
	if ((result = tcgetattr(STDIN_FILENO, &termSettings)) != 0)
		term_error("Failed to get terminal attributes");

	termSettings.c_lflag &= flags;
	if ((result = tcsetattr(STDIN_FILENO,TCSADRAIN, &termSettings)) != 0)
		term_error("Failed to set terminal attributes");
}

void term_disableLocalFlag(tcflag_t flags) {
	struct termios termSettings;
	int result;

	term_ensureTerminalDevice();
	if ((result = tcgetattr(STDIN_FILENO, &termSettings)) != 0)
		term_error("Failed to get terminal attributes");

	termSettings.c_lflag &= ~flags;
	if ((result = tcsetattr(STDIN_FILENO,TCSADRAIN, &termSettings)) != 0)
		term_error("Failed to set terminal attributes");
}

void term_getCurrentTerm(struct termios* term) {
	int result;

	term_ensureTerminalDevice();
	if ((result = tcgetattr(STDIN_FILENO, term)) != 0)
		term_error("Failed to get terminal attributes");
}

void term_setCurrentTerm(struct termios* term) {
	int result;
	
	term_ensureTerminalDevice();
	if ((result = tcsetattr(STDIN_FILENO,TCSADRAIN, term)) != 0)
		term_error("Failed to set terminal attributes");
}

void term_saveOriginalTerm() {
	int result;
	term_ensureTerminalDevice();
	if ((result = tcgetattr(STDIN_FILENO, &originalTerm)) != 0)
		term_error("Failed to save terminal attributes");
}

void term_restoreOriginalTerm() {
	int result;
	term_ensureTerminalDevice();
	if ((result = tcsetattr(STDIN_FILENO,TCSADRAIN, &originalTerm)) != 0)
		term_error("Failed to restore terminal attributes");
}


int term_handleEscapeSequence(int c) {
	char seq[3];

	if (read(STDIN_FILENO, &seq[0], 1) != 1) return TERM_ESCAPE_CHAR;
	if (read(STDIN_FILENO, &seq[1], 1) != 1) return TERM_ESCAPE_CHAR;

	if (seq[0] == '[') {
		switch (seq[1]) {
			case 'A': return TERM_ARROW_UP;
			case 'B': return TERM_ARROW_DOWN;
			case 'C': return TERM_ARROW_RIGHT;
			case 'D': return TERM_ARROW_LEFT;
		}
	}

	return TERM_UNKNOWN;
}