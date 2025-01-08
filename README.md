<H1>FALCON TEXT EDITOR</H1>
Falcon is somwhat decent now, and... 
proudly written in C++.

<H2>FEATURES</H2>

- open/save files
- scroll off
- remove/add charcters
- remove/add lines
- file navigation with arrow keys, <C-d> <C-u> and scroll wheel

<H2>HOW TO RUN</H2>
Dependencies:

- C++ compiler (I recommend gcc)
- ncurses library
- cmake (3.31 or newer)
- ninja or gnu make

Personally i use ninja, because it compiles the project generally faster.

NOTE:
- using ninja the executable will be generated in the project folder
- whereas the gnu make alternative generates the executable inside the build directory

<H3>USING NINJA</H3>

You can compile the project by running `cmake -GNinja && ninja`

After you have run `cmake -GNinja` once, you can just run `ninja` going forward

<H3>USING GNU MAKE</H3>

You can compile the project by running `cmake -B build && cmake --build build`

After you have run `cmake -B build` once, you can just run `cmake --build build` going forward
