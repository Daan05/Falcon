#include "editor.ih"

void Editor::drawLines()
{

    wmove(textBufWin, 0, 0);
    for (size_t ix = currentRow;
         ix != std::min(currentRow + termRows - 1, fileRows); ++ix)
    {
        if (lines[ix].size() > termCols)
            throw std::runtime_error(
                "A line was longer than the terminal width. As things break "
                "when this happens, this exception is a temporary \"solution\""
            );
        wprintw(textBufWin, "%s\n", lines[ix].c_str());
    }

    // move cursor to correct position and refresh screen
    wmove(
        textBufWin, cursorRow,
        std::min(cursorCol, lines[currentRow + cursorRow].size())
    );
    wrefresh(textBufWin);
}

// This functions draws the text from the current file onto the screen
