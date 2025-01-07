#include "editor.ih"

void Editor::drawLines()
{
    // move cursor to start
    wmove(textBufWin, 0, 0);
    // draw text
    for (size_t ix = current_row;
         ix != std::min(current_row + term_rows - 1, file_rows); ++ix)
    {
        if (lines[ix].size() > term_cols)
            throw std::runtime_error(
                "A line was longer than the terminal width. As things break "
                "when this happens, this exception is a temporary \"solution\""
            );
        wprintw(textBufWin, "%s\n", lines[ix].c_str());
    }

    // move cursor to correct position and refresh screen
    wmove(
        textBufWin, cursor_row,
        std::min(cursor_col, lines[current_row + cursor_row].size())
    );
    wrefresh(textBufWin);
}

// This functions draws the text from the current file onto the screen
