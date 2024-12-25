#include "falcon.ih"

FalconEditor::~FalconEditor()
{
	endwin();
}

// endwin() returns the terminal backk to normal mode and cleans up memory
