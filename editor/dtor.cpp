#include "editor.ih"

Editor::~Editor()
{
	endwin();
}

// endwin() returns the terminal backk to normal mode and cleans up memory
