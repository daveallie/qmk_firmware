#include <stdio.h>
#include "custom_serial.c"

typedef union {
    uint8_t raw[CUSTOM_SERIAL_M2S_BYTES];
    struct {
        bool is_mac_mode      : 1;
        bool caps_lock        : 1;
        bool time_set         : 1;
        bool alert_count_set  : 1;
        uint8_t default_layer : 4;
        uint8_t layer         : 4;
        uint8_t hours         : 8;
        uint8_t minutes       : 8;
        uint8_t alert_count   : 8;
    };
} master_data_t;
master_data_t master_data;

typedef union {
    uint8_t raw[CUSTOM_SERIAL_S2M_BYTES];
    struct {};
} slave_data_t;
slave_data_t slave_data;

char time_string[6];
char alert_count_string[4];

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

bool is_time_set(void) {
    return master_data.time_set;
}

char* get_time_string(void) {
    if (master_data.time_set) {
        snprintf(time_string, sizeof(time_string), "%2d:%02d", master_data.hours % 100, master_data.minutes % 100);
    }

    return time_string;
}

void set_time(uint8_t hours, uint8_t minutes) {
    master_data.hours = hours;
    master_data.minutes = minutes;
    master_data.time_set = true;
}

bool is_alert_count_set(void) {
    return master_data.alert_count_set;
}

char* get_alert_count_string(void) {
    if (master_data.alert_count_set) {
        snprintf(alert_count_string, sizeof(alert_count_string), "%d", master_data.alert_count);
    }

    return alert_count_string;
}

uint8_t get_alert_count(void) {
    return master_data.alert_count;
}

void set_alert_count(uint8_t alert_count) {
    master_data.alert_count = alert_count;
    master_data.alert_count_set = true;
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
