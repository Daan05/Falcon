#include "falcon.ih"

void FalconEditor::setPath(char const *str)
{
    conf.workingDirectory = str;

    // if its a directory:
    //      do nothing for now
    // if its a file:
    //      set the directory to str minus the file name
    //      openFile()
    openFile(str);
}
