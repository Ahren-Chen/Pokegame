#define is_down(b) input->buttons[b].is_down
#define was_pressed(b) (is_down(b) && input->buttons[b].changed)
#define was_released(b) (!is_down(b) && input->buttons[b].changed)

float player_pos_x = 0.f;
float player_pos_y = 0.f;

internal void Simulate(Input* input) {
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
    clear_screen(0xff5500);
    draw_rectangle(player_pos_x, player_pos_y, 4, 2, 0xff0000);
}