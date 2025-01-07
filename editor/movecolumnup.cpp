#include "editor.ih"

void Editor::moveColumnUp()
{
    if (cursor_row > 0)
    {
        --cursor_row;
        if (current_row > 0 && cursor_row < scrolloff)
        {
            --current_row;
            ++cursor_row;
            drawLineNumbers();
        }
    }
}
