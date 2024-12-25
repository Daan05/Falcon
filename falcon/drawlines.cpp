#include "falcon.ih"

void FalconEditor::drawLines()
{
    // move cursor to start
    wmove(textBufWin, 1, 0);
    // draw text
    for (size_t ix = conf.cur_row; ix != conf.file_rows; ++ix)
    {
        for (const std::string& line : lines)
        {
            wprintw(textBufWin, "%s\n", line.c_str());
        }
    }

    // move cursor to correct position and refresh screen
    wmove(textBufWin, conf.cur_row + 1, conf.cur_col);
    wrefresh(textBufWin);
}

// This functions draws the text from the current file onto the screen
