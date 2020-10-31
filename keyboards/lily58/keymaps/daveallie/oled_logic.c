#define ANIM_FRAMES 5
#define ANIM_SIZE 128
#define ANIM_FRAME_DURATION 20

uint32_t anim_timer = 0;
uint8_t current_frame = 0;
uint8_t current_layer = 0;
uint8_t last_layer = 0;

// 32px x 32px
static bool render_layer_chevrons(uint8_t row) {
    static const char PROGMEM empty[][ANIM_SIZE] = {
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,0,0,0,0,0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }};
    static const char PROGMEM lower[ANIM_FRAMES][ANIM_SIZE] = {
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,112,248,252,248,240, 96,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16, 56,124,254,252,252,254,124, 56, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,128,  0,  0,  0,  0,  0,  0,128,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 15, 31, 63,127,254,252,252,254,127, 63, 31, 15,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48,120,252,252,248,240,224,192,128,  0,  0,  0,  0,  0,  0,128,192,224,240,248,252,252,120, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  7, 15, 31, 63,127,254,252,252,254,127, 63, 31, 15,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,  0,  0,  0,  0,  4, 14, 31, 63,127,254,252,248,240,224,192,128,  0,  0,  0,  0,  0,  0,128,192,224,240,248,252,254,127, 63, 31, 14,  4,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  7, 15, 31, 63,127,254,252,252,254,127, 63, 31, 15,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
    };
    static const char PROGMEM raise[ANIM_FRAMES][ANIM_SIZE] = {
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6, 15, 31, 63, 31, 14,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8, 28, 62,127, 63, 63,127, 62, 28,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,240,248,252,254,127, 63, 63,127,254,252,248,240,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  1,  0,  0,  0,  0,  0,  0,  1,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,224,240,248,252,254,127, 63, 63,127,254,252,248,240,224,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12, 30, 63, 63, 31, 15,  7,  3,  1,  0,  0,  0,  0,  0,  0,  1,  3,  7, 15, 31, 63, 63, 30, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,224,240,248,252,254,127, 63, 63,127,254,252,248,240,224,192,128,  0,  0,  0,  0,  0,  0,  0,  0, 32,112,248,252,254,127, 63, 31, 15,  7,  3,  1,  0,  0,  0,  0,  0,  0,  1,  3,  7, 15, 31, 63,127,254,252,248,112, 32,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0 }
    };
    static const char PROGMEM adjust[ANIM_FRAMES][ANIM_SIZE] = {
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6, 15, 31, 63, 31, 14,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,112,248,252,248,240, 96,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8, 28, 62,127, 63, 63,127, 62, 28,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24, 60,126,254,252,252,254,124, 60, 24,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,240,248,252,254,127, 63, 63,127,254,252,248,240,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 15, 31, 63,127,254,252,252,254,127, 63, 31, 15,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48,120,252,252,248,240,240,248,252,254,127, 63, 63,127,254,252,248,240,240,248,252,252,120, 48,  0,  0,  0,  0,  0,  0,  0,  0, 12, 30, 63, 63, 31, 15, 15, 31, 63,127,254,252,252,254,127, 63, 31, 15, 15, 31, 63, 63, 30, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,  0,  0,  0,  0,  4, 14, 31, 63,127,254,252,248,240,240,248,252,254,127, 63, 63,127,254,252,248,240,240,248,252,254,127, 63, 31, 14,  4,  0,  0, 32,112,248,252,254,127, 63, 31, 15, 15, 31, 63,127,254,252,252,254,127, 63, 31, 15, 15, 31, 63,127,254,252,248,112, 32,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0 }
    };

    uint8_t current_active_layer(void) {
        switch (get_layer()) {
            case _RAISE:
            case _LOWER:
            case _ADJUST:
                return get_layer();
            default:
                return 0;
        }
    }

    //assumes 1 frame prep stage
    bool animation_phase(void) {
        if (current_layer != current_active_layer()) {
            if (current_layer != 0 && current_active_layer() != 0) {
                current_frame = 0;
                last_layer = 0;
                current_layer = current_active_layer();
            } else {
                last_layer = current_layer;
                current_layer = current_active_layer();
            }
        }

        oled_set_cursor(0, row);

        if (current_layer == 0 && current_frame == 0) {
            oled_write_raw_P(empty[0], ANIM_SIZE);
            return true;
        }

        if (current_layer == 0 && current_frame > 0) {
            switch (last_layer) {
                case _RAISE:
                    oled_write_raw_P(raise[current_frame], ANIM_SIZE);
                    break;
                case _LOWER:
                    oled_write_raw_P(lower[current_frame], ANIM_SIZE);
                    break;
                case _ADJUST:
                    oled_write_raw_P(adjust[current_frame], ANIM_SIZE);
                    break;
                default:
                    oled_write_raw_P(empty[0], ANIM_SIZE);
                    return true;
            }
            current_frame = current_frame - 1;
            return false;
        }

        switch (current_layer) {
            case _RAISE:
                oled_write_raw_P(raise[current_frame], ANIM_SIZE);
                break;
            case _LOWER:
                oled_write_raw_P(lower[current_frame], ANIM_SIZE);
                break;
            case _ADJUST:
                oled_write_raw_P(adjust[current_frame], ANIM_SIZE);
                break;
            default:
                oled_write_raw_P(empty[0], ANIM_SIZE);
                return true;
        }
        if (current_frame < ANIM_FRAMES - 1) {
            current_frame = current_frame + 1;
        }

        return false;
    }

    bool res = false;
    if (current_active_layer() != 0) {
        if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            res = animation_phase();
        }
    } else {
        if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            res = animation_phase();
        }
    }
    return res;
}

