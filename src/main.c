#include "engine.h"

int main(int argc, char *argv[]) {
    Engine engine;

    if (!Engine_Init(&engine, "My Game Engine", 800, 600)) {
        return -1;
    }

    SDL_Color red = {255, 0, 0, 255};
    GameObject player;
    GameObject_Init(&player, 100.0f, 100.0f, 50, 50, red);  // Initialize the player with float coordinates

    while (engine.isRunning) {
        Engine_HandleEvents(&engine);
        Engine_Update(&engine, &player);
        Engine_Render(&engine, &player);
    }

    Engine_Clean(&engine);

    return 0;
}