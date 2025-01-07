#include "editor.ih"

void Editor::resizeTerminal()
{
    getmaxyx(stdscr, termRows, termCols);

    if (termRows < 16 || termCols < 9)
        throw std::runtime_error("The terminal is too small to work with");

    lineNumWin = newwin(termRows, 6, 0, 0);
    textBufWin = newwin(termRows, termCols - 6, 0, 8);

    /*start_color();*/
    /*init_pair(1, COLOR_GREEN, COLOR_BLACK);*/
    /*attron(COLOR_PAIR(1));*/
    /*//print();*/
    /*attroff(COLOR_PAIR(1));*/

    refresh();
    drawLineNumbers();
    drawLines();
}
