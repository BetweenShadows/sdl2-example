# Compile with g++
g++ -Wall -Wextra src/*.cpp src/*.hpp -o life -lSDL2

# Debug gdb
# g++ -g -Wall -Wextra src/main.cpp src/app.hpp src/app.cpp src/world.hpp src/world.cpp src/cell.hpp src/cell.cpp src/util.hpp src/util.cpp -o life_debug -lSDL2

# Make build folder with executable
mkdir -p build
mv life build/life

# Make debug folder with executable 
# mkdir -p debug
# mv life_debug debug/life_debug