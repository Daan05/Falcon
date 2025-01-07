#include "editor.ih"
#include <ncurses.h>

void Editor::initialize()
{
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    currentRow = 0;
    scrollOff = 8;
    cursorRow = 0;
    cursorCol = 0;

    resizeTerminal();
}

// This function enabled rawmode and configures the terminal to the way we want
// it. gets the window size, creates a  window for the line numbers and text
// buffer. prints the line numbers
