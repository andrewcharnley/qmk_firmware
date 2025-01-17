#include QMK_KEYBOARD_H

// Windows key changed to second FN key. Use KC_LGUI to revert.

enum userspace_layers {
  QWERTY,
  FNLAYER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.

    [QWERTY] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, MO(FNLAYER), KC_LALT,                            KC_SPC,                       KC_RALT, MO(FNLAYER),KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [FNLAYER] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_MEDIA_PLAY_PAUSE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET  ,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RGB_VAI, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, RGB_VAD, _______
    ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if(IS_LAYER_ON(FNLAYER)) {
     if (clockwise) {
       tap_code(KC_MEDIA_NEXT_TRACK);
     } else {
       tap_code(KC_MEDIA_PREV_TRACK);
     }
  } else {
     if (clockwise) {
       tap_code(KC_VOLU);
     } else {
       tap_code(KC_VOLD);
     }
  }
  return false;
}

static uint8_t val;

void keyboard_post_init_user(void) {

  val = rgb_matrix_get_val();
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

  if (host_keyboard_led_state().caps_lock) {
    rgb_matrix_set_color_all(val,0,0);
  } else {
    rgb_matrix_set_color_all(val, val, val);
    val = rgb_matrix_get_val();
  }
}
