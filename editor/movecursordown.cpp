#include "editor.ih"

void Editor::moveCursorDown()
{
    if (cursorRow + currentRow < fileRows - 1)
    {
        ++cursorRow;
        if (currentRow + termRows - 1 < fileRows
            && cursorRow + 2 > termRows - scrollOff)
        {
            ++currentRow;
            --cursorRow;
            drawLineNumbers();
        }
    }
}
