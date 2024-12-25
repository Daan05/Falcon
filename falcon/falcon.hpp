#ifndef FALCON_EDITOR_HPP
#define FALCON_EDITOR_HPP

#include <cstddef>
#include <ncurses.h>
#include <vector>
#include <filesystem>

struct FalconConfig
{
    std::filesystem::path workingDirectory;

    size_t term_rows;
    size_t term_cols;

    size_t cur_row;
    size_t cur_col;

    size_t file_rows;
};

class FalconEditor
{
private:
    bool quit = false;
    FalconConfig conf;
    WINDOW *lineNumWin;
    WINDOW *textBufWin;

    std::vector<std::string> lines;

public:
    FalconEditor();
    ~FalconEditor();

    void setPath(char const *str);

    void initialize();
    void openFile(std::string filename);
    void run();

private:
    int readKey();
    void processKeypress(int ch);

    void drawLines();
};

#endif
