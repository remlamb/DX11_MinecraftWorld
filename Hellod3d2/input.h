#pragma once

namespace inputs {
struct input_state {
  bool esc = false;
  bool left = false;
  bool right = false;
  bool up = false;
  bool down = false;
  bool space = false;
  bool ctrl = false;

  float mouse_pos_x = 0.0f;
  float mouse_pos_y = 0.0f;

  float old_mouse_pos_x = 0.0f;
  float old_mouse_pos_y = 0.0f;

  float delta_mouse_pos_x = 0.0f;
  float delta_mouse_pos_y = 0.0f;

  bool is_mouse_relative = false;

  void CalculateDeltaMousePos() {
    delta_mouse_pos_x = mouse_pos_x - old_mouse_pos_x;
    delta_mouse_pos_y = mouse_pos_y - old_mouse_pos_y;
  }
};
}  // namespace inputs
