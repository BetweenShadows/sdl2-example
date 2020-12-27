# SDL2 Example

# About 
This is a preview to show and learn basics of SDL2 in C++. For that, the game of life 
was implemented since it's an easy program to make.

# Getting Started 
To compile the project, you can use the build script. It's very basic and it only contains
the following commands:

```sh
g++ -Wall -Wextra src/*.cpp src/*.hpp -o life -lSDL2
mkdir -p build
mv life build/life
```
To run the script, just execute the executable generated in the build folder, or you can run the run script.

After starting the program, if you want to generate a next generation of cells, you press the RETURN button on your keyboard. 