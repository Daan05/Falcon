#include "editor.ih"

void Editor::moveCursorUp()
{
    if (cursorRow > 0)
    {
        --cursorRow;
        if (currentRow > 0 && cursorRow < scrollOff)
        {
            --currentRow;
            ++cursorRow;
            drawLineNumbers();
        }
    }
}
