#include "engine.h"
#include "grid.h"

int main(int argc, char *argv[]) {
    Engine engine;

    if (!Engine_Init(&engine, "Isometric Grid Test", 1024, 768)) {
        return -1;
    }

    // Create a 5x5 grid using TheCube.png as the tile
    Grid *grid = Grid_Create(15, 5, engine.renderer, "assets/TheCube.png");
    if (!grid) {
        Engine_Clean(&engine);
        return -1;
    }

    while (engine.isRunning) {
        Engine_HandleEvents(&engine);
        
        // Stop further processing if the engine is no longer running
        if (!engine.isRunning) {
            break;
        }
        
        Engine_Update(&engine);
        
        // Render the grid
        SDL_SetRenderDrawColor(engine.renderer, 0, 0, 0, 255);
        SDL_RenderClear(engine.renderer);
        Grid_Render(grid, engine.renderer);
        SDL_RenderPresent(engine.renderer);
    }

    Grid_Destroy(grid);
    Engine_Clean(&engine);

    return 0;
}