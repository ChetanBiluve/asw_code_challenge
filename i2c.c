#include "i2c.h"

#include <stdint.h>
#include <stdio.h>

status_t i2c_read(
    uint8_t bus_address,
    uint8_t register_address,
    uint16_t length,
    uint8_t *buffer)
{
    printf(
        "read [%d] bytes from bus [%d] for register [%d]\n",
        length,
        bus_address,
        register_address);

    /* Setting the output to some arbitrary value */
    for (size_t i = 0; i < length; ++i) {
        buffer[i] = 0xff;
    }

    return STATUS_OK;
}

status_t i2c_write(
    uint8_t bus_address,
    uint8_t register_address,
    uint16_t length,
    uint8_t *buffer)
{
    printf(
        "write [%d] bytes to bus [%d] for register [%d]\n\t",
        length,
        bus_address,
        register_address);

    for (size_t i = 0; i < length; ++i) {
        printf("%p", buffer);
    }
    printf("\n");
    return STATUS_OK;
}
