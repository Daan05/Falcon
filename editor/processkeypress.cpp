#include "editor.ih"

void Editor::processKeypress(int ch)
{
    switch (ch)
    {
    case KEY_F(1):
        quit = true;
        break;
    case KEY_UP:
        keypressedArrowUp();
        break;
    case KEY_DOWN:
        keypressedArrowDown();
        break;
    case KEY_LEFT:
        break;
    case KEY_RIGHT:
        break;
    case control_key('u'):
        for (size_t ix = 0; ix != term_rows / 2; ++ix)
            keypressedArrowUp();
        break;
    case control_key('d'):
        for (size_t ix = 0; ix != term_rows / 2; ++ix)
            keypressedArrowDown();
        break;
    default:
        break;
    }
}

// This function takes in a keypress and processes the key
