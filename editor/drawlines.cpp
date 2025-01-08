#include "editor.ih"
#include <cstddef>
#include <ncurses.h>

void Editor::drawLines()
{

    wmove(textBufWin, 0, 0);
    bool drawExtraLine = false;
    size_t range = currentRow + termRows - 1;
    if (range > fileRows)
    {
        range = fileRows;
        drawExtraLine = true;
    }

    for (size_t ix = currentRow; ix != range; ++ix)
    {
        if (lines[ix].size() > termCols)
            throw std::runtime_error(std::string(
                "Line " + std::to_string(ix)
                + " was longer than the terminal width. As things break "
                  "when this happens, this exception is a temporary "
                  "\"solution\""
            ));
        wprintw(textBufWin, "%s\n", lines[ix].c_str());
    }
    if (drawExtraLine)
        wprintw(textBufWin, "\n");

    // move cursor to correct position and refresh screen
    wmove(
        textBufWin, cursorRow,
        std::min(cursorCol, lines[currentRow + cursorRow].size())
    );
    wrefresh(textBufWin);
}

// This functions draws the text from the current file onto the screen
