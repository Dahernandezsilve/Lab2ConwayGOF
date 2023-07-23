#include <SDL2/SDL.h>
#include <cstdlib> // Para la función rand()
#include <ctime> // Para la función time()

const int FRAMEBUFFER_WIDTH = 200;
const int FRAMEBUFFER_HEIGHT = 200;
const int FRAMEBUFFER_SIZE = FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

struct Color {
    uint8_t r, g, b, a;
};

Color framebuffer[FRAMEBUFFER_SIZE];
Color clearColor = {0, 0, 0, 255};
Color currentColor = {255, 255, 255, 255};

bool glider[3 * 3] = {
        0, 1, 0,
        0, 0, 1,
        1, 1, 1
};

bool block[2 * 2] = {
        1, 1,
        1, 1
};

bool flor[5 * 5] = {
        0, 0, 1, 0, 0,
        0, 1, 1, 1, 0,
        1, 1, 1, 1, 1,
        0, 1, 1, 1, 0,
        0, 0, 1, 0, 0
};
bool pulsar[13 * 13] = {
        0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1,
        0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0,
        0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0,
        0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0
};

bool blinker[1 * 3] = {
        1,
        1,
        1
};

bool spaceship[3 * 3] = {
        0, 1, 0,
        0, 0, 1,
        1, 1, 1
};

bool house[6 * 6] = {
        0, 0, 1, 1, 0, 0,
        0, 1, 0, 0, 1, 0,
        1, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 1
};

bool building[10 * 10] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 1, 0, 1, 1, 0, 0, 1,
        1, 0, 1, 1, 0, 1, 1, 0, 0, 1,
        1, 0, 1, 1, 0, 1, 1, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

void clear() {
    for (int i = 0; i < FRAMEBUFFER_SIZE; i++) {
        framebuffer[i] = clearColor;
    }
}

Color getRandomColor() {
    return {static_cast<uint8_t>(rand() % 256),
            static_cast<uint8_t>(rand() % 256),
            static_cast<uint8_t>(rand() % 256),
            255};
}

void point(int x, int y) {
    if (x >= 0 && x < FRAMEBUFFER_WIDTH && y >= 0 && y < FRAMEBUFFER_HEIGHT) {
        framebuffer[y * FRAMEBUFFER_WIDTH + x] = currentColor;
    }
}

bool getCellState(bool* grid, int x, int y, int gridWidth) {
    return grid[y * gridWidth + x];
}

void setCellState(bool* grid, int x, int y, int gridWidth, bool state) {
    grid[y * gridWidth + x] = state;
}

void updateGrid(bool* grid, int gridWidth, int gridHeight) {
    bool newGrid[gridWidth * gridHeight];
    for (int y = 0; y < gridHeight; y++) {
        for (int x = 0; x < gridWidth; x++) {
            int neighbors = 0;
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (dx == 0 && dy == 0) continue;
                    if (getCellState(grid, x + dx, y + dy, gridWidth)) neighbors++;
                }
            }

            bool currentState = getCellState(grid, x, y, gridWidth);
            bool nextState = currentState ? (neighbors == 2 || neighbors == 3) : (neighbors == 3);
            setCellState(newGrid, x, y, gridWidth, nextState);
        }
    }

    memcpy(grid, newGrid, sizeof(bool) * gridWidth * gridHeight);
}

void renderBuffer(SDL_Renderer* renderer, bool* grid, int gridWidth, int gridHeight) {
    clear();
    for (int y = 0; y < gridHeight; y++) {
        for (int x = 0; x < gridWidth; x++) {
            if (getCellState(grid, x, y, gridWidth)) point(x, y);
        }
    }

    SDL_Texture* texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ABGR8888,
            SDL_TEXTUREACCESS_STREAMING,
            FRAMEBUFFER_WIDTH,
            FRAMEBUFFER_HEIGHT
    );

    SDL_UpdateTexture(
            texture,
            nullptr,
            framebuffer,
            FRAMEBUFFER_WIDTH * sizeof(Color)
    );

    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_DestroyTexture(texture);
}

void setPattern(bool* grid, int patternWidth, int patternHeight, int x, int y, const bool* pattern) {
    for (int py = 0; py < patternHeight; py++) {
        for (int px = 0; px < patternWidth; px++) {
            setCellState(grid, x + px, y + py, FRAMEBUFFER_WIDTH, pattern[py * patternWidth + px]);
        }
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    srand(time(nullptr));

    bool grid[FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT];
    for (int i = 0; i < FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT; i++) {
        grid[i] = rand() % 2 == 0;
    }

    SDL_Window* window = SDL_CreateWindow("Conway's Game Of Life", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Add the patterns to the grid
    int patterns[][2] = {
            {150, 150},
            {100, 100},
            {200, 200},
            {180, 180},
            {10, 10},
            {50, 50},
            {300, 50},
            {100, 50},
            {80, 50}
    };

    const bool* patternData[] = {glider, glider, block, flor, pulsar, blinker, spaceship, house, building};
    const int patternWidth[] = {3, 3, 2, 5, 13, 1, 3, 6, 10};
    const int patternHeight[] = {3, 3, 2, 5, 13, 3, 3, 6, 10};
    const int numPatterns = sizeof(patterns) / sizeof(patterns[0]);

    for (int i = 0; i < numPatterns; i++) {
        setPattern(grid, patternWidth[i], patternHeight[i], patterns[i][0], patterns[i][1], patternData[i]);
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        currentColor = getRandomColor();
        updateGrid(grid, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
        renderBuffer(renderer, grid, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
