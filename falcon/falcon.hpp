#ifndef FALCON_EDITOR_HPP
#define FALCON_EDITOR_HPP

#include <cstddef>
#include <ncurses.h>
#include <vector>

struct FalconConfig
{
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

    std::vector<char> line = { 'h', 'e', 'l', 'l', 'o' };

public:
    FalconEditor();
    ~FalconEditor();

    void initialize();
    void openFile();
    void run();

private:
    int readKey();
    void processKeypress(int ch);

    void drawLines();
};

#endif
