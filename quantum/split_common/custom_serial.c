#include "custom_serial.h"

static uint8_t m2s_data[CUSTOM_SERIAL_M2S_BYTES];
static uint8_t s2m_data[CUSTOM_SERIAL_S2M_BYTES];

void set_custom_serial_data_for_transport(bool is_master, uint8_t* transport_data) {
    if (is_master) {
        memcpy(transport_data, &m2s_data, sizeof(uint8_t) * CUSTOM_SERIAL_M2S_BYTES);
    } else {
        memcpy(transport_data, &s2m_data, sizeof(uint8_t) * CUSTOM_SERIAL_S2M_BYTES);
    }
}

void set_custom_serial_data_from_transport(bool is_master, uint8_t* transport_data) {
    if (is_master) {
        memcpy(&s2m_data, transport_data, sizeof(uint8_t) * CUSTOM_SERIAL_S2M_BYTES);
    } else {
        memcpy(&m2s_data, transport_data, sizeof(uint8_t) * CUSTOM_SERIAL_M2S_BYTES);
    }
}

uint8_t * get_custom_serial_data(bool is_master) {
    if (is_master) {
        return s2m_data;
    } else {
        return m2s_data;
    }
}

void set_custom_serial_data(bool is_master, uint8_t* data) {
    if (is_master) {
        memcpy(&m2s_data, data, sizeof(uint8_t) * CUSTOM_SERIAL_M2S_BYTES);
    } else {
        memcpy(&s2m_data, data, sizeof(uint8_t) * CUSTOM_SERIAL_S2M_BYTES);
    }
}
