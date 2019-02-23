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

// wheson
#define KC_ KC_TRNS
#define KC_RST RESET
enum user_macro {
  UM_EMHL,
  UM_KHKR
};
#define KC_EMHL MACROTAP(UM_EMHL)      // Lower / 英数(Mac)&変換(Win)
#define KC_KHKR MACROTAP(UM_KHKR)      // Raise / かな(Mac)&無変換(Win)
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
            ,      ,      ,  SPC ,/*|||*/ RGUI , EMHL , ENT  ,         SPC , KHKR , RALT ,/*|||*/ LEFT , DOWN ,  UP  , RGHT 
  // `--------------------------------------------------------      `-------------------------------------------------------'
  ),

  [_LOWER] = LAYOUT_kc(
  // ,------------------------------------------------.                    .------------------------------------------------.
        ESC , F11  ,  F12 ,      ,      ,      ,      ,                           ,      ,   7  ,   8  ,   9  ,      , BSPC ,
  // |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
       TABCT,  F6  ,   F7 ,  F8  ,  F9  ,  F10 ,      ,                           ,      ,   4  ,   5  ,   6  ,      ,      , 
  // |------+------+------+------+------+------+-------                    |------+------+------+------+------+------+------|
       LSFT ,  F1  ,   F2 ,  F3  ,  F4  ,  F5  ,      ,                           ,   0  ,   1  ,   2  ,   3  , DOT  ,      ,
  // |-------------+------+------+------+------+------+------.      .------+------+------+------+------+------+-------------|
            ,      ,      ,  SPC ,/*|||*/ RGUI , EMHL , ENT  ,         SPC , KHKR , RALT ,/*|||*/ HOME , PGDN , PGUP , END  
  // `--------------------------------------------------------      `-------------------------------------------------------'
  ),

  [_RAISE] = LAYOUT_kc(
  // \ [ ] ^ $      @ ! & |
  // # ( ) - ~      = + - %
  // ` { } _          * /
  // ,------------------------------------------------.                    .------------------------------------------------.
        ESC , BSLS , LBRC , RBRC , CIRC , DLR  ,      ,                           ,  AT  , EXLM , AMPR , PIPE ,      , BSPC ,
  // |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
       TABCT, HASH , LPRN , RPRN , MINS , TILD ,      ,                           ,  EQL , PLUS , MINS , PERC ,      ,      , 
  // |------+------+------+------+------+------+-------                    |------+------+------+------+------+------+------|
       LSFT , GRV  , LCBR , RCBR , UNDS ,      ,      ,                           ,      , ASTR , SLSH ,      ,      ,      ,
  // |-------------+------+------+------+------+------+------.      .------+------+------+------+------+------+-------------|
            ,      ,      ,  SPC ,/*|||*/ RGUI , EMHL , ENT  ,         SPC , KHKR , RALT ,/*|||*/ HOME , PGDN , PGUP , END  
  // `--------------------------------------------------------      `-------------------------------------------------------'
  ),

  [_ADJUST] = LAYOUT_kc(
  // ,------------------------------------------------.                    .------------------------------------------------.
            ,      ,      ,      ,      ,      ,      ,                           ,      ,      ,      ,      ,      ,      ,
  // |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
            ,      ,      ,      ,      ,      ,      ,                           ,      ,      ,      ,      ,      ,      ,
  // |------+------+------+------+------+------+-------                    |------+------+------+------+------+------+------|
            ,      ,      ,      ,      ,      ,      ,                           ,      ,      ,      ,      ,      ,      ,
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

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
        case UM_EMHL: // タップで「英数」と「無変換」、ホールドで「Lower」
        return MACRO_TAP_HOLD_LAYER( record, MACRO(T(MHEN), T(LANG2), END), _LOWER );
        case UM_KHKR: // タップで「かな」と「変換」、ホールドで「Raise」
        return MACRO_TAP_HOLD_LAYER( record, MACRO(T(HENK), T(LANG1), END), _RAISE );
        };
        return MACRO_NONE;
}
