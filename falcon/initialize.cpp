#include "falcon.ih"
#include <ncurses.h>

void FalconEditor::initialize()
{
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    getmaxyx(stdscr, conf.term_rows, conf.term_cols);

    lineNumWin = newwin(conf.term_rows, 6, 0, 0);
    textBufWin = newwin(conf.term_rows, conf.term_cols - 6, 0, 8);

    conf.cursor_row = 0;
    conf.cursor_col = 0;

    conf.current_row = 0;
    conf.scrolloff = 8;

    conf.relative_row = 0;

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
