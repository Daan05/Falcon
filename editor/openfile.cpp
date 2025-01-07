#include "editor.ih"

void Editor::openFile(char const *filename)
{
    this->filename = filename;
    std::ifstream file(filename);

    if (!file)
        throw std::runtime_error(
            std::string("Could not open file " + std::string(filename) + "\n")
        );

    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();
    file_rows = lines.size();
}

// This function opens a filepath from <filesystem> and loads its data
