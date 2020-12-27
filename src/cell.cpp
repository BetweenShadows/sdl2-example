#include "cell.hpp"

Cell::Cell(int x, int y, int size, const CellStatus& status) {
    x_ = x;
    y_ = y;
    rect_.h = size;
    rect_.w = size;
    rect_.x = x * size;
    rect_.y = y * size;
    status_ = status;
    this->size_ = size;
}

void Cell::Revive() {
    status_ = CellStatus::ALIVE;
}

void Cell::Kill() {
    status_ = CellStatus::DEAD;
}

bool Cell::IsAlive() {
    return status_ == CellStatus::ALIVE;
}

bool Cell::IsDead() {
    return status_ == CellStatus::DEAD;
}

int Cell::GetX() const {
    return x_;
}

int Cell::GetY() const {
    return y_;
}

SDL_Color Cell::GetColor() {
    SDL_Color color;
    switch (status_)
    {
        case CellStatus::ALIVE:
            color = SDL_Color{.r = 0, .g = 0, .b = 0, .a = 255};
            break;

        case CellStatus::DEAD:
            color = SDL_Color{.r = 255, .g = 255, .b = 255, .a = 1};
            break;

        default:
            color = SDL_Color{.r = 100, .g = 100, .b = 100, .a = 255};
            break;
    }

    return color;
}

void Cell::Render(SDL_Renderer* renderer) {
    SDL_Color color = GetColor();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect_);
}