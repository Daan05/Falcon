#include "editor.ih"

void Editor::drawLines()
{
    // move cursor to start
    wmove(textBufWin, 0, 0);
    // draw text
    for (size_t ix = current_row;
         ix != std::min(current_row + term_rows - 1, file_rows); ++ix)
    {
        wprintw(textBufWin, "%s\n", lines[ix].c_str());
    }

    // move cursor to correct position and refresh screen
    wmove(textBufWin, relative_row, 0);
    wrefresh(textBufWin);
}

// This functions draws the text from the current file onto the screen
