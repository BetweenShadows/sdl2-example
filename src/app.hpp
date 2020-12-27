#ifndef __APP_HPP__
#define __APP_HPP__

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include "world.hpp"

class App
{
public:
    App();
    ~App();
    void Run();

private:
    bool Init();
    void HandleEvents();
    void Update();
    void Render();

    bool isRunning_ = false;
    SDL_Event event;
    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;

    World *world = nullptr;
};

#endif // !__APP_HPP__