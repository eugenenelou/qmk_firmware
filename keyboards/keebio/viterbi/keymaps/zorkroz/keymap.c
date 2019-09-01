#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};

// Fillers to make layering more clear
#define KC_ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_LOWR LOWER
#define KC_RASE RAISE
// #define KC_CTLZ LCTL(KC_LBRC)
// #define KC_CTLX LCTL(KC_C)
// #define KC_CTLC LCTL(KC_H)
// #define KC_CTLV LCTL(KC_U)
#define KC_UNSC RALT(KC_SPC)
#define KC_SCLK LGUI(KC_O)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |  ESC |   `  |   1  |   2  |   3  |   4  |   5  |      |   6  |   7  |   8  |   9  |   0  |   -  |   =  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |  Tab |   ]  |   Q  |   W  |   E  |   R  |   T  |      |   Y  |   U  |   I  |   O  |   P  |   [  | Del  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Caps |   #  |   A  |   S  |   D  |   F  |   G  |      |   H  |   J  |   K  |   L  |   ;  |   "  |Enter |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Shift| Shift|   Z  |   X  |   C  |   V  |   B  |      |   N  |   M  |   ,  |   .  |   /  | Shift| GUI  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |Insert|Lower |Raise |Bkspce|      |Bkspce|AltGR | Ctrl | Left | Down |  Up  | Right|
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_QWERTY] = LAYOUT_kc(
  //,-------+-------+-------+-------+-------+-------+-------.    ,-------+-------+-------+-------+-------+-------+-------.
     KC_ESC ,KC_GRV , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,      KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_MINS,KC_EQL ,
  //|-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------|
     KC_TAB ,KC_RBRC, KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,      KC_Y  , KC_U   ,KC_I  , KC_O  , KC_P  ,KC_LBRC,KC_DEL ,
  //|-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------|
     KC_CAPS,KC_NUHS, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,      KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,KC_ENT ,
  //|-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------|
     KC_LSFT,KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,      KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_RSFT,KC_RGUI,
  //|-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------|
     KC_LCTL,KC_LGUI,KC_LALT,KC_INS ,KC_LOWR,KC_RASE,KC_BSPC,     KC_SPC ,KC_RALT,KC_RCTL,KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT
  //`-------+-------+-------+-------+-------+-------+-------'    `-------+-------+-------+-------+-------+-------+-------'
  ),

/* Lower
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |  ESC |   `  |   1  |   2  |   3  |   4  |   5  |      |   6  |   7  |   8  |   9  |   0  |   -  |   =  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |  Tab |      |      |      |      |      |      |      |      |      |      |      |      |      | Del  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Caps |      | Cut  | Copy |Paste |Cancel|      |      |      | Left | Down |  Up  | Right|      |Enter |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      | Shift|      |      |      |      |      |      |      |      |      |      |      | Shift| GUI  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |Insert|Lower |Raise |Bkspce|      | Space|AltGR | Ctrl | Left | Down |  Up  | Right|
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_LOWER] = LAYOUT_kc(
  //,-------+-------+-------+-------+-------+-------+-------.    ,-------+-------+-------+-------+-------+-------+-------.
     KC_ESC ,KC_GRV , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,      KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_MINS,KC_EQL ,
  //|-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------|
     KC_TAB ,KC_VOLU,       ,       ,       ,       ,       ,            ,       ,       ,       ,       ,       ,KC_DEL ,
  //|-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------|
     KC_CAPS,KC_VOLD,KC_CUT ,KC_COPY,KC_PSTE,KC_UNDO,       ,            ,KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT,       ,KC_ENT ,
  //|-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------|
     KC_LSFT,KC_LSFT,       ,       ,       ,       ,       ,            ,       ,       ,       ,       ,KC_RSFT,KC_RGUI,
  //|-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------|
     KC_LCTL,KC_LGUI,KC_LALT,KC_INS ,KC_LOWR,KC_RASE,KC_BSPC,     KC_SPC ,KC_RALT,KC_RCTL,KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT
  //`-------+-------+-------+-------+-------+-------+-------'    `-------+-------+-------+-------+-------+-------+-------'
  ),

/* Raise
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |  ESC |   `  |   1  |   2  |   3  |   4  |   5  |      |   6  |   7  |   8  |   9  |   0  |   -  |   =  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |  Tab |Vol up|      |      | Pg up| Menu |NumLck|      |      |   7  |   8  |   9  |      |      | Del  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Caps |Vol dn| Home | ESC  | Pg dn| End  |ScrnLk|      |      |   4  |   5  |   6  |   .  |      |Enter |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      | Shift|      |      |      |      |Pause |      |      |   1  |   2  |   3  |   _  | Shift| GUI  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |Insert|Lower |Raise |Bkspce|      | Space|   0  |      | Left | Down |  Up  | Right|
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_RAISE] = LAYOUT_kc(
  //,-------+-------+-------+-------+-------+-------+-------.    ,-------+-------+-------+-------+-------+-------+-------.
     KC_ESC, KC_GRV ,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,     KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,
  //|-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------|
     KC_TAB ,KC_VOLU,       ,       ,KC_PGUP,KC_MENU,KC_NLCK,            , KC_P7 , KC_P8 , KC_P9 ,       ,       ,KC_DEL ,
  //|-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------|
     KC_CAPS,KC_VOLD,KC_HOME,KC_ESC ,KC_PGDN,KC_END ,KC_SCLK,            , KC_P4 , KC_P5 , KC_P6 ,KC_PDOT,       ,KC_ENT ,
  //|-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------|
     KC_LSFT,KC_LSFT,       ,       ,       ,       ,KC_PAUS,            , KC_P1 , KC_P2 , KC_P3 ,KC_UNSC,KC_RSFT,KC_RGUI,
  //|-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------|
     KC_LCTL,KC_LGUI,KC_LALT,KC_INS ,KC_LOWR,KC_RASE,KC_BSPC ,    KC_SPC , KC_P0 , KC_P0 ,KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT
  //`-------+-------+-------+-------+-------+-------+-------'    `-------+-------+-------+-------+-------+-------+-------'
  ),

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _QWERTY);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _QWERTY);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _QWERTY);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _QWERTY);
      }
      return false;
      break;
  }
  return true;
}
