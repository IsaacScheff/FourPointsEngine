#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <stdbool.h>

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool isRunning;
    Uint32 lastFrameTime;
} Engine;

typedef struct {
    float x, y;  // Positions are floats for smooth movement
    int width, height;
    SDL_Color color;
} GameObject;

bool Engine_Init(Engine *engine, const char *title, int width, int height);
void Engine_HandleEvents(Engine *engine);
void Engine_Update(Engine *engine, GameObject *player);
void Engine_Render(Engine *engine, GameObject *player);
void Engine_Clean(Engine *engine);

void GameObject_Init(GameObject *object, float x, float y, int width, int height, SDL_Color color);
void GameObject_Render(GameObject *object, SDL_Renderer *renderer);

#endif // ENGINE_H