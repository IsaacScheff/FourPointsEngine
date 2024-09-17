#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL_image.h>

// Function to create a grid
Grid *Grid_Create(int width, int height, SDL_Renderer *renderer, const char *tilePath) {
    Grid *grid = (Grid *)malloc(sizeof(Grid));
    grid->width = width;
    grid->height = height;

    // Allocate memory for the grid cells
    grid->cells = (GridCell **)malloc(height * sizeof(GridCell *));
    for (int i = 0; i < height; i++) {
        grid->cells[i] = (GridCell *)malloc(width * sizeof(GridCell));
    }

    // Load the tile texture
    SDL_Surface *tileSurface = IMG_Load(tilePath);
    if (!tileSurface) {
        printf("Failed to load tile image %s! SDL_image Error: %s\n", tilePath, IMG_GetError());
        free(grid);
        return NULL;
    }
    SDL_Texture *tileTexture = SDL_CreateTextureFromSurface(renderer, tileSurface);
    SDL_FreeSurface(tileSurface);
    if (!tileTexture) {
        printf("Failed to create tile texture! SDL_Error: %s\n", SDL_GetError());
        free(grid);
        return NULL;
    }

    // Initialize each grid cell with the tile texture and its position
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid->cells[y][x].x = x;
            grid->cells[y][x].y = y;
            grid->cells[y][x].texture = tileTexture;
        }
    }

    return grid;
}

// Function to render the grid
void Grid_Render(Grid *grid, SDL_Renderer *renderer) {
    int tileWidth, tileHeight;

    // Assuming all grid cells share the same texture
    if (grid->width > 0 && grid->height > 0) {
        SDL_QueryTexture(grid->cells[0][0].texture, NULL, NULL, &tileWidth, &tileHeight);
    } else {
        // If the grid is empty or improperly initialized, return early
        return;
    }

    // Render each tile based on its grid position
    for (int y = 0; y < grid->height; y++) {
        for (int x = 0; x < grid->width; x++) {
            GridCell *cell = &grid->cells[y][x];

            // Calculate screen position with a 2:1 ratio for isometric view but using real dimensions
            int screenX = (x - y) * (tileWidth / 2);
            int screenY = (x + y) * (tileHeight / 4); // Adjust this factor to tweak the isometric look

            // Render the tile without altering its proportions
            SDL_Rect destRect = { screenX + 400, screenY + 100, tileWidth, tileHeight };  // Offset for centering
            SDL_RenderCopy(renderer, cell->texture, NULL, &destRect);
        }
    }
}

void Grid_Destroy(Grid *grid) {
    if (grid) {
        // Free the texture (only once, as all cells share the same texture)
        if (grid->width > 0 && grid->height > 0 && grid->cells[0][0].texture) {
            SDL_DestroyTexture(grid->cells[0][0].texture);
            grid->cells[0][0].texture = NULL; // Set to NULL to avoid accidental reuse
        }

        // Free grid cells
        for (int i = 0; i < grid->height; i++) {
            free(grid->cells[i]);
        }
        free(grid->cells);

        // Free the grid structure itself
        free(grid);
    }
}