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
    SDL_Texture *texture;  // Add texture to GameObject for rendering
} GameObject;

bool Engine_Init(Engine *engine, const char *title, int width, int height);
void Engine_HandleEvents(Engine *engine);
void Engine_Update(Engine *engine);
void Engine_Render(Engine *engine, GameObject *object);
void Engine_Clean(Engine *engine);

bool GameObject_Init(GameObject *object, Engine *engine, const char *imagePath, float x, float y);
void GameObject_Render(GameObject *object, SDL_Renderer *renderer);

#endif // ENGINE_H