#include "editor.ih"

void Editor::deleteCharBack()
{
    size_t fileRowsStart = fileRows;

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
        if (cursorRow > 0) // not at top of file
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
        currentRow = fileRows - termRows;
        drawLineNumbers();
        moveCursorDown();
        if (fileRowsStart != fileRows)
            moveCursorDown();
    }
}
