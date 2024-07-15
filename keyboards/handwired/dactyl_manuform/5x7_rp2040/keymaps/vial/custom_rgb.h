#include QMK_KEYBOARD_H
//#include "dynamic_keymap.h"
#define CUSTOM_RGB_H

void set_colour(uint8_t led_index, uint16_t hue, uint8_t sat, uint8_t val){
    uint8_t brightness = val;
    if (val > rgb_matrix_get_val()) {
        brightness = rgb_matrix_get_val();
    }
    HSV hsv = (HSV){hue, sat, brightness};
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(led_index, rgb.r, rgb.g, rgb.b);
}

void set_base_layer_colours(uint8_t led_min, uint8_t led_max){
    uint8_t led_processed_count = 0;

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            if (led_processed_count == RGB_MATRIX_LED_PROCESS_LIMIT){
                return;
            }
            uint8_t led_index = g_led_config.matrix_co[row][col];
            uint16_t keycode = keymap_key_to_keycode(0, (keypos_t){col,row});
            if (led_index >= led_min && led_index <= led_max && led_index != NO_LED) {
                led_processed_count++;

                switch (keycode)
                {
                    case KC_CAPS_LOCK:
                        set_colour(led_index, HSV_GREEN);
                        break;
                    case KC_A ... KC_Z:
                        if(host_keyboard_led_state().caps_lock){
                            set_colour(led_index, HSV_RED);
                        }
                        else{
                            set_colour(led_index, HSV_BLUE);
                        }
                        break;
                    case KC_ENTER:
                        set_colour(led_index, HSV_MAGENTA);
                        break;
                    case KC_BACKSPACE:
                    case KC_DELETE:
                    case QK_BOOTLOADER:
                        set_colour(led_index, HSV_RED);
                        break;
                    case KC_TAB ... KC_SLASH:
                    case MODIFIER_KEYCODE_RANGE:
                        set_colour(led_index, HSV_GOLD);
                        break;
                    case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
                    case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
                    case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
                    case QK_MOMENTARY ... QK_MOMENTARY_MAX:
                    case QK_MOD_TAP ... QK_MOD_TAP_MAX:
                    case MAGIC_KEYCODE_RANGE:
                        set_colour(led_index, HSV_PURPLE);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void set_active_layer_colours(uint8_t led_min, uint8_t led_max){
    uint8_t led_processed_count = 0;

    //Turn off the whole board before colouring the active keys.
    rgb_matrix_sethsv_noeeprom(HSV_OFF);

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            if (led_processed_count == RGB_MATRIX_LED_PROCESS_LIMIT){
                return;
            }
            uint8_t led_index = g_led_config.matrix_co[row][col];
            if (led_index >= led_min && led_index <= led_max && led_index != NO_LED) {
                led_processed_count++;
                uint8_t layer = get_highest_layer(layer_state);
                uint16_t momentary_keycode = keymap_key_to_keycode(layer, (keypos_t){col,row});
                if (momentary_keycode <= KC_TRNS) {
                    continue;
                }
                // The middle layer is green, except that the numpad section turns
                // orange when Num Lock is on:
                bool num_lock_state = host_keyboard_led_state().num_lock;
                bool scroll_lock_state = host_keyboard_led_state().scroll_lock;

                switch (momentary_keycode)
                {
                    case KC_KP_EQUAL:
                    case KC_KP_SLASH ... KC_KP_DOT:
                        if (num_lock_state){
                            set_colour(led_index, HSV_PURPLE);
                        }
                        else{
                            set_colour(led_index, HSV_ORANGE);
                        }
                        break;
                    case KC_NUM_LOCK:
                        if (num_lock_state){
                            set_colour(led_index, HSV_GREEN);
                        }
                        else{
                            set_colour(led_index, HSV_PINK);
                        }
                        break;
                    case KC_RIGHT ... KC_UP:
                        if (scroll_lock_state){
                            set_colour(led_index, HSV_ORANGE);
                        }
                        else{
                            set_colour(led_index, HSV_PURPLE);
                        }
                    default:
                        set_colour(led_index, HSV_BLUE);
                        break;
                }
            }
        }
    }
}

// void set_dynamic_key_colours(){
//     uint16_t dyn_keycode = dynamic_keymap_get_keycode(0, row, col);
//     switch (dyn_keycode) {
//         case KC_NO:
//         case KC_TRNS:
//             rgb_matrix_set_color(led_index, 0, 0, 0);
//             break;
//         case KC_A ... KC_Z:
//             rgb_matrix_set_color(led_index, 0, 119, 255);
//             break;
//         default:
//             break;
//     }
// }
