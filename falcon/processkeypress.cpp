#include "falcon.ih"

void FalconEditor::processKeypress(int ch)
{
    switch (ch)
    {
    case KEY_F(1):
        quit = true;
        break;
    default:
        break;
    }
}

// This function takes in a keypress and processes the key
