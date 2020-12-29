#include "world.hpp"

const int ALLOW_SPAWN = 1;

World::World(int w, int h, int cell_size)
{
    width_ = w;
    height_ = h;
    cellSize_ = cell_size;
    Generation *first_generation = new Generation();
    first_generation->number = 1;
    for (int i = 0; i < width_; i++)
    {
        std::vector<Cell> row;
        for (int j = 0; j < height_; j++)
        {
            Cell cell(i, j, cell_size, CellStatus::DEAD);
            int p = RandInt(0, 2);
            if (p == ALLOW_SPAWN)
            {
                cell.Revive();
            }
            row.emplace_back(cell);
        }
        first_generation->population.emplace_back(row);
    }
    generations_.emplace_back(first_generation);
    currentGeneration_ = generations_.front();
    genPointer_ = 1;
}

World::~World()
{
    for (auto &g : generations_)
    {
        delete g;
    }
}

void World::Render(SDL_Renderer *renderer)
{
    for (auto &v : currentGeneration_->population)
    {
        for (auto &c : v)
        {
            c.Render(renderer);
        }
    }
}

void World::Update()
{
    // Get keyboard keys state
    auto keys = SDL_GetKeyboardState(NULL);
    SDL_PumpEvents();

    // When pressing left key, go back to past generations
    if (keys[SDL_SCANCODE_LEFT])
    {
        // Edge case: don't allow pointer to be less than 1 if the user hits LEFT
        if (genPointer_ > 1)
        {
            genPointer_--;
        }

        else
        {
            genPointer_ = 1;
        }

        SwapGeneration(genPointer_);
        SDL_Delay(200);
    }

    // When pressing right key, advance to the next generations
    if (keys[SDL_SCANCODE_RIGHT])
    {
        genPointer_++;
        if (genPointer_ > generations_.size())
        {
            auto next_gen = NextGeneration();
            generations_.emplace_back(next_gen);
        }
        SwapGeneration(genPointer_);
        SDL_Delay(200);
    }
}

int World::GetCurrentGeneration() const
{
    return currentGeneration_->number;
}

int World::GetTotalGenerations() const
{
    return generations_.size();
}

std::vector<Cell> World::GetNeighbours(const Cell &cell)
{
    std::vector<Cell> neighbours;
    for (int dx = -1; dx < 3; dx++)
    {
        for (int dy = -1; dy < 3; dy++)
        {
            bool valid = true;
            int x = cell.GetX() + dx;
            int y = cell.GetY() + dy;
            if (x < 0 || x >= width_)
                valid = false;
            if (y < 0 || y >= height_)
                valid = false;
            if (valid)
            {
                neighbours.emplace_back(currentGeneration_->population[x][y]);
            }
        }
    }
    return neighbours;
}

int World::AmountAliveNeighbours(const Cell &cell)
{
    int amount = 0;
    auto neighbours = GetNeighbours(cell);
    for (auto &n : neighbours)
    {
        if (n.IsAlive())
        {
            ++amount;
        }
    }
    return amount;
}

Generation *World::NextGeneration()
{
    Generation *next_gen = new Generation();
    next_gen->population = currentGeneration_->population;
    next_gen->number = currentGeneration_->number + 1;
    for (auto &v : next_gen->population)
    {
        for (auto &c : v)
        {
            int alive_neighbours = AmountAliveNeighbours(c);
            if (c.IsDead())
            {
                if (alive_neighbours == 3)
                {
                    c.Revive();
                }
            }

            if (c.IsAlive())
            {
                if (alive_neighbours < 2 || alive_neighbours > 3)
                {
                    c.Kill();
                }
            }
        }
    }
    return next_gen;
}

void World::SwapGeneration(int to)
{
    currentGeneration_ = generations_[to - 1];
}