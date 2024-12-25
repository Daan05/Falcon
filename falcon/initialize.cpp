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

    conf.cur_row = 0;
    conf.cur_col = 0;

    conf.file_rows = 1;

    move(0, 2);
	printw(" Falcon -- The best terminal based text editor out there ");
    move(1, 1);
    refresh();

    wmove(lineNumWin, 1, 0);
    for (size_t ix = 1; ix < conf.term_rows - 1; ++ix)
    {
        wprintw(lineNumWin, "%*zu\n", 5, ix);
    }
    wrefresh(lineNumWin);
    
    wmove(textBufWin, 1, 0);
    drawLines();
    wrefresh(textBufWin);
}

// This function enabled rawmode and configures the terminal to the way we want it.
// gets the window size, creates a  window for the line numbers and text buffer.
// prints the line numbers
