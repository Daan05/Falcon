#include "editor.ih"

void Editor::deleteCharForw()
{
    if (cursorCol < lines[currentRow + cursorRow].size())
    {
        ++cursorCol;
        deleteCharBack();
    }
    else
    {
        if (currentRow + cursorRow < fileRows - 1)
        {
            lines[currentRow + cursorRow] += lines[currentRow + cursorRow + 1];
            lines.erase(lines.begin() + currentRow + cursorRow + 1);
            --fileRows;
        }
    }
}
