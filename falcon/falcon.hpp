#ifndef FALCON_EDITOR_HPP
#define FALCON_EDITOR_HPP

#include <cstddef>
#include <ncurses.h>
#include <vector>
#include <string>

struct FalconConfig
{
    size_t term_rows;
    size_t term_cols;

    size_t cursor_row;
    size_t cursor_col;

    size_t scrolloff;
    size_t row;
    size_t current_row;

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

    void initialize();
    void openFile(const char *filename);
    void run();

private:
    int readKey();
    void processKeypress(int ch);

    void drawLines();
    void drawLineNumbers();
};

#endif
