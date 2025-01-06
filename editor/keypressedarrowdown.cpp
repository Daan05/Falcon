#include "editor.ih"

void Editor::keypressedArrowDown()
{
    if (relative_row + current_row < file_rows - 1)
    {
        ++relative_row;
        if (current_row + term_rows - 1 < file_rows && relative_row + 2 > term_rows - scrolloff)
        {
            ++current_row;
            --relative_row;
        }
        drawLineNumbers();
    }
}
