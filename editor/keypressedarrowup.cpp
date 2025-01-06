#include "editor.ih"

void Editor::keypressedArrowUp()
{
    if (relative_row > 0)
    {
        --relative_row;
        if (current_row > 0 && relative_row < scrolloff)
        {
            --current_row;
            ++relative_row;
        }
        drawLineNumbers();
    }
}
