#ifndef GRID_H
#define GRID_H

#include <SDL.h>

typedef struct {
    int x;  // Grid position x
    int y;  // Grid position y
    SDL_Texture *texture;  // Pointer to the tile texture
} GridCell;

typedef struct {
    int width;  // Number of columns
    int height; // Number of rows
    GridCell **cells;  // 2D array of GridCells
} Grid;

// Function declarations
Grid *Grid_Create(int width, int height, SDL_Renderer *renderer, const char *tilePath);
void Grid_Render(Grid *grid, SDL_Renderer *renderer);
void Grid_Destroy(Grid *grid);

#endif // GRID_H