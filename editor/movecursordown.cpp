#include "editor.ih"

void Editor::moveColumnDown()
{
    if (cursor_row + current_row < file_rows - 1)
    {
        ++cursor_row;
        if (current_row + term_rows - 1 < file_rows
            && cursor_row + 2 > term_rows - scrolloff)
        {
            ++current_row;
            --cursor_row;
            drawLineNumbers();
        }
    }
}
