#ifndef __WORLD_HPP__
#define __WORLD_HPP__

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "cell.hpp"
#include "util.hpp"

class World
{

public:
    World(int w, int h, int cell_size);
    ~World();
    void Render(SDL_Renderer *renderer);
    void Update();

private:
    std::vector<Cell *> GetNeighbours(Cell *cell);
    int AmountAliveNeighbours(Cell *cell);
    void NextGeneration();

    std::vector<std::vector<Cell *>> cells_;
    int width_;
    int height_;
    int cellSize_;
};

#endif // __WORLD_HPP__