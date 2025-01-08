#include "editor.ih"

void Editor::saveFile()
{
    std::ofstream file(filename);

    if (!file)
        throw std::runtime_error(
            std::string("Could not open file " + filename + "for saving\n")
        );

    for (std::string const &line : lines)
    {
        file << line << '\n';
    }

    file.close();

    std::string msg = "Succesfully saved " + std::to_string(fileRows)
        + " lines to " + filename.c_str() + "   ";
    wmove(stdscr, termRows - 1, termCols - msg.length());
    wprintw(stdscr, "%s", msg.c_str());
    refresh();
}
