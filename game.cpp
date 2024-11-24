#include "game.h"

// Constructor
Game::Game()
    : player_pos_x(0.f), player_pos_y(0.f) {}

// Destructor
Game::~Game() {}

// Initialize the game
void Game::initialize() {
    // Any initialization logic for the game can go here
    player_pos_x = 0.f;
    player_pos_y = 0.f;
}

// Process player input
void Game::process_input(Input* input) {
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
}

// Update the renderer with the current game state
void Game::update_renderer() {
    Renderer& renderer = Renderer::get_instance();

    // Render updates
    renderer.clear_screen(0xff5500); // Clear with background color
    renderer.draw_rectangle(player_pos_x, player_pos_y, 4, 2, 0xff0000); // Draw the player
}

// Run the game simulation
void Game::simulate(Input* input) {
    process_input(input);
    update_renderer();
}
