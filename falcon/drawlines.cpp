#include "falcon.ih"

void FalconEditor::drawLines()
{
    // move cursor to start
    wmove(textBufWin, 1, 0);
    // draw text
    for (size_t ix = conf.row; ix != std::min(
        conf.row + conf.term_rows - 3, conf.file_rows); ++ix)
    {
        wprintw(textBufWin, "%s\n", lines[ix].c_str());
    }

    // move cursor to correct position and refresh screen
    wmove(textBufWin, conf.cursor_row + 1, conf.cursor_col);
    wrefresh(textBufWin);
}

// This functions draws the text from the current file onto the screen
