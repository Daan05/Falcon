#include "falcon.ih"

void FalconEditor::drawLines()
{
    // move cursor to start
    wmove(textBufWin, 0, 0);
    // draw text
    for (size_t ix = conf.current_row; ix != std::min(
        conf.current_row + conf.term_rows - 1, conf.file_rows); ++ix)
    {
        wprintw(textBufWin, "%s\n", lines[ix].c_str());
    }

    // move cursor to correct position and refresh screen
    wmove(textBufWin, conf.relative_row, conf.cursor_col);
    wrefresh(textBufWin);
}

// This functions draws the text from the current file onto the screen
