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

    delta_time = 0.016666;
    QueryPerformanceCounter(&frame_time);

    LARGE_INTEGER perf;
    QueryPerformanceFrequency(&perf);
    performance_frequency = (float)perf.QuadPart;
}

// Process player input
void Game::process_input(Input* input) {
    float speed = 50.f; // units per second

    if (is_down(BUTTON_LEFT)) {
        player_pos_x -= speed * delta_time;
    }
    if (is_down(BUTTON_RIGHT)) {
        player_pos_x += speed * delta_time;
    }
    if (is_down(BUTTON_UP)) {
        player_pos_y += speed * delta_time;
    }
    if (is_down(BUTTON_DOWN)) {
        player_pos_y -= speed * delta_time;
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

void Game::update_time() {
    LARGE_INTEGER frame_end_time;
    QueryPerformanceCounter(&frame_end_time);
    delta_time = (float)(frame_end_time.QuadPart - frame_time.QuadPart) / performance_frequency;
    frame_time = frame_end_time;
}