#include QMK_KEYBOARD_H

#define _DVORAK 0
#define _ACTIONS 1
#define _NUMPAD 2
#define _FUNCTIONS 3
#define MAC_SCRNSHOT LSG(KC_5)
#define REFRESH G(KC_R)
#define MAC_COPY G(KC_C)
#define MAC_CUT G(KC_X)
#define MAC_PASTE G(KC_V)
#define MAC_PASTE_SPECIAL RCS(KC_V)
#define ZOOM_RAISE_HAND ROPT(KC_Y)
#define ZOOM_LEAVE_MEETING G(KC_W)
#define ZOOM_TOGGLE_VIDEO LSG(KC_V)
#define ZOOM_TOGGLE_MUTE LSG(KC_A)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DVORAK] = LAYOUT(
        KC_ESC , KC_1, KC_2, KC_3, KC_4, KC_5, REFRESH,                        _______, KC_6, KC_7, KC_8,   KC_9,   KC_0,   KC_EQL,
        KC_TAB,  KC_QUOT, KC_COMM,KC_DOT, KC_P, KC_Y, G(KC_A),                 KC_SLSH, KC_F, KC_G, KC_C,   KC_R,   KC_L,   KC_BSLS,
        KC_CAPS, LT(_ACTIONS, KC_A), KC_O, KC_E, KC_U, KC_I, G(KC_S),                        _______, KC_D, KC_H, KC_T,   KC_N,   KC_S,  KC_MINS,
        KC_LSFT, LGUI_T(KC_SCLN), LOPT_T(KC_Q), KC_J, KC_K, KC_X, G(KC_SPC),                     _______,   LT(_NUMPAD, KC_B), KC_M, KC_W, RALT_T(KC_V) ,RGUI_T(KC_Z), KC_RSFT,
        KC_LCTL,KC_LGUI,KC_LBRC, KC_RBRC,                                                                   KC_SCLN, KC_GRV, KC_RALT,  KC_RCTL,
                                            KC_SPC,KC_BSPC,                        KC_DEL, KC_ENT,
                                            G(KC_GRV), LAG(KC_W),                  _______,  _______,
                                            MAC_COPY, MAC_PASTE,                      MAC_CUT, MAC_PASTE_SPECIAL
        ),

    [_ACTIONS] = LAYOUT(
        _______,LCAG(KC_1),LCAG(KC_2), LCA(KC_D) ,LCA(KC_LEFT),LCA(KC_E) ,LCA(KC_C),                        QK_BOOT,LCA(KC_T),LCA(KC_RIGHT),LCA(KC_G),LCAG(KC_9),LCAG(KC_0),_______,
        _______,_______,_______,_______,_______,_______,_______,                        KC_APP, _______ , KC_HOME , KC_UP ,KC_END,_______,_______,
        _______,_______,_______,_______,_______,_______ ,_______,                       MAC_SCRNSHOT, _______ , KC_LEFT , KC_DOWN ,KC_RIGHT,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,                        QK_CLEAR_EEPROM, _______, KC_PGUP , _______ ,KC_PGDN ,_______,_______,
        _______,_______,_______,_______,                                                                         ZOOM_TOGGLE_MUTE,ZOOM_TOGGLE_VIDEO,ZOOM_RAISE_HAND,ZOOM_LEAVE_MEETING,
                                             _______,_______,            _______,_______,
                                             _______,_______,            KC_MEDIA_PLAY_PAUSE,KC_KB_MUTE,
                                             _______,_______,            KC_KB_VOLUME_UP,KC_KB_VOLUME_DOWN
        ),

    [_NUMPAD] = LAYOUT(
        _______,_______,_______,_______,_______,_______,_______,                        _______,KC_NUM,KC_KP_ASTERISK,KC_KP_PLUS,KC_KP_MINUS,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,                        _______,KC_KP_SLASH,KC_P7,KC_P8 ,KC_P9,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,                        _______,_______,KC_P4,KC_P5,KC_P6,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,                        _______,_______,KC_P1,KC_P2,KC_P3,_______,_______,
        _______,_______,_______,_______,                                                                        KC_P0,KC_PDOT,_______,_______,
                                             _______,_______,            _______,_______,
                                             _______,_______,            _______,_______,
                                             _______,_______,            _______,_______
        ),
    [_FUNCTIONS] = LAYOUT(
        _______,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,                                    KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,_______,
        _______,_______,_______,_______,_______,_______,_______,                        _______,KC_KP_SLASH,KC_P7,KC_P8 ,KC_P9,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,                        _______,_______,KC_P4,KC_P5,KC_P6,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,                        _______,_______,KC_P1,KC_P2,KC_P3,_______,_______,
        _______,_______,_______,_______,                                                                        KC_P0,KC_PDOT,_______,_______,
                                             _______,_______,            _______,_______,
                                             _______,_______,            _______,_______,
                                             _______,_______,            _______,_______
        )
};

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
    debug_mouse=true;
#else
    debug_enable=false;
    debug_matrix=false;
    debug_keyboard=false;
    debug_mouse=false;
#endif
}

void set_colour(uint8_t led_index, uint16_t hue, uint8_t sat, uint8_t val){
    uint8_t brightness = val;
    if (val > rgb_matrix_get_val()) {
        brightness = rgb_matrix_get_val();
    }
    HSV hsv = (HSV){hue, sat, brightness};
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(led_index, rgb.r, rgb.g, rgb.b);
}

// Custom RGB indicator behaviour:
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t led_processed_count = 0;
    //uint8_t brightness = rgb_matrix_config.hsv.v;

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            if (led_processed_count == RGB_MATRIX_LED_PROCESS_LIMIT){
                return false;
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
                        //set_colour(led_index, base_colour.r, base_colour.g, base_colour.b);
                        break;
                }

                // Whenever a layer above base is active, recolour only the keys that are different on that layer:
                if (get_highest_layer(layer_state) > 0) {
                    uint8_t layer = get_highest_layer(layer_state);
                    uint16_t momentary_keycode = keymap_key_to_keycode(layer, (keypos_t){col,row});
                    if (momentary_keycode > KC_TRNS) {
                        // The middle layer is green, except that the numpad section turns
                        // orange when Num Lock is on:
                        if (host_keyboard_led_state().num_lock &&
                        (momentary_keycode == KC_KP_EQUAL ||
                        (momentary_keycode >= KC_NUM_LOCK && momentary_keycode <= KC_KP_DOT)
                        )) {
                            if(momentary_keycode == KC_NUM_LOCK){
                                set_colour(led_index,  HSV_GREEN);
                            }
                            else
                            {
                                set_colour(led_index, HSV_PURPLE);
                            }
                        } else {
                            set_colour(led_index, HSV_BLUE);
                        }
                        // Light arrow keys orange if Scroll Lock is on, otherwise light them purple:
                        if (momentary_keycode >= KC_RIGHT && momentary_keycode <= KC_UP) {
                            if (host_keyboard_led_state().scroll_lock) {
                                set_colour(led_index, HSV_ORANGE);
                            } else {
                                set_colour(led_index, HSV_PURPLE);
                            }
                        }
                    }
                    else{
                        set_colour(led_index, HSV_OFF);
                    }
                }
            }
        }
    }
    return false;
}
