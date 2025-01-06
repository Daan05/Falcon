#include "editor.ih"
#include <ncurses.h>

void Editor::initialize()
{
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    getmaxyx(stdscr, term_rows, term_cols);

    lineNumWin = newwin(term_rows, 6, 0, 0);
    textBufWin = newwin(term_rows, term_cols - 6, 0, 8);

    current_row = 0;
    scrolloff = 8;
    relative_row = 0;

    /*start_color();*/
    /*init_pair(1, COLOR_GREEN, COLOR_BLACK);*/
    /*attron(COLOR_PAIR(1));*/
    /*//print();*/
    /*attroff(COLOR_PAIR(1));*/

    refresh();
    drawLineNumbers();
    drawLines();
}

// This function enabled rawmode and configures the terminal to the way we want it.
// gets the window size, creates a  window for the line numbers and text buffer.
// prints the line numbers
