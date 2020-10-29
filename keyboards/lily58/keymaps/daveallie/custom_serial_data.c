#include "custom_serial.c"

typedef union {
    uint8_t raw[CUSTOM_SERIAL_M2S_BYTES];
    struct {
        bool is_mac_mode;
        bool caps_lock;
        uint8_t default_layer;
        uint8_t layer;
    };
} master_data_t;
master_data_t master_data;

typedef union {
    uint8_t raw[CUSTOM_SERIAL_S2M_BYTES];
    struct {};
} slave_data_t;
slave_data_t slave_data;

uint8_t get_default_layer(void) {
    return master_data.default_layer;
}

void set_default_layer(uint8_t default_layer) {
    master_data.default_layer = default_layer;
}

uint8_t get_layer(void) {
    return master_data.layer;
}

void set_layer(uint8_t layer) {
    master_data.layer = layer;
}

bool get_is_mac_mode(void) {
    return master_data.is_mac_mode;
}

void set_is_mac_mode(bool is_mac_mode) {
    master_data.is_mac_mode = is_mac_mode;
}

bool get_caps_lock(void) {
    return master_data.caps_lock;
}

void set_caps_lock(bool caps_lock) {
    master_data.caps_lock = caps_lock;
}

void load_data(void) {
    if (is_keyboard_master()) {
        memcpy(slave_data.raw, get_custom_serial_data(true), sizeof(slave_data.raw));
    } else {
        memcpy(master_data.raw, get_custom_serial_data(false), sizeof(master_data.raw));
    }
}

void send_data(void) {
    if (is_keyboard_master()) {
        set_custom_serial_data(true, master_data.raw);
    } else {
        set_custom_serial_data(false, slave_data.raw);
    }
}
