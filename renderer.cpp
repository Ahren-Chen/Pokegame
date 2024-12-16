// renderer.cpp
#include "renderer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

// Singleton instance
Renderer& Renderer::get_instance() {
    static Renderer instance; // Initialized once, shared across the program
    return instance;
}

// Constructor
Renderer::Renderer() : render_scale(0.01f), render_state{} {
    render_state.memory = nullptr;
}

// Destructor
Renderer::~Renderer() {
    free_memory();
}

//float render_scale = 0.01f;

// Initialize the renderer
void Renderer::initialize(int width, int height) {
    render_state.width = width;
    render_state.height = height;

    int size = render_state.width * render_state.height * sizeof(u32);

    free_memory();
    render_state.memory = allocate_memory(size);

    render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
    render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
    render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
    render_state.bitmap_info.bmiHeader.biPlanes = 1;
    render_state.bitmap_info.bmiHeader.biBitCount = 32;
    render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;
}

// Allocate memory
void* Renderer::allocate_memory(int size) {
    return VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
}

// Free allocated memory
void Renderer::free_memory() {
    if (render_state.memory) {
        VirtualFree(render_state.memory, 0, MEM_RELEASE);
        render_state.memory = nullptr;
    }
}

void Renderer::clear_screen(u32 color) {
    u32* pixel = (u32*)render_state.memory;
    
    for (int y = 0; y < render_state.height; y++) {
        for (int x = 0; x < render_state.width; x++) {
            *pixel++ = color;
        }
    }
}

void Renderer::draw_rectangle_pixels(int left_bottom_X, int left_bottom_Y, int right_top_X, int right_top_Y, u32 color) {

    left_bottom_X = clamp(0, left_bottom_X, render_state.width);
    right_top_X = clamp(0, right_top_X, render_state.width);
    left_bottom_Y = clamp(0, left_bottom_Y, render_state.height);
    right_top_Y = clamp(0, right_top_Y, render_state.height);

    for (int y = left_bottom_Y; y < right_top_Y; y++) {
        u32* pixel = (u32*)render_state.memory + left_bottom_X + y * render_state.width;

        for (int x = left_bottom_X; x < right_top_X; x++) {
            if (left_bottom_X <= x && x <= right_top_X && left_bottom_Y <= y && y <= right_top_Y) {
                *pixel = color;
            }
            pixel++;
        }
    }
}

void Renderer::draw_rectangle(float x, float y, float half_size_x, float half_size_y, u32 color) {
    // Scale to render height as percentages
    x *= render_state.height * render_scale;
    y *= render_state.height * render_scale;
    half_size_x *= render_state.height * render_scale;
    half_size_y *= render_state.height * render_scale;

    // Centering the rectangle
    x += render_state.width / 2.f;
    y += render_state.height / 2.f;

    s32 left_bottom_X = x - half_size_x;
    s32 left_bottom_Y = y - half_size_y;
    s32 right_top_X = x + half_size_x;
    s32 right_top_Y = y + half_size_y;

    draw_rectangle_pixels(left_bottom_X, left_bottom_Y, right_top_X, right_top_Y, color);
}

// Render scale accessors
float Renderer::get_render_scale() const {
    return render_scale;
}

void Renderer::set_render_scale(float scale) {
    render_scale = scale;
}

int Renderer::get_width() const {
    return render_state.width;
}

int Renderer::get_height() const {
    return render_state.height;
}

void* Renderer::get_memory() const {
    return render_state.memory;
}

const BITMAPINFO* Renderer::get_bitmap_info() const {
    return &render_state.bitmap_info;
}

void Renderer::draw_image(const char* file_path, int x, int y, int width, int height) {
    int img_width, img_height, channels;
    // Load the image
    unsigned char* image_data = stbi_load(file_path, &img_width, &img_height, &channels, 4); // Force 4 channels (RGBA)

    if (!image_data) {
        //std::cerr << "Failed to load image: " << file_path << endl;
        return;
    }

    unsigned char* resized_image_data = new unsigned char[width * height * 4];  // RGBA
    stbir_resize_uint8_srgb(image_data, img_width, img_height, img_width * 4,  // Input image data and its original dimensions
        resized_image_data, width, height, // Output image data and new dimensions
        width * 4, stbir_pixel_layout::STBIR_RGBA);

    // Draw the image pixel by pixel
    if (resized_image_data) {
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                unsigned char* pixel = resized_image_data + (row * width + col) * 4;
                u32 color = (pixel[3] << 24) | (pixel[2] << 16) | (pixel[1] << 8) | pixel[0];

                // Calculate the target position in the renderer memory
                int draw_x = x + col;
                int draw_y = y + row;

                if (draw_x < render_state.width && draw_y < render_state.height) {
                    u32* target_pixel = (u32*)render_state.memory + draw_x + draw_y * render_state.width;
                    *target_pixel = color;
                }
            }
        }
    }

    delete[] resized_image_data;

    // Free the image data
    stbi_image_free(image_data);
}
