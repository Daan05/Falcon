#include "falcon.ih"

void FalconEditor::drawLineNumbers()
{
    wmove(lineNumWin, 1, 0);
    for (size_t ix = conf.row + 1; ix != conf.row + conf.term_rows - 1; ++ix)
    {
        wprintw(lineNumWin, "%*zu\n", 5, ix);
    }
    wrefresh(lineNumWin);
}
