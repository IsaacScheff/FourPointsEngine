#include "engine.h"

int main(int argc, char *argv[]) {
    Engine engine;

    if (!Engine_Init(&engine, "My Game Engine", 1024, 768)) {
        return -1;
    }

    GameObject cube;
    if (!GameObject_Init(&cube, &engine, "assets/TheCube.png", 100.0f, 100.0f)) {
        Engine_Clean(&engine);
        return -1;
    }

    while (engine.isRunning) {
        Engine_HandleEvents(&engine);
        Engine_Update(&engine);
        Engine_Render(&engine, &cube);
    }

    Engine_Clean(&engine);
    return 0;
}