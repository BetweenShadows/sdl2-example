#ifndef __CELL_HPP__
#define __CELL_HPP__

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

enum class CellStatus {
    ALIVE,
    DEAD
};

class Cell {
public:
    Cell(int x, int y, int size, const CellStatus& status);
    void Revive();
    void Kill();
    bool IsAlive();
    bool IsDead();
    int GetX() const;
    int GetY() const;
    void Render(SDL_Renderer* renderer);
private:
    SDL_Color GetColor();

    int x_;
    int y_;
    int size_;
    SDL_Rect rect_;
    CellStatus status_;
};

#endif // !__CELL_HPP__