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
 * | Ctrl | GUI  | Alt  |Key lk|Lower |Raise |Space |      |Bkspce|AltGR | Ctrl | Left | Down |  Up  | Right|
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
     ESC, GRV , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,MINS,EQL ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     TAB ,RBRC, Q  , W  , E  , R  , T  ,      Y  , U  , I  , O  , P  ,LBRC,DEL ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     CAPS,NUHS, A  , S  , D  , F  , G  ,      H  , J  , K  , L  ,SCLN,QUOT,ENT ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     LSFT,LSFT, Z  , X  , C  , V  , B  ,      N  , M  ,COMM,DOT ,SLSH,RSFT,RGUI,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     LCTL,LGUI,LALT,INS ,LOWR,RASE,SPC ,     BSPC,RALT,RCTL,LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

/* Lower
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |  ESC |   `  |   1  |   2  |   3  |   4  |   5  |      |   6  |   7  |   8  |   9  |   0  |   -  |   =  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |  Tab |      |      |      |      |      |      |      |      |      |      |      |      |      | Del  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Caps |      | Cut  | Copy |Paste |Cancel|      |      |      | Left | Down |  Up  | Right|      |Enter |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      | Shift|      |      |      |      |      |      |      |      |      |      |      | Shift|Insert|
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |Key lk|Lower |Raise |Space |      |Bkspce|AltGR | Ctrl | Left | Down |  Up  | Right|
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
     ESC, GRV , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,MINS,EQL ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     TAB ,VOLU,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,DEL ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     CAPS,VOLD,CUT ,COPY,PSTE,UNDO,    ,         ,LEFT,DOWN, UP ,RGHT,    ,ENT ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     LSFT,LSFT,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,RSFT,RGUI,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     LCTL,LGUI,LALT,INS ,LOWR,RASE,SPC ,     BSPC,RALT,RCTL,LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

/* Raise
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |  ESC |   `  |   1  |   2  |   3  |   4  |   5  |      |   6  |   7  |   8  |   9  |   0  |   -  |   =  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |  Tab |Vol up|      |      | Pg up| Menu |NumLck|      |      |   7  |   8  |   9  |      |      | Del  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Caps |Vol dn| Home | ESC  | Pg dn| End  |ScrnLk|      |      |   4  |   5  |   6  |   .  |      |Enter |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      | Shift|      |      |      |      |Pause |      |      |   1  |   2  |   3  |   _  | Shift|Insert|
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |Key lk|Lower |Raise |Space |      |Bkspce|   0  |      | Left | Down |  Up  | Right|
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
     ESC, GRV , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,MINS,EQL ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     TAB ,VOLU,    ,    ,PGUP,MENU,NLCK,         ,KP_7,KP_8,KP_9,    ,    ,DEL ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     CAPS,VOLD,HOME,ESC ,PGDN,END ,SCLK,         ,KP_4,KP_5,KP_6,PDOT,    ,ENT ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     LSFT,LSFT,    ,    ,    ,    ,PAUS,         ,KP_1,KP_2,KP_3,UNSC,RSFT,RGUI,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     LCTL,LGUI,LALT,INS ,LOWR,RASE,SPC ,     BSPC,KP_0,    ,LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
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
