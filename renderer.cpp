#include "utility.cpp"

unsigned int* pixel;

void render_background() {
    pixel = (unsigned int*)render_state.memory;

    for (int y = 0; y < render_state.height; y++) {
        for (int x = 0; x < render_state.width; x++) {
            *pixel++ = 0xff5500 * x;
        }
    }
}

void clear_screen(unsigned int color) {
    pixel = (unsigned int*)render_state.memory;

    for (int y = 0; y < render_state.height; y++) {
        for (int x = 0; x < render_state.width; x++) {
            *pixel++ = color;
        }
    }
}

void draw_rectangle(int left_bottom_X, int left_bottom_Y, int right_top_X, int right_top_Y, unsigned int color) {

    left_bottom_X = clamp(0, left_bottom_X, render_state.width);
    right_top_X = clamp(0, right_top_X, render_state.width);
    left_bottom_Y = clamp(0, left_bottom_Y, render_state.height);
    right_top_Y = clamp(0, right_top_Y, render_state.height);


    for (int y = left_bottom_Y ; y < right_top_Y; y++) {
        pixel = (unsigned int*)render_state.memory + left_bottom_X + y * render_state.width;

        for (int x = left_bottom_X; x < right_top_X; x++) {
            if (left_bottom_X <= x && x <= right_top_X && left_bottom_Y <= y && y <= right_top_Y) {
                *pixel = color;
            }
            pixel++;
        }
    }
}