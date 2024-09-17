#include "engine.h"
#include <stdio.h>

bool Engine_Init(Engine *engine, const char *title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    engine->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!engine->window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    engine->renderer = SDL_CreateRenderer(engine->window, -1, SDL_RENDERER_ACCELERATED);
    if (!engine->renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(engine->window);
        SDL_Quit();
        return false;
    }

    engine->isRunning = true;
    engine->lastFrameTime = SDL_GetTicks();  // Initialize last frame time
    return true;
}

void Engine_HandleEvents(Engine *engine) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            engine->isRunning = false;
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                engine->isRunning = false;
            }
        }
    }
}

void Engine_Update(Engine *engine, GameObject *player) {
    Uint32 currentFrameTime = SDL_GetTicks();
    float deltaTime = (currentFrameTime - engine->lastFrameTime) / 1000.0f;  // Time since last frame in seconds
    engine->lastFrameTime = currentFrameTime;

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    float speed = 100.0f;  // Pixels per second
    if (state[SDL_SCANCODE_UP]) {
        player->y -= speed * deltaTime;
    }
    if (state[SDL_SCANCODE_DOWN]) {
        player->y += speed * deltaTime;
    }
    if (state[SDL_SCANCODE_LEFT]) {
        player->x -= speed * deltaTime;
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        player->x += speed * deltaTime;
    }
}

void Engine_Render(Engine *engine, GameObject *player) {
    SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 255);
    SDL_RenderClear(engine->renderer);

    GameObject_Render(player, engine->renderer);

    SDL_RenderPresent(engine->renderer);
}

void Engine_Clean(Engine *engine) {
    SDL_DestroyRenderer(engine->renderer);
    SDL_DestroyWindow(engine->window);
    SDL_Quit();
}

void GameObject_Init(GameObject *object, float x, float y, int width, int height, SDL_Color color) {
    object->x = x;
    object->y = y;
    object->width = width;
    object->height = height;
    object->color = color;
}

void GameObject_Render(GameObject *object, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, object->color.r, object->color.g, object->color.b, object->color.a);
    SDL_Rect rect = { (int)object->x, (int)object->y, object->width, object->height };
    SDL_RenderFillRect(renderer, &rect);
}