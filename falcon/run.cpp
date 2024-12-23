#include "falcon.ih"

void FalconEditor::run()
{
    move(0, 2);
	printw(" Falcon -- The best terminal based text editor out there ");
    move(1, 1);
    refresh();

    wmove(lineNumWin, 1, 0);
    for (size_t ix = 1; ix < conf.term_rows - 1; ++ix)
    {
        wprintw(lineNumWin, "%*zu\n", 5, ix);
    }
    wrefresh(lineNumWin);
    
    wmove(textBufWin, 1, 0);
    wrefresh(textBufWin);

    drawLines();

	while (!quit)
    {
        processKeypress(readKey());
        drawLines();
    }
}

