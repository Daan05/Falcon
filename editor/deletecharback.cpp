#include "editor.ih"

void Editor::deleteCharBack()
{
    if (cursor_col > 0
        && lines[current_row + cursor_row].size()
            != 0) // cursor not at start of line
    {
        lines[current_row + cursor_row].erase(
            std::min(cursor_col, lines[current_row + cursor_row].size()) - 1, 1
        );
        --cursor_col;
    }
    else
    {
        if (lines[current_row + cursor_row].size() == 0) // empty line
        {
            lines.erase(lines.begin() + current_row + cursor_row);
            --file_rows;
            moveColumnUp();
            cursor_col = lines[current_row + cursor_row].size();
        }
        else
        {
            if (cursor_row + cursor_row != 0) // not at start of file
            {
                cursor_col = lines[current_row + cursor_row - 1].size();
                lines[current_row + cursor_row - 1]
                    += lines[current_row + cursor_row];
                lines.erase(lines.begin() + current_row + cursor_row);
                --file_rows;
                moveColumnUp();
            }
        }
    }

    if (current_row + term_rows > file_rows)
    {
        moveColumnDown();
        current_row = file_rows - term_rows;
        drawLineNumbers();
    }
}
