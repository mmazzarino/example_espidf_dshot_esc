#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/rmt_tx.h"
#include "dshot_esc_encoder.h"


class Rmt_dshot_esc {
    /*    EXAMPLE OF USAGE:
     *
     *    Rmt_dshot_esc motor_1;
     *    Rmt_dshot_esc motor_2;
     *    Rmt_dshot_esc motor_3;
     *    Rmt_dshot_esc motor_4;
     *
     *    motor_1.create_rmt_tx_channel(RMT_CLK_SRC_DEFAULT, PIN_MOTOR_1, 64, DSHOT_ESC_RESOLUTION_HZ, 10);
     *    motor_2.create_rmt_tx_channel(RMT_CLK_SRC_DEFAULT, PIN_MOTOR_2, 64, DSHOT_ESC_RESOLUTION_HZ, 10);   
     *    motor_3.create_rmt_tx_channel(RMT_CLK_SRC_DEFAULT, PIN_MOTOR_3, 64, DSHOT_ESC_RESOLUTION_HZ, 10);
     *    motor_4.create_rmt_tx_channel(RMT_CLK_SRC_DEFAULT, PIN_MOTOR_4, 64, DSHOT_ESC_RESOLUTION_HZ, 10);
     *
     *    motor_1.install_dshot_esc_encoder(300000, 50);
     *    motor_2.install_dshot_esc_encoder(300000, 50);
     *    motor_3.install_dshot_esc_encoder(300000, 50);
     *    motor_4.install_dshot_esc_encoder(300000, 50);
     *
     *    motor_1.start_esc(false);
     *    motor_2.start_esc(false);
     *    motor_3.start_esc(false);
     *    motor_4.start_esc(true);    // is_the_last_motor = true
     *
     *    for (uint16_t thro = 70; thro < 200; thro += 10) {
     *        motor_1.define_throttle((uint16_t) thro);
     *        motor_2.define_throttle((uint16_t) thro);
     *        motor_3.define_throttle((uint16_t) thro);
     *        motor_4.define_throttle((uint16_t) thro);
     *        vTaskDelay(pdMS_TO_TICKS(1000));
     *    }
     */

    public:
        Rmt_dshot_esc();
        // ~Rmt_dshot_esc();
        void create_rmt_tx_channel(rmt_clock_source_t rmt_clk_src, gpio_num_t pin_dshot, size_t mem_block_symbols, uint32_t dshot_esc_resolution_hz, size_t trans_queue_depth);
        void install_dshot_esc_encoder(uint32_t dshot_protocol_hz, uint32_t post_delay_us);
        void start_esc(bool is_the_last_motor);
        void define_throttle(uint16_t throttle_value);

    private:
        rmt_channel_handle_t esc_chan = NULL;
        rmt_tx_channel_config_t tx_chan_config;    
        rmt_encoder_handle_t dshot_encoder = NULL;
        dshot_esc_encoder_config_t encoder_config;
        rmt_transmit_config_t tx_config;
        dshot_esc_throttle_t throttle;
};