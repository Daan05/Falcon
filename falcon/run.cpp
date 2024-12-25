#include "falcon.ih"

void FalconEditor::run()
{
    while (!quit)
    {
        processKeypress(readKey());
        drawLines();
    }
}

// This function is the run loop
