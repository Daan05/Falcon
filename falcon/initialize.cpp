#include "falcon.ih"

void FalconEditor::initialize()
{
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    getmaxyx(stdscr, conf.term_rows, conf.term_cols);
    box(stdscr, 0 , 0);

    lineNumWin = newwin(conf.term_rows - 2, 6, 1, 1);
    textBufWin = newwin(conf.term_rows - 2, conf.term_cols - 9, 1, 8);

    conf.cursor_row = 0;
    conf.cursor_col = 0;

    conf.row = 0;
    conf.scrolloff = 8;

    conf.current_row = conf.row + conf.cursor_row;

    move(0, 2);
	printw(" Falcon -- The best terminal based text editor out there ");
    move(1, 1);
    refresh();

    drawLineNumbers();
    
    wmove(textBufWin, 1, 0);
    drawLines();
    wrefresh(textBufWin);
}

// This function enabled rawmode and configures the terminal to the way we want it.
// gets the window size, creates a  window for the line numbers and text buffer.
// prints the line numbers
