#include <iostream>

#include "editor/editor.hpp"

int main(int argc, char **argv)
try
{
    Editor editor;
    if (argc > 1)
        editor.openFile(argv[1]);
    editor.run();
}
catch (std::runtime_error const &err)
{
    std::cout << "Runtime error: " << err.what() << "\n";
}
