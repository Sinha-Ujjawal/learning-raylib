#include <stdlib.h>
#include <raylib.h>

#define TITLE            "The Psychophysicists Electrode!"
#define BACKGROUND_COLOR BLACK
#define RING_COLOR       WHITE
#define SCREEN_WIDTH     800
#define SCREEN_HEIGHT    600
#define CENTER_X         (SCREEN_WIDTH >> 1)
#define CENTER_Y         (SCREEN_HEIGHT >> 1)
#define FONT_SIZE        30
#define TEXT_COLOR       WHITE
#define DELTA            1
#define THICKNESS        7
#define MAX_RINGS        40
#define SPACINGS         20

size_t delta = 0;
const Vector2 center = {CENTER_X, CENTER_Y};
bool show_help = true;
bool pause = true;

static inline void Update(void) {
    if (!pause) {
        delta = (delta + DELTA) % SPACINGS;
    }
    if (IsKeyPressed(KEY_SPACE)) {
        pause = !pause;
        show_help = false;
    }
    else if (IsKeyPressed(KEY_H)) {
        show_help = !show_help;
    }
}

static inline void draw_text_center(const char* text, int posy, size_t font_size, Color font_color) {
    int posx = (SCREEN_WIDTH - MeasureText(text, font_size)) >> 1;
    DrawText(text, posx, posy, font_size, font_color);
}

static inline void draw_help(void) {
    draw_text_center("Press <SPACE> to play/pause.", CENTER_Y + (FONT_SIZE *  0), FONT_SIZE, TEXT_COLOR);
    draw_text_center("Press 'h' to show/hide help.", CENTER_Y + (FONT_SIZE * +1), FONT_SIZE, TEXT_COLOR);
}

static inline void draw_rings(void) {
    for (int r = MAX_RINGS - 1; r >= 0; r--) {
        size_t innerRadius = r * SPACINGS + delta;
        DrawRing(center, innerRadius, innerRadius + THICKNESS, 0, 360, 1, RING_COLOR);
    }
}

static inline void Draw(void) {
    if (show_help) {
        draw_help();
    } else {
        draw_rings();
    }
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(90);
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

