// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(custom_solid_colours)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "keymap_common.h"
#include "keycodes.h"
#include "dynamic_keymap.h"

// e.g: A simple effect, self-contained within a single method
static bool custom_solid_colours(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  uint8_t led_processed_count = 0;
  //RGB rgb = hsv_to_rgb(rgb_matrix_config.hsv);
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            if (led_processed_count == RGB_MATRIX_LED_PROCESS_LIMIT){
                return true;
            }
            uint8_t led_index = g_led_config.matrix_co[row][col];
            uint16_t keycode = keymap_key_to_keycode(0, (keypos_t){col,row});
            if (keycode >= KC_A && keycode <= KC_Z) {
                rgb_matrix_set_color(led_index, 0, 119, 255);
            }
            uint16_t dyn_keycode = dynamic_keymap_get_keycode(0, row, col);
            switch (dyn_keycode) {
                case KC_NO:
                case KC_TRNS:
                    rgb_matrix_set_color(led_index, 0, 0, 0);
                    break;
                case KC_A ... KC_Z:
                    rgb_matrix_set_color(led_index, 0, 119, 255);
                    break;
                default:
                    //rgb_matrix_set_color(led_index, rgb.r, rgb.g, rgb.b);
                    break;
            }
        }
    }
  return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
