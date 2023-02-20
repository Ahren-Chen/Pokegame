global_variable u32* pixel;
global_variable float render_scale = 0.01f;

internal void clear_screen(u32 color) {
    pixel = (u32*)render_state.memory;

    for (int y = 0; y < render_state.height; y++) {
        for (int x = 0; x < render_state.width; x++) {
            *pixel++ = color;
        }
    }
}

internal void draw_rectangle_pixels(int left_bottom_X, int left_bottom_Y, int right_top_X, int right_top_Y, u32 color) {

    left_bottom_X = clamp(0, left_bottom_X, render_state.width);
    right_top_X = clamp(0, right_top_X, render_state.width);
    left_bottom_Y = clamp(0, left_bottom_Y, render_state.height);
    right_top_Y = clamp(0, right_top_Y, render_state.height);


    for (int y = left_bottom_Y ; y < right_top_Y; y++) {
        pixel = (u32*)render_state.memory + left_bottom_X + y * render_state.width;

        for (int x = left_bottom_X; x < right_top_X; x++) {
            if (left_bottom_X <= x && x <= right_top_X && left_bottom_Y <= y && y <= right_top_Y) {
                *pixel = color;
            }
            pixel++;
        }
    }
}

internal void draw_rectangle(float x, float y, float half_size_x, float half_size_y, u32 color) {
    // Change to percentages of the height, enter from 0-1
    x *= render_state.height * render_scale;
    y *= render_state.height * render_scale;
    half_size_x *= render_state.height * render_scale;
    half_size_y *= render_state.height * render_scale;

    //Centering the rectangle
    x += render_state.width / 2.f;
    y += render_state.height / 2.f;

    s32 left_bottom_X = x - half_size_x;
    s32 left_bottom_Y = y - half_size_y;
    s32 right_top_X = x + half_size_x;
    s32 right_top_Y = y + half_size_y;

    draw_rectangle_pixels(left_bottom_X, left_bottom_Y, right_top_X, right_top_Y, color);
}