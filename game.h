// game.h
#ifndef GAME_H
#define GAME_H

#include "platform_common.h"
#include "renderer.h"

// Macros
#define is_down(b) input->buttons[b].is_down
#define was_pressed(b) (is_down(b) && input->buttons[b].changed)
#define was_released(b) (!is_down(b) && input->buttons[b].changed)

// Global variables for player position
extern float player_pos_x;
extern float player_pos_y;

// Function declaration
void Simulate(Input* input);

#endif // GAME_H
#pragma once
