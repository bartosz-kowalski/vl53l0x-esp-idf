#include "i2c.h"
#include "driver/i2c_master.h"

_i2c i2c;

void _i2c::init(int scl, int sda) {

    const gpio_num_t I2C_MASTER_SCL_IO = (gpio_num_t)scl;       /*!< GPIO number used for I2C master clock */
    const gpio_num_t I2C_MASTER_SDA_IO = (gpio_num_t)sda;       /*!< GPIO number used for I2C master data  */
    const i2c_port_t I2C_MASTER_NUM = I2C_NUM_0;            /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
    const int I2C_MASTER_FREQ_HZ = 100000;   /*!< I2C master clock frequency */

    i2c_master_bus_config_t bus_config = {};
    bus_config.i2c_port = I2C_MASTER_NUM,
    bus_config.sda_io_num = I2C_MASTER_SDA_IO,
    bus_config.scl_io_num = I2C_MASTER_SCL_IO,
    bus_config.glitch_ignore_cnt = 7,
    bus_config.intr_priority = 0,
    bus_config.trans_queue_depth = 0,
    bus_config.flags = {
        .enable_internal_pullup = true,
        .allow_pd = false,};

    i2c_device_config_t device_config = {};
    device_config.dev_addr_length = I2C_ADDR_BIT_LEN_7,
    device_config.device_address = 0x29,
    device_config.scl_speed_hz = I2C_MASTER_FREQ_HZ,
    device_config.scl_wait_us = 0,
    device_config.flags = {
        .disable_ack_check = false,};

    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &bus));
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus, &device_config, &sensor));

}

void _i2c::write(uint8_t* data, size_t size) {
    i2c_master_transmit(this->sensor, data, size, 100);
}

void _i2c::write(uint8_t data) {
    i2c_master_transmit(this->sensor, &data, 1, 100);
}

void _i2c::read(uint8_t* data, size_t size) {
    i2c_master_receive(this->sensor, data, size, 100);
}
