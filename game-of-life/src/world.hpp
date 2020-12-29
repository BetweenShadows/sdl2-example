#ifndef __WORLD_HPP__
#define __WORLD_HPP__

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "cell.hpp"
#include "util.hpp"

struct Generation
{
    int number;
    std::vector<std::vector<Cell>> population;
};

class World
{

public:
    World(int w, int h, int cell_size);
    ~World();
    void Render(SDL_Renderer *renderer);
    void Update();
    int GetCurrentGeneration() const;
    int GetTotalGenerations() const;

private:
    std::vector<Cell> GetNeighbours(const Cell &cell);
    int AmountAliveNeighbours(const Cell &cell);
    Generation *NextGeneration();
    void SwapGeneration(int to);

private:
    std::vector<Generation *> generations_;
    Generation *currentGeneration_;
    size_t genPointer_;
    int width_;
    int height_;
    int cellSize_;
};

#endif // __WORLD_HPP__