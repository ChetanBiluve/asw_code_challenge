#ifndef I2C_HEADER_H
#define I2C_HEADER_H

#include <stdint.h>

typedef enum {
    STATUS_OK,
    STATUS_ERROR
} status_t;

status_t i2c_read(
    uint8_t bus_address,
    uint8_t register_address,
    uint16_t length,
    uint8_t *buffer);

status_t i2c_write(
    uint8_t bus_address,
    uint8_t register_address,
    uint16_t length,
    uint8_t *buffer);

#endif
