// game.h
#ifndef GAME_H
#define GAME_H

#include "platform_common.h"
#include "renderer.h"

// Macros
#define is_down(b) input->buttons[b].is_down
#define was_pressed(b) (is_down(b) && input->buttons[b].changed)
#define was_released(b) (!is_down(b) && input->buttons[b].changed)

class Game {
public:
    Game();
    ~Game();

    // Initialize the game
    void initialize();

    // Run the game simulation
    void simulate(Input* input);

    // Record the latest time and calculate the seconds/frame
    void update_time();

private:
    // Player position
    float player_pos_x;
    float player_pos_y;
    float delta_time;
    float performance_frequency;
    LARGE_INTEGER frame_time;

    // Helper methods
    void process_input(Input* input);
    void update_renderer();
};

#endif // GAME_H
#pragma once
