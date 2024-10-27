// renderer.h
#ifndef RENDERER_H
#define RENDERER_H

#include <windows.h>
#include "utility.h"
#include "platform_common.h"

extern float render_scale;

struct Render_State {
    int height, width;
    void* memory;

    BITMAPINFO bitmap_info;
};

extern Render_State render_state;

// Function declarations
void clear_screen(u32 color);
void draw_rectangle_pixels(int left_bottom_X, int left_bottom_Y, int right_top_X, int right_top_Y, u32 color);
void draw_rectangle(float x, float y, float half_size_x, float half_size_y, u32 color);

#endif // RENDERER_H
