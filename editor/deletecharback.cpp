#include "editor.ih"

void Editor::deleteCharBack()
{
    if (cursorCol > 0
        && lines[currentRow + cursorRow].size()
            != 0) // cursor not at start of line
    {
        lines[currentRow + cursorRow].erase(
            std::min(cursorCol, lines[currentRow + cursorRow].size()) - 1, 1
        );
        --cursorCol;
    }
    else
    {
        if (lines[currentRow + cursorRow].size() == 0) // empty line
        {
            lines.erase(lines.begin() + currentRow + cursorRow);
            --fileRows;
            moveCursorUp();
            cursorCol = lines[currentRow + cursorRow].size();
        }
        else
        {
            if (cursorRow + cursorRow != 0) // not at start of file
            {
                cursorCol = lines[currentRow + cursorRow - 1].size();
                lines[currentRow + cursorRow - 1]
                    += lines[currentRow + cursorRow];
                lines.erase(lines.begin() + currentRow + cursorRow);
                --fileRows;
                moveCursorUp();
            }
        }
    }

    if (currentRow + termRows > fileRows)
    {
        moveCursorDown();
        currentRow = fileRows - termRows;
        drawLineNumbers();
    }
}
