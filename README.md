# DSHOT300 Protocol Implementation with ESP32

This repository contains the implementation of the DSHOT300 protocol (adaptable to other DSHOT versions) using the RMT peripheral of the ESP32. This project allows simultaneous control of multiple motors with minimal CPU interference, as the RMT peripheral is configured to operate in a hardware-controlled loop, continuously sending DSHOT frames until a new value is set by the software.

## Tools Used

- **PlatformIO IDE (Core 6.1.15)** on **VSCode**
- **ESP-IDF Framework (5.2.1)**

This project is based on the ["dshot_esc" example by Espressif](https://github.com/espressif/esp-idf/tree/master/examples/peripherals/rmt/dshot_esc).

## Usage Instructions

To control each motor, follow these steps:

1. Create an instance of the `Rmt_dshot_esc` class.
2. Call the `create_rmt_tx_channel` method, passing the following parameters:
   - `RMT_CLK_SRC_DEFAULT`
   - Motor pin (`PIN_MOTOR_X`)
   - `64`
   - `DSHOT_ESC_RESOLUTION_HZ`
   - `10`
3. Call the `install_dshot_esc_encoder` method, passing the following parameters:
   - `DSHOT_PROTOCOL_HZ`
   - `DSHOT_PROTOCOL_POST_DELAY_US`
4. Call the `start_esc` method, passing the boolean parameter `is_the_last_motor` to apply the initialization delay to all ESCs.
5. Call the `define_throttle` method, passing the desired throttle value whenever needed (48 <= `uint16_t throttle` <= 2047).

## Example (main.cpp file)

```cpp
#include "Rmt_dshot_esc.h"

// Creating motor instances
Rmt_dshot_esc motor_1;
Rmt_dshot_esc motor_2;
Rmt_dshot_esc motor_3;
Rmt_dshot_esc motor_4;

void setup() {
    // Configuring RMT channels for each motor
    motor_1.create_rmt_tx_channel(RMT_CLK_SRC_DEFAULT, PIN_MOTOR_1, 64, DSHOT_ESC_RESOLUTION_HZ, 10);
    motor_2.create_rmt_tx_channel(RMT_CLK_SRC_DEFAULT, PIN_MOTOR_2, 64, DSHOT_ESC_RESOLUTION_HZ, 10);   
    motor_3.create_rmt_tx_channel(RMT_CLK_SRC_DEFAULT, PIN_MOTOR_3, 64, DSHOT_ESC_RESOLUTION_HZ, 10);
    motor_4.create_rmt_tx_channel(RMT_CLK_SRC_DEFAULT, PIN_MOTOR_4, 64, DSHOT_ESC_RESOLUTION_HZ, 10);

    // Installing DSHOT encoders
    motor_1.install_dshot_esc_encoder(DSHOT_PROTOCOL_HZ, DSHOT_PROTOCOL_POST_DELAY_US);
    motor_2.install_dshot_esc_encoder(DSHOT_PROTOCOL_HZ, DSHOT_PROTOCOL_POST_DELAY_US);
    motor_3.install_dshot_esc_encoder(DSHOT_PROTOCOL_HZ, DSHOT_PROTOCOL_POST_DELAY_US);
    motor_4.install_dshot_esc_encoder(DSHOT_PROTOCOL_HZ, DSHOT_PROTOCOL_POST_DELAY_US);

    // Starting ESCs
    motor_1.start_esc(false);
    motor_2.start_esc(false);
    motor_3.start_esc(false);
    motor_4.start_esc(true);
}

void loop() {
    // Varying motor throttle
    for (uint16_t throttle = 70; throttle < 200; throttle += 10) {
        motor_1.define_throttle(throttle);
        motor_2.define_throttle(throttle);
        motor_3.define_throttle(throttle);
        motor_4.define_throttle(throttle);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
