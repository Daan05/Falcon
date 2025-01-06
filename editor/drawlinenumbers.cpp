#include "editor.ih"

void Editor::drawLineNumbers()
{
    wmove(lineNumWin, 0, 0);
    for (size_t ix = current_row + 1; ix != current_row + term_rows; ++ix)
    {
        wprintw(lineNumWin, "%*zu\n", 5, ix);
    }
    wrefresh(lineNumWin);
}
