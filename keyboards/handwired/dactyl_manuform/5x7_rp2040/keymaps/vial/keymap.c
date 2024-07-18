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
    #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode(RGB_MATRIX_CUSTOM_CUSTOM_SOLID_COLOURS);
    #endif  // RGB_MATRIX_ENABLE
}

// Custom RGB indicator behaviour:
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_CUSTOM_SOLID_COLOURS);
    return false;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode(RGB_MATRIX_CUSTOM_CUSTOM_SOLID_COLOURS);
    #endif
    return state;
}
