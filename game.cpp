// game.cpp
#include "game.h"

// Initialize global variables
float player_pos_x = 0.f;
float player_pos_y = 0.f;

// Function implementation
void Simulate(Input* input) {
    if (was_pressed(BUTTON_LEFT)) {
        player_pos_x -= 1.f;
    }
    if (was_pressed(BUTTON_RIGHT)) {
        player_pos_x += 1.f;
    }
    if (was_pressed(BUTTON_UP)) {
        player_pos_y += 1.f;
    }
    if (was_pressed(BUTTON_DOWN)) {
        player_pos_y -= 1.f;
    }

    Renderer& renderer = Renderer::get_instance();

    // Render updates
    renderer.clear_screen(0xff5500);
    renderer.draw_rectangle(player_pos_x, player_pos_y, 4, 2, 0xff0000);
}
