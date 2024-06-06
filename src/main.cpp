#include "esp_log.h"
#include "Rmt_dshot_esc.h"

#define DSHOT_ESC_RESOLUTION_HZ 40000000
#define DSHOT_PROTOCOL_HZ 300000
#define DSHOT_PROTOCOL_POST_DELAY_US 50
#define PIN_MOTOR_1 GPIO_NUM_25             // marrom
#define PIN_MOTOR_2 GPIO_NUM_26             // branco
#define PIN_MOTOR_3 GPIO_NUM_15             // cinza
#define PIN_MOTOR_4 GPIO_NUM_2              // roxo 


extern "C" void app_main(void) {

    Rmt_dshot_esc motor_1;
    Rmt_dshot_esc motor_2;
    Rmt_dshot_esc motor_3;
    Rmt_dshot_esc motor_4;

    motor_1.create_rmt_tx_channel(RMT_CLK_SRC_DEFAULT, PIN_MOTOR_1, 64, DSHOT_ESC_RESOLUTION_HZ, 10);
    motor_2.create_rmt_tx_channel(RMT_CLK_SRC_DEFAULT, PIN_MOTOR_2, 64, DSHOT_ESC_RESOLUTION_HZ, 10);   
    motor_3.create_rmt_tx_channel(RMT_CLK_SRC_DEFAULT, PIN_MOTOR_3, 64, DSHOT_ESC_RESOLUTION_HZ, 10);
    motor_4.create_rmt_tx_channel(RMT_CLK_SRC_DEFAULT, PIN_MOTOR_4, 64, DSHOT_ESC_RESOLUTION_HZ, 10);

    motor_1.install_dshot_esc_encoder(DSHOT_PROTOCOL_HZ, DSHOT_PROTOCOL_POST_DELAY_US);
    motor_2.install_dshot_esc_encoder(DSHOT_PROTOCOL_HZ, DSHOT_PROTOCOL_POST_DELAY_US);
    motor_3.install_dshot_esc_encoder(DSHOT_PROTOCOL_HZ, DSHOT_PROTOCOL_POST_DELAY_US);
    motor_4.install_dshot_esc_encoder(DSHOT_PROTOCOL_HZ, DSHOT_PROTOCOL_POST_DELAY_US);

    motor_1.start_esc(false);
    motor_2.start_esc(false);
    motor_3.start_esc(false);
    motor_4.start_esc(true);

    for (uint16_t thro = 70; thro < 200; thro += 10) {
        motor_1.define_throttle((uint16_t) thro);
        motor_2.define_throttle((uint16_t) thro);
        motor_3.define_throttle((uint16_t) thro);
        motor_4.define_throttle((uint16_t) thro);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
