#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

#define TITLE              "Counter"
#define BACKGROUND_COLOR   ORANGE
#define SCREEN_WIDTH       500
#define SCREEN_HEIGHT      200
#define CENTER_Y           (SCREEN_HEIGHT >> 1)
#define MAX_COUNT          100
#define TEXT_BUFFER_CAP    10
#define COUNTER_FONT_COLOR BLACK
#define COUNTER_FONT_SIZE  200
#define HELP_FONT_COLOR    BLACK
#define HELP_FONT_SIZE     20

size_t count = 0;
size_t cycles = 0;
size_t textWidth = 0;
char textBuffer[TEXT_BUFFER_CAP];
bool show_help = true;

static inline void Update(void) {
    if (IsKeyPressed(KEY_UP)) {
        show_help = false;
        if (count == MAX_COUNT - 1) {
            cycles += 1;
        }
        count = (count + 1) % MAX_COUNT;
    }
    else if (IsKeyPressed(KEY_DOWN)) {
        show_help = false;
        count = count == 0 ? 0 : count - 1;
    }
    else if (IsKeyPressed(KEY_H)) {
        show_help = true;
    }
}

static inline void draw_text_center(const char* text, int posy, size_t font_size, Color font_color) {
    int posx = (SCREEN_WIDTH - MeasureText(text, font_size)) >> 1;
    DrawText(text, posx, posy, font_size, font_color);
}

static inline void Draw(void) {
    if (show_help) {
        draw_text_center("Press UP to count up."                    , CENTER_Y + (HELP_FONT_SIZE * -1), HELP_FONT_SIZE, HELP_FONT_COLOR);
        draw_text_center("Press DOWN to count down."                , CENTER_Y + (HELP_FONT_SIZE *  0), HELP_FONT_SIZE, HELP_FONT_COLOR);
        draw_text_center("Press h for help."                        , CENTER_Y + (HELP_FONT_SIZE * +1), HELP_FONT_SIZE, HELP_FONT_COLOR);
        draw_text_center("Note: The count goes till 99, then repeat", CENTER_Y + (HELP_FONT_SIZE * +2), HELP_FONT_SIZE, HELP_FONT_COLOR);
    }
    else {
        sprintf(textBuffer, "%zu", count);
        textWidth =  MeasureText(textBuffer, COUNTER_FONT_SIZE);
        DrawText(textBuffer, (SCREEN_WIDTH - textWidth) >> 1, 0, COUNTER_FONT_SIZE, COUNTER_FONT_COLOR);
    }
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
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

