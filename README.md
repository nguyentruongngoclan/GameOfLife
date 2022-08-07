# GameOfLife

## Source codes
Main file is InfiniteBoard.cpp, core libraries that contains most of the Game of life's state computation is in include/GameOfLifeState.cpp

## Build system
Use cmake as the build system

## Prebuilt executable
The build/Debug folder contains an Windows x86 executable that you can run

## Running the executable

### Inputs:

A list of live cells coordinates represents the x and y coordinates of a live cell separated by space, each in its own line. 

-9223372036854775808 < x,y < 9223372036854775807 (limits of long long). 

The program will keep reading the inputs until EOF character is hit (Ctrl-Z for Windows, Ctrl-D for Unix if using standard input) 

### Some handy flags (all optional):
  - -f: Path to input file, if not provided the program will read from standard inputs
  - -t: Number of iterations of the Game of live, default 10
  
### Outputs:
  The program will print out the state of each iterations of the Game of live (include the initial state) to standard ouput in Life #1.06 format
 
### Examples:
  ./build/Debug/GameOfLifeInfBoard.exe -f examples/test2.txt -t 20 (will print out 1 + 20 iterations of the game of live, including the starting state provided in examples/test2.txt file)
  
  
