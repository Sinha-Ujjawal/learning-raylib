#include <stdlib.h>
#include <stdbool.h>
#include <raylib.h>
#include <time.h>

#define TITLE            "Game Of Life"
#define BACKGROUND_COLOR WHITE
#define SCREEN_WIDTH     800
#define SCREEN_HEIGHT    600
#define CENTER_Y         (SCREEN_HEIGHT >> 1)
#define CELL_COLOR       BLACK
#define CELL_WIDTH       5
#define CELL_HEIGHT      5
#define GRID_COLS        (SCREEN_WIDTH / CELL_WIDTH)
#define GRID_ROWS        (SCREEN_HEIGHT / CELL_HEIGHT)
#define FONT_SIZE        25
#define TEXT_COLOR       RED
#define PROB_SPAWN       0.1

#define wrap_incr(x, n) ((x) + 1) % (n)
#define wrap_decr(x, n) (x) == 0 ? (n) - 1 : (x) - 1

#define to_cell_idx(row, col) (row) * GRID_COLS + (col)

#define top(row, col)          to_cell_idx( wrap_decr(row, GRID_ROWS), col                       )
#define bottom(row, col)       to_cell_idx( wrap_incr(row, GRID_ROWS), col                       )
#define left(row, col)         to_cell_idx( row                      , wrap_decr(col, GRID_COLS) )
#define right(row, col)        to_cell_idx( row                      , wrap_incr(col, GRID_COLS) )
#define top_left(row, col)     to_cell_idx( wrap_decr(row, GRID_ROWS), wrap_decr(col, GRID_COLS) )
#define bottom_left(row, col)  to_cell_idx( wrap_incr(row, GRID_ROWS), wrap_decr(col, GRID_COLS) )
#define top_right(row, col)    to_cell_idx( wrap_decr(row, GRID_ROWS), wrap_incr(col, GRID_COLS) )
#define bottom_right(row, col) to_cell_idx( wrap_incr(row, GRID_ROWS), wrap_incr(col, GRID_COLS) )

bool grid[GRID_ROWS * GRID_COLS] = {0};
bool temp[GRID_ROWS * GRID_COLS] = {0};
bool show_help = true;
bool pause = true;

static inline void randomize_grid() {
    for (size_t row = 0; row < GRID_ROWS; ++row) {
        for (size_t col = 0; col < GRID_COLS; ++col) {
            float r = rand() * 1.0 / RAND_MAX;
            grid[to_cell_idx(row, col)] = r <= PROB_SPAWN;
        }
    }
}

static inline size_t count_alive_neighbors(size_t row, size_t col) {
    return (
            grid[top(row, col)]
            + grid[bottom(row, col)]
            + grid[left(row, col)]
            + grid[right(row, col)]
            + grid[top_left(row, col)]
            + grid[bottom_left(row, col)]
            + grid[top_right(row, col)]
            + grid[bottom_right(row, col)]
           );
}

static inline bool is_alive(size_t row, size_t col) {
    size_t cnt_alive_neighbors = count_alive_neighbors(row, col);
    if (grid[to_cell_idx(row, col)]) {
        return cnt_alive_neighbors == 2 || cnt_alive_neighbors == 3;
    }
    return cnt_alive_neighbors == 3;
}

static inline void evolve_grid(void) {
    for (size_t row = 0; row < GRID_ROWS; ++row) {
        for (size_t col = 0; col < GRID_COLS; ++col) {
            temp[to_cell_idx(row, col)] = is_alive(row, col);
        }
    }
    for (size_t row = 0; row < GRID_ROWS; ++row) {
        for (size_t col = 0; col < GRID_COLS; ++col) {
            grid[to_cell_idx(row, col)] = temp[to_cell_idx(row, col)];
        }
    }
}

static inline void Update(void) {
    if (!pause) {
        evolve_grid();
    }

    if (IsKeyPressed(KEY_SPACE)) {
        pause = !pause;
        show_help = false;
    }
    else if (IsKeyPressed(KEY_H)) {
        show_help = !show_help;
    }
    else if (IsKeyPressed(KEY_R)) {
        show_help = false;
        randomize_grid();
    }
}

static inline void draw_text_center(const char* text, int posy, size_t font_size, Color font_color) {
    int posx = (SCREEN_WIDTH - MeasureText(text, font_size)) >> 1;
    DrawText(text, posx, posy, font_size, font_color);
}

static inline void draw_help(void) {
    draw_text_center("Press <SPACE> to play/pause.", CENTER_Y + (FONT_SIZE * -1), FONT_SIZE, TEXT_COLOR);
    draw_text_center("Press 'r' to reset."         , CENTER_Y + (FONT_SIZE *  0), FONT_SIZE, TEXT_COLOR);
    draw_text_center("Press 'h' to show/hide help.", CENTER_Y + (FONT_SIZE * +1), FONT_SIZE, TEXT_COLOR);
}

static inline void draw_cell(size_t row, size_t col) {
    if (grid[to_cell_idx(row, col)]) {
        DrawRectangle(col*CELL_WIDTH, row*CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, CELL_COLOR);
    }
}

static inline void draw_cells(void) {
    for (size_t row = 0; row < GRID_ROWS; ++row) {
        for (size_t col = 0; col < GRID_COLS; ++col) {
            draw_cell(row, col);
        }
    }
}

static inline void Draw(void) {
    if (show_help) {
        draw_help();
    }
    else {
        draw_cells();
    }
}

int main(void) {
    srand(time(NULL));
    randomize_grid();
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(60);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        Update();
        Draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

