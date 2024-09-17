#include "engine.h"
#include <SDL_image.h>
#include <stdio.h>

bool Engine_Init(Engine *engine, const char *title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        SDL_Quit();
        return false;
    }

    engine->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!engine->window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    engine->renderer = SDL_CreateRenderer(engine->window, -1, SDL_RENDERER_ACCELERATED);
    if (!engine->renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(engine->window);
        IMG_Quit();
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
        }
    }
}

void Engine_Update(Engine *engine) {
    // Placeholder for future update logic
}

void Engine_Render(Engine *engine, GameObject *object) {
    SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 255);
    SDL_RenderClear(engine->renderer);

    // Render the object
    GameObject_Render(object, engine->renderer);

    SDL_RenderPresent(engine->renderer);
}

void Engine_Clean(Engine *engine) {
    SDL_DestroyRenderer(engine->renderer);
    SDL_DestroyWindow(engine->window);
    IMG_Quit();
    SDL_Quit();
}

bool GameObject_Init(GameObject *object, Engine *engine, const char *imagePath, float x, float y) {
    SDL_Surface *surface = IMG_Load(imagePath);
    if (!surface) {
        printf("Unable to load image %s! SDL_image Error: %s\n", imagePath, IMG_GetError());
        return false;
    }

    object->texture = SDL_CreateTextureFromSurface(engine->renderer, surface);
    SDL_FreeSurface(surface);

    if (!object->texture) {
        printf("Unable to create texture from %s! SDL_Error: %s\n", imagePath, SDL_GetError());
        return false;
    }

    SDL_QueryTexture(object->texture, NULL, NULL, &object->width, &object->height);
    object->x = x;
    object->y = y;
    return true;
}

void GameObject_Render(GameObject *object, SDL_Renderer *renderer) {
    SDL_Rect destRect = { (int)object->x, (int)object->y, object->width, object->height };
    SDL_RenderCopy(renderer, object->texture, NULL, &destRect);
}