// 1 row (8px)
static void render_time(uint8_t row) {
    if (is_time_set()) {
            // don't turn on the OLED just to update the time
            if (is_oled_on()) {
                oled_set_cursor(0, row);
                oled_write_ln(get_time_string(), false);
            }
        }
}

// 2 rows (16px)
static void render_caps_lock(uint8_t row) {
    oled_set_cursor(0, row);

    if (get_caps_lock()) {
        char line1[6] = { 0x85, 0x86, 0x87, 0x88, 0x89, 0 };
        char line2[6] = { 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0 };
        oled_write(line1, false);
        oled_write_ln(line2, false);
    } else {
        char line1[6] = { 0x80, 0x81, 0x82, 0x83, 0x84, 0 };
        char line2[6] = { 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0 };
        oled_write(line1, false);
        oled_write_ln(line2, false);
    }
}

// 2 rows (16px)
static void render_keyboard_base_info(uint8_t row) {
    oled_set_cursor(3, row);
    if (get_is_mac_mode()) {
        char line1[3] = { 0x95, 0x96, 0 };
        char line2[3] = { 0xB5, 0xB6, 0 };
        oled_write(line1, false);
        oled_set_cursor(3, row + 1);
        oled_write(line2, false);
    } else {
        char line1[3] = { 0x97, 0x98, 0 };
        char line2[3] = { 0xB7, 0xB8, 0 };
        oled_write(line1, false);
        oled_set_cursor(3, row + 1);
        oled_write(line2, false);
    }

    oled_set_cursor(0, row);
    switch (get_default_layer()) {
        case _QWERTY:
            oled_write_P(PSTR("QR \r"), false);
            oled_write_P(PSTR("TY "), false);
            break;
        case _COLEMAK:
            oled_write_P(PSTR("CL \r"), false);
            oled_write_P(PSTR("MK "), false);
            break;
        default:
            oled_write_P(PSTR("?? \r"), false);
            oled_write_P(PSTR("?? "), false);
    }
}

static void render_left_screen(void) {
    render_time(0);
    render_layer_chevrons(2);
    render_caps_lock(11);
    render_keyboard_base_info(14);
}

void render_right_screen(void) {
    render_time(0);
    render_layer_chevrons(2);
}


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void oled_task_user(void) {
    load_data();

    if (is_keyboard_master()) {
        set_default_layer(get_highest_layer(default_layer_state));
        set_layer(get_highest_layer(layer_state));
        set_is_mac_mode(is_mac_mode);
        set_caps_lock(host_keyboard_led_state().caps_lock);
        send_data();
    }

    if (eeconfig_read_handedness()) {
        render_left_screen();
    } else {
        render_right_screen();
    }
}
