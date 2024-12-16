// renderer.h
#ifndef RENDERER_H
#define RENDERER_H

#include <windows.h>
#include "utility.h"
#include "platform_common.h"

struct Render_State {
    int height, width;
    void* memory;

    BITMAPINFO bitmap_info;
};

// Function declarations
//void clear_screen(u32 color);
//void draw_rectangle_pixels(int left_bottom_X, int left_bottom_Y, int right_top_X, int right_top_Y, u32 color);
//void draw_rectangle(float x, float y, float half_size_x, float half_size_y, u32 color);

class Renderer {
public:
    // Delete copy constructors for safety
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    // Public methods
    static Renderer& get_instance(); // Singleton instance access

    // Initialize renderer with dimensions
    void initialize(int width, int height);

    // Clear the screen with a specific color
    void clear_screen(u32 color);

    // Draw rectangle in pixel coordinates
    void draw_rectangle_pixels(int left_bottom_X, int left_bottom_Y, int right_top_X, int right_top_Y, u32 color);

    // Draw rectangle using world coordinates
    void draw_rectangle(float x, float y, float half_size_x, float half_size_y, u32 color);

    // Accessors for render scale
    float get_render_scale() const;
    void set_render_scale(float scale);

    int get_width() const;
    int get_height() const;
    void* get_memory() const;
    const BITMAPINFO* get_bitmap_info() const;
    void draw_image(const char* file_path, int x, int y, int width, int height);

private:
    // Private constructor/destructor for singleton
    Renderer();
    ~Renderer();

    float render_scale;
    Render_State render_state;

    void* allocate_memory(int size);
    void free_memory();
};

#endif // RENDERER_H
