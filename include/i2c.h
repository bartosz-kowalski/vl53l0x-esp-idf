#pragma once
#include "driver/i2c_master.h"

class _i2c {
   public:
    void init(int scl = 22, int sda = 21);
    void write(uint8_t data);
    void write(uint8_t* data, size_t size);
    void read(uint8_t* data, size_t size);

   private:
    i2c_master_bus_handle_t bus;
    i2c_master_dev_handle_t sensor;
};

extern _i2c i2c;
