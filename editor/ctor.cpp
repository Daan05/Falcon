#include "editor.ih"

Editor::Editor()
    : scrollOff(8)
    , cursorRow(0)
    , cursorCol(0)
    , currentRow(0)
{
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    resizeTerminal();
}
