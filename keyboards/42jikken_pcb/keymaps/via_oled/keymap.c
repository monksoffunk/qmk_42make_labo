// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer{
    TENKEY = 0,
    HEX,
    FUNC,
    ADJ,

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [TENKEY] = LAYOUT_ortho_4x4_with_2encoder(
        KC_P7,   KC_P8,   KC_P9,   KC_PSLS,   KC_MUTE,
        KC_P4,   KC_P5,   KC_P6,   KC_PAST,   KC_ESC,
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        LT(HEX, KC_P0),   LT(FUNC, KC_PDOT), LT(ADJ, KC_PENT), KC_PPLS
    ),
    [HEX] = LAYOUT_ortho_4x4_with_2encoder(
        KC_P7,   KC_P8,   KC_P9,   KC_A,      KC_MUTE,
        KC_P4,   KC_P5,   KC_P6,   KC_B,      KC_ESC,
        KC_P1,   KC_P2,   KC_P3,   KC_C,
        KC_P0,   KC_F,    KC_E,    KC_D
    ),
    [FUNC] = LAYOUT_ortho_4x4_with_2encoder(
        KC_F7,   KC_F8,   KC_F9,   KC_F10,      KC_MUTE,
        KC_F4,   KC_F5,   KC_F6,   KC_F11,      KC_ESC,
        KC_F1,   KC_F2,   KC_F3,   KC_F12,
        KC_P0,   KC_PDOT, KC_PENT, KC_PPLS    
    ),
    [ADJ] = LAYOUT_ortho_4x4_with_2encoder(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_MUTE,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_ESC,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO    
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [TENKEY] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(RGB_MOD, RGB_RMOD)  },
    [HEX]  =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(RGB_VAD, RGB_VAI)  },
    [FUNC]  =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(RGB_SAD, RGB_SAI)  },
    [ADJ]  =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(RGB_HUD, RGB_HUI)  },
};
#endif

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case TENKEY:
            oled_write_P(PSTR("TENKEY\n"), false);
            break;
        case HEX:
            oled_write_P(PSTR("HEX\n"), false);
            break;
        case FUNC:
            oled_write_P(PSTR("FUNC\n"), false);
            break;
        case ADJ:
            oled_write_P(PSTR("ADJ\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    
    return false;
}
#endif