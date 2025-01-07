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
    case KEY_UP:
        moveColumnUp();
        break;
    case KEY_DOWN:
        moveColumnDown();
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
            moveColumnUp();
        cursor_col = 0;
        break;
    case controlKey('d'):
        for (size_t ix = 0; ix != term_rows / 2; ++ix)
            moveColumnDown();
        cursor_col = 0;
        break;
    default:
        break;
    }
}

// This function takes in a keypress and processes the key
