#include "falcon.ih"

void FalconEditor::drawLineNumbers()
{
    wmove(lineNumWin, 0, 0);
    for (size_t ix = conf.current_row + 1; ix != conf.current_row + conf.term_rows; ++ix)
    {
        wprintw(lineNumWin, "%*zu\n", 5, ix);
    }
    wrefresh(lineNumWin);
}
