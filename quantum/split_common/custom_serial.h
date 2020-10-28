#pragma once

#include <string.h>
#include <stdbool.h>

void set_custom_serial_data_for_transport(bool is_master, uint8_t* transport_data);
void set_custom_serial_data_from_transport(bool is_master, uint8_t* transport_data);

uint8_t * get_custom_serial_data(bool is_master);
void set_custom_serial_data(bool is_master, uint8_t* data);
