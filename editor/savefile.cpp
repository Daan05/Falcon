#include "editor.ih"

void Editor::saveFile()
{
    std::ofstream file(filename);

    // Check if the file was opened successfully
    if (!file)
        throw std::runtime_error(
            std::string("Could not open file " + filename + "for saving\n")
        );

    // Write each string to the file
    for (std::string const &line : lines)
    {
        file << line << '\n'; // Write the string followed by a newline
    }

    // Close the file
    file.close();

    // succes message
    std::string msg = "Succesfully saved " + std::to_string(fileRows)
        + " lines to " + filename.c_str() + "   ";
    wmove(stdscr, termRows - 1, termCols - msg.length());
    wprintw(stdscr, "%s", msg.c_str());
    refresh();
}
