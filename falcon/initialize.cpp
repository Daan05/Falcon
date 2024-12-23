#include "falcon.ih"

void FalconEditor::initialize()
{
    // set up terminal the way we like it
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    // get window size
    getmaxyx(stdscr, conf.term_rows, conf.term_cols);
    box(stdscr, 0 , 0);

    // initialize lineNumWin
    lineNumWin = newwin(conf.term_rows - 2, 6, 1, 1);
    textBufWin = newwin(conf.term_rows - 2, conf.term_cols - 9, 1, 8);

    conf.cur_row = 0;
    conf.cur_col = 0;

    conf.file_rows = 1;
}
