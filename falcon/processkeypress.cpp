#include "falcon.ih"

void FalconEditor::processKeypress(int ch)
{
    switch (ch)
    {
    case KEY_F(1):
        quit = true;
        break;
    case KEY_UP:
        if (conf.relative_row > 0)
        {
            --conf.relative_row;
            if (conf.current_row > 0 && conf.relative_row < conf.scrolloff)
            {
                --conf.current_row;
                ++conf.relative_row;
            }
            drawLineNumbers();
        }
        break;
    case KEY_DOWN:
        if (conf.relative_row + conf.current_row < conf.file_rows - 1)
        {
            ++conf.relative_row;
            if (conf.current_row + conf.term_rows - 1 < conf.file_rows && conf.relative_row + 2 > conf.term_rows - conf.scrolloff)
            {
                ++conf.current_row;
                --conf.relative_row;
            }
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
