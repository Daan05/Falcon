#include "falcon.ih"

void FalconEditor::openFile(std::string filename)
{
    std::ifstream file(conf.workingDirectory);
    
    if (!file)
        throw std::runtime_error(std::string(
            "Could not open file " + filename + "\n"));
    
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    // file is open
    file.close();
}

// This function opens a filepath from <filesystem> and loads its data
