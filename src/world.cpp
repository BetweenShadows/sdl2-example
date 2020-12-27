#include "world.hpp"

const int ALLOW_SPAWN = 1;

World::World(int w, int h, int cell_size) {
    width_ = w;
    height_ = h;
    cellSize_ = cell_size;
    for(int i = 0; i < width_; i++) {
        std::vector<Cell*> row;
        for(int j = 0; j < height_; j++) {
            Cell* cell = new Cell(i, j, cell_size, CellStatus::DEAD);
            int p = RandInt(0, 2);
            if(p == ALLOW_SPAWN) {
                cell->Revive();
            }
            row.emplace_back(cell);
        }
        cells_.emplace_back(row);
    }
}

World::~World() {
    for(auto& v : cells_) {
        for(auto& c : v) {
            delete c;
        }
    }
}

void World::Render(SDL_Renderer* renderer) {
    for(const auto& v : cells_) {
        for(const auto& c : v) {
            c->Render(renderer);
        }
    }
}

void World::Update() {
    // Get keyboard keys state
    auto keys = SDL_GetKeyboardState(NULL);
    SDL_PumpEvents();
    if(keys[SDL_SCANCODE_RETURN]) {
        NextGeneration();
        SDL_Delay(100);
    }
}

std::vector<Cell*> World::GetNeighbours(Cell* cell) {
    std::vector<Cell*> neighbours;
    for(int dx = -1; dx < 3; dx++) {
        for(int dy = -1; dy < 3; dy++) {
            bool valid = true;
            int x = cell->GetX() + dx;
            int y = cell->GetY() + dy;
            if(x < 0 || x >= width_) valid = false;
            if(y < 0 || y >= height_) valid = false;
            if(valid) {
                neighbours.emplace_back(cells_[x][y]);
            }
        }
    }
    return neighbours;
}

int World::AmountAliveNeighbours(Cell* cell) {
    int amount = 0;
    auto neighbours = GetNeighbours(cell);
    for(auto& n : neighbours) {
        if(n->IsAlive()) {
            ++amount;
        }
    }
    return amount;
}

void World::NextGeneration()  {
    for(auto& v : cells_) {
        for(auto& c : v) {
            int alive_neighbours = AmountAliveNeighbours(c);
            if(c->IsDead()) {
                if(alive_neighbours == 3) {
                    c->Revive();
                }
            }

            if(c->IsAlive()) {
                if(alive_neighbours < 2 || alive_neighbours > 3) {
                    c->Kill();
                }
            }
        }
    }
}