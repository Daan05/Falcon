#include "editor.ih"

void Editor::run()
{
    while (!quit)
    {
        drawLines();
        processKeypress(readKey());
    }
}

// This function is the run loop
