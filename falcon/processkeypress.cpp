#include "falcon.ih"

void FalconEditor::processKeypress(int ch)
{
    switch (ch)
    {
    case KEY_F(1):
        quit = true;
        break;
    case KEY_UP:
        if (conf.row > 0)
        {
            --conf.row;
            drawLineNumbers();
        }
        break;
    case KEY_DOWN:
        if (conf.row + conf.term_rows - 3 < conf.file_rows)
        {
            ++conf.row;
            drawLineNumbers();
        }
        break;
    case KEY_LEFT:
        break;
    case KEY_RIGHT:
        break;
    default:
        break;
    }
}

// This function takes in a keypress and processes the key
