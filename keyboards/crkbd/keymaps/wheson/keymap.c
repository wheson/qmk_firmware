#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)

// wheson
#define KC_ KC_TRNS
#define KC_EMHC LGUI_T(KC_HENK)      // ⌘ / 英数(Mac)&変換(Win)
#define KC_KHKA RALT_T(KC_MHEN)      // Alt / かな(Mac)&無変換(Win)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       ESC ,   Q  ,   W  ,   E  ,   R  ,   T  ,                    Y  ,   U  ,   I  ,   O  ,   P  , BSPC ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,   A  ,   S  ,   D  ,   F  ,   G  ,                    H  ,   J  ,   K  ,   L  ,  SCLN, QUOT ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      LSFT ,   Z  ,   X  ,   C  ,   V  ,   B  ,                    N  ,   M  , COMM ,  DOT , SLSH , RSFT ,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  EMHC, LOWER,   ENT ,     SPC , RAISE, KHKA \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  // \ [ ] * %      ^ 7 8 9 !
  // # ( ) - +      $ 4 5 6 & @
  // ` { } = _      0 1 2 3 | ~
  //,-----------------------------------------.                ,-----------------------------------------.
       ESC , BSLS , LBRC , RBRC , ASTR , PERC ,                  CIRC ,   7  ,   8  ,   9  , EXLM , BSPC ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB, HASH , LPRN , RPRN , MINS , PLUS ,                  DLR  ,   4  ,   5  ,   6  , AMPR ,  AT  ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      LSFT , GRV  , LCBR , RCBR , EQL  , UNDS ,                    0  ,   1  ,   2  ,   3  , PIPE , TILD ,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  EMHC, LOWER,   ENT ,     SPC , RAISE, KHKA \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  // \ [ ] * %      ^ 7 8 9 !
  // # ( ) - +      $ 4 5 6 & @
  // ` { } = _      0 1 2 3 | ~
  //,-----------------------------------------.                ,-----------------------------------------.
       ESC , BSLS , LBRC , RBRC , ASTR , PERC ,                  CIRC ,   7  ,   8  ,   9  , EXLM , BSPC ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB, HASH , LPRN , RPRN , MINS , PLUS ,                  DLR  ,   4  ,   5  ,   6  , AMPR ,  AT  ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      LSFT , GRV  , LCBR , RCBR , EQL  , UNDS ,                    0  ,   1  ,   2  ,   3  , PIPE , TILD ,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  EMHC, LOWER,   ENT ,     SPC , RAISE, KHKA \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  LRST, XXXXX, XXXXX, XXXXX, XXXXX,                   F7  ,  F8  ,  F9  ,  F10 ,  F11 ,  F12 ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, XXXXX, XXXXX,                   F4  ,  F5  ,  F6  , XXXXX,  UP  , XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD, XXXXX, XXXXX,                   F1  ,  F2  ,  F3  , LEFT , DOWN , RIGHT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  EMHC, LOWER,   ENT ,     SPC , RAISE, KHKA \
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  /*
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
  */
  matrix_write(matrix, read_logo());
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
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
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

