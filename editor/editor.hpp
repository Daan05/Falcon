#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <cstddef>
#include <ncurses.h>
#include <string>
#include <vector>

class Editor
{
private:
    bool quit = false;

    size_t termRows;
    size_t termCols;

    size_t scrollOff;
    size_t cursorRow;
    size_t cursorCol;
    size_t currentRow;
    size_t fileRows;

    WINDOW *lineNumWin;
    WINDOW *textBufWin;

    std::vector<std::string> lines;
    std::string filename;

public:
    Editor();
    ~Editor();

    void initialize();
    void resizeTerminal();
    void openFile(const char *filename);
    void saveFile();
    void run();

private:
    int readKey();
    void processKeypress(int ch);

    void drawLines();
    void drawLineNumbers();

    void moveCursorUp();
    void moveCursorDown();
    void deleteCharBack();
};

constexpr inline int controlKey(int ch) { return ((ch) & 0x1f); }

#endif
