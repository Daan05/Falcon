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
        if (cursor_col < lines[current_row + cursor_row].size())
            ++cursor_col;
        deleteCharBack();
        break;
    case KEY_UP:
        moveCursorUp();
        break;
    case KEY_DOWN:
        moveCursorDown();
        break;
    case KEY_LEFT:
        if (cursor_col > 0)
            --cursor_col;
        break;
    case KEY_RIGHT:
        if (cursor_col < lines[current_row + cursor_row].size())
            ++cursor_col;
        break;
    case controlKey('u'):
        for (size_t ix = 0; ix != term_rows / 2; ++ix)
            moveCursorUp();
        cursor_col = 0;
        break;
    case controlKey('d'):
        for (size_t ix = 0; ix != term_rows / 2; ++ix)
            moveCursorDown();
        cursor_col = 0;
        break;
    case controlKey('s'):
        saveFile();
        break;
    default:
        break;
    }
}

// This function takes in a keypress and processes the key
