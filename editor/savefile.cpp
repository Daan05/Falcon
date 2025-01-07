#include "editor.ih"

void Editor::saveFile()
{
    std::ofstream file(filename);

    // Check if the file was opened successfully
    if (!file)
        throw std::runtime_error(std::string(
            "Could not open file " + std::string(filename) + "for saving\n"
        ));

    // Write each string to the file
    for (std::string const &line : lines)
    {
        file << line << '\n'; // Write the string followed by a newline
    }

    // Close the file
    file.close();
}
