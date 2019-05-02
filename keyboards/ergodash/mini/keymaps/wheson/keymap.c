#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define EISU LALT(KC_GRV)
#define KC_LOWER LOWER
#define KC_RAISE RAISE

// wheson
#define KC_ KC_TRNS
#define KC_RST RESET
#define KC_EMHC LGUI_T(KC_HENK)      // ⌘ / 英数(Mac)&変換(Win)
#define KC_KHKA RALT_T(KC_MHEN)      // Alt / かな(Mac)&無変換(Win)
#define KC_TABCT LCTL_T(KC_TAB) // LeftControl / Tab

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc( \
  // ,------------------------------------------------.                    .------------------------------------------------.
        ESC ,   Q  ,   W  ,   E  ,   R  ,   T  ,      ,                           ,   Y  ,   U  ,   I  ,   O  ,   P  , BSPC ,
  // |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
       TABCT,   A  ,   S  ,   D  ,   F  ,   G  ,      ,                           ,   H  ,   J  ,   K  ,   L  , SCLN , QUOT , 
  // |------+------+------+------+------+------+-------                    |------+------+------+------+------+------+------|
       LSFT ,   Z  ,   X  ,   C  ,   V  ,   B  ,      ,                           ,   N  ,   M  , COMM ,  DOT , SLSH , RSFT ,
  // |-------------+------+------+------+------+------+------.      .------+------+------+------+------+------+-------------|
            ,      ,      ,  SPC ,/*|||*/ EMHC ,LOWER , ENT  ,         SPC ,RAISE , KHKA ,/*|||*/ LEFT , DOWN ,  UP  , RGHT 
  // `--------------------------------------------------------      `-------------------------------------------------------'
  ),

  [_LOWER] = LAYOUT_kc(
  // \ [ ] * %      ^ 7 8 9 !
  // # ( ) - +      $ 4 5 6 & @ 
  // ` { } _ =      0 1 2 3 | ~ 
  // ,------------------------------------------------.                    .------------------------------------------------.
        ESC , BSLS , LBRC , RBRC , ASTR , PERC ,      ,                           , CIRC ,   7  ,   8  ,   9  , EXLM , BSPC ,
  // |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
       TABCT, HASH , LPRN , RPRN , MINS , PLUS ,      ,                           , DLR  ,   4  ,   5  ,   6  , AMPR ,  AT  , 
  // |------+------+------+------+------+------+-------                    |------+------+------+------+------+------+------|
       LSFT , GRV  , LCBR , RCBR , UNDS , EQL  ,      ,                           ,   0  ,   1  ,   2  ,   3  , PIPE , TILD ,
  // |-------------+------+------+------+------+------+------.      .------+------+------+------+------+------+-------------|
            ,      ,      ,  SPC ,/*|||*/ EMHC ,LOWER , ENT  ,         SPC ,RAISE , KHKA ,/*|||*/ HOME , PGDN , PGUP , END  
  // `--------------------------------------------------------      `-------------------------------------------------------'
  ),

  [_RAISE] = LAYOUT_kc(
  // \ [ ] * %      ^ 7 8 9 !
  // # ( ) - +      $ 4 5 6 & @ 
  // ` { } _ =      0 1 2 3 | ~ 
  // ,------------------------------------------------.                    .------------------------------------------------.
        ESC , BSLS , LBRC , RBRC , ASTR , PERC ,      ,                           , CIRC ,   7  ,   8  ,   9  , EXLM , BSPC ,
  // |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
       TABCT, HASH , LPRN , RPRN , MINS , PLUS ,      ,                           , DLR  ,   4  ,   5  ,   6  , AMPR ,  AT  , 
  // |------+------+------+------+------+------+-------                    |------+------+------+------+------+------+------|
       LSFT , GRV  , LCBR , RCBR , UNDS , EQL  ,      ,                           ,   0  ,   1  ,   2  ,   3  , PIPE , TILD ,
  // |-------------+------+------+------+------+------+------.      .------+------+------+------+------+------+-------------|
            ,      ,      ,  SPC ,/*|||*/ EMHC ,LOWER , ENT  ,         SPC ,RAISE , KHKA ,/*|||*/ HOME , PGDN , PGUP , END  
  // `--------------------------------------------------------      `-------------------------------------------------------'
  ),

  [_ADJUST] = LAYOUT_kc(
  // ,------------------------------------------------.                    .------------------------------------------------.
            ,      ,      ,      ,      ,      ,      ,                           ,      ,      ,      ,      ,      ,      ,
  // |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
            ,      ,      ,      ,      ,      ,      ,                           ,  F7  ,  F8  ,  F9  ,  F10 ,  F11 ,  F12 ,
  // |------+------+------+------+------+------+-------                    |------+------+------+------+------+------+------|
            ,      ,      ,      ,      ,      ,      ,                           ,  F1  ,  F2  ,  F3  ,  F4  ,  F5  ,  F6  ,
  // |-------------+------+------+------+------+------+------.      .------+------+------+------+------+------+-------------|
            ,      ,      ,      ,/*|||*/      ,      ,      ,             ,      ,      ,/*|||*/      ,      ,      ,      
  // `--------------------------------------------------------      `-------------------------------------------------------'
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
