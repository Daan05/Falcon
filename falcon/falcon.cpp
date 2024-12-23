#include "falcon.ih"
#include <ncurses.h>

FalconEditor::FalconEditor()
{
}

FalconEditor::~FalconEditor() {
    //clear();
	endwin();
}

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

void FalconEditor::openFile()
{
    return;
}

void FalconEditor::run()
{
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
    wrefresh(textBufWin);

    drawLines();

	while (!quit)
    {
        processKeypress(readKey());
        drawLines();
    }
}

int FalconEditor::readKey()
{
    return getch();
}

void FalconEditor::processKeypress(int ch)
{
    switch (ch)
    {
    case KEY_F(1):
        quit = true;
        break;
    default:
        break;
    }
}

void FalconEditor::drawLines()
{
    // move cursor to start
    wmove(textBufWin, 1, 0);
    // draw text
    for (size_t ix = conf.cur_row; ix != conf.file_rows; ++ix)
    {
        for (const auto& ch : line)
        {
            waddch(textBufWin, ch);
        }
    }

    // move cursor to correct position and refresh screen
    wmove(textBufWin, conf.cur_row + 1, conf.cur_col);
    wrefresh(textBufWin);
}

