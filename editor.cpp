#include <iostream>

#include "falcon/falcon.hpp"

int main()
try
{
    FalconEditor editor;
    editor.initialize();
    editor.run();
}
catch (std::runtime_error const &err)
{
    std::cout << "Runtime error: " << err.what() << "\n";
}


