#include "editor.ih"

void Editor::run()
{
    while (!quit)
    {
        processKeypress(readKey());
        drawLines();
    }
}

// This function is the run loop
