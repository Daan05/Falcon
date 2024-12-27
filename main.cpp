#include <iostream>

#include "falcon/falcon.hpp"

int main(int argc, char **argv)
try
{
    FalconEditor editor;
    if (argc > 1)
        editor.openFile(argv[1]);
    editor.initialize();
    editor.run();
}
catch (std::runtime_error const &err)
{
    std::cout << "Runtime error: " << err.what() << "\n";
}

