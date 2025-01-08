#include "editor.ih"

void Editor::insertChar(int ch)
{
    if (ch > 32 && ch < 126)
    {
        lines[currentRow + cursorRow].insert(cursorCol, 1, ch);
        ++cursorCol;
    }
    else if (ch == '\n')
    {
        if (cursorCol == 0)
        {
            lines.insert(
                lines.begin() + currentRow + cursorRow, std::string("")
            );
            ++fileRows;
            moveCursorDown();
        }
        else
        {
            lines.insert(
                lines.begin() + currentRow + cursorRow + 1, std::string("")
            );
            ++fileRows;

            std::string str = lines[currentRow + cursorRow].substr(cursorCol);
            lines[currentRow + cursorRow + 1].append(str);
            lines[currentRow + cursorRow].erase(
                lines[currentRow + cursorRow].begin() + cursorCol,
                lines[currentRow + cursorRow].end()
            );
        }
    }
}
