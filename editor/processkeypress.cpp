#include "editor.ih"

void Editor::processKeypress(int ch)
{
    switch (ch)
    {
    case KEY_F(1):
        quit = true;
        break;
    case controlKey('q'):
        quit = true;
        break;
    case KEY_BACKSPACE:
        deleteCharBack();
        break;
    case KEY_DC:
        deleteCharForw();
        break;
    case KEY_UP:
        moveCursorUp();
        break;
    case KEY_DOWN:
        moveCursorDown();
        break;
    case KEY_LEFT:
        if (cursorCol > 0)
            cursorCol
                = std::min(cursorCol, lines[currentRow + cursorRow].size()) - 1;
        break;
    case KEY_RIGHT:
        if (cursorCol < lines[currentRow + cursorRow].size())
            ++cursorCol;
        break;
    case controlKey('u'):
        for (size_t ix = 0; ix != termRows / 2; ++ix)
            moveCursorUp();
        cursorCol = 0;
        break;
    case controlKey('d'):
        for (size_t ix = 0; ix != termRows / 2; ++ix)
            moveCursorDown();
        cursorCol = 0;
        break;
    case controlKey('s'):
        saveFile();
        break;
    case KEY_RESIZE:
        resizeTerminal();
    default:
        insertChar(ch);

        break;
    }
}

// This function takes in a keypress and processes the key
