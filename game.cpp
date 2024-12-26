#include "game.h"

// Constructor
Game::Game() {
    // Initialize player positions
    player_pos_x = -80.f;
    player_pos_y = 0.f;
    arena_half_size_x = 85.f;
    arena_half_size_y = 45.f;
    player_half_size_x = 2.5f;
    player_half_size_y = 12.f;
    ball_x = 0.f;
    ball_y = 0.f;
    ball_dp_x = 70;
    ball_dp_y = 0;
    ball_half_size = 1;

    // Initialize delta time
    delta_time = 0.016666f;

    // Query performance counters for timing
    QueryPerformanceCounter(&frame_time);

    LARGE_INTEGER perf;
    QueryPerformanceFrequency(&perf);
    performance_frequency = (float)perf.QuadPart;
}

// Destructor
Game::~Game() {}

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

    // Arena
    renderer.draw_rectangle(0, 0, arena_half_size_x, arena_half_size_y, 0xffaa33);

    process_ball();

    // Other paddle object
    renderer.draw_rectangle(80, 0, player_half_size_x, player_half_size_y, 0xff0000);

    // Player wall collision
    if (player_pos_x + player_half_size_x > arena_half_size_x) {
        player_pos_x = arena_half_size_x - player_half_size_x;
    }
    else if (player_pos_x - player_half_size_x < -arena_half_size_x) {
        player_pos_x = -arena_half_size_x + player_half_size_x;
    }

    if (player_pos_y + player_half_size_y > arena_half_size_y) {
        player_pos_y = arena_half_size_y - player_half_size_y;
    }
    else if (player_pos_y - player_half_size_y < -arena_half_size_y) {
        player_pos_y = -arena_half_size_y + player_half_size_y;
    }

    // Player
    renderer.draw_rectangle(player_pos_x, player_pos_y, 2.5, 12, 0xff0000);

    // Image test
    const char* image_path = "test.png";
    renderer.draw_image(image_path, 0, 0, 8, 8);
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

void Game::process_ball() {
    Renderer& renderer = Renderer::get_instance();

    ball_x += ball_dp_x * delta_time;
    ball_y += ball_dp_y * delta_time;

    // Collision with non player paddle
    if (ball_x + ball_half_size > 80 - player_half_size_x &&
        ball_x - ball_half_size < 80 + player_half_size_x &&
        ball_y + ball_half_size > 0 - player_half_size_y &&
        ball_y - ball_half_size < 0 + player_half_size_y) {

        ball_x = 80 - player_half_size_x - ball_half_size;
        ball_dp_x *= -1;
        ball_dp_y = (ball_y - 0)*3;
    }
    // Collision with player paddle
    else if (ball_x + ball_half_size > player_pos_x - player_half_size_x &&
        ball_x - ball_half_size < player_pos_x + player_half_size_x &&
        ball_y + ball_half_size > player_pos_y - player_half_size_y &&
        ball_y - ball_half_size < player_pos_y + player_half_size_y) {

        ball_x = player_pos_x + player_half_size_x + ball_half_size;
        ball_dp_x *= -1;

        ball_dp_y = (ball_y - player_pos_y) * 3;
    }

    // Collision with arena top and bottom
    if (ball_y + ball_half_size > arena_half_size_y) {
        ball_y = arena_half_size_y - ball_half_size;
        ball_dp_y *= -1;
    }
    else if (ball_y - ball_half_size < -arena_half_size_y) {
        ball_y = -arena_half_size_y + ball_half_size;
        ball_dp_y *= -1;
    }
    
    // Draw Ball 
    renderer.draw_rectangle(ball_x, ball_y, ball_half_size, ball_half_size, 0xffffff);
}