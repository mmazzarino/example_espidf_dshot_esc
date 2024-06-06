#include "Rmt_dshot_esc.h"


Rmt_dshot_esc::Rmt_dshot_esc() {
    tx_config.loop_count = -1;       // infinite loop
    throttle.throttle = 0;           // start with zero throttle
    throttle.telemetry_req = false;  // telemetry is not supported in this class
}


// Rmt_dshot_esc::~Rmt_dshot_esc() {
//     // TODO write destructor
// }


void Rmt_dshot_esc::create_rmt_tx_channel(rmt_clock_source_t rmt_clk_src, gpio_num_t pin_dshot, size_t mem_block_symbols, uint32_t dshot_esc_resolution_hz, size_t trans_queue_depth) {
    ESP_LOGI("classe Rmt_dshot_esc", "Create RMT TX channel");

    tx_chan_config.clk_src = rmt_clk_src;
    tx_chan_config.gpio_num = pin_dshot;
    tx_chan_config.mem_block_symbols = mem_block_symbols;
    tx_chan_config.resolution_hz = dshot_esc_resolution_hz;
    tx_chan_config.trans_queue_depth = trans_queue_depth;
    
    ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_chan_config, &esc_chan));
}


void Rmt_dshot_esc::install_dshot_esc_encoder(uint32_t dshot_protocol_hz, uint32_t post_delay_us) {
    ESP_LOGI("classe Rmt_dshot_esc", "Install Dshot ESC encoder");

    encoder_config.resolution = tx_chan_config.resolution_hz;
    encoder_config.baud_rate = dshot_protocol_hz;
    encoder_config.post_delay_us = post_delay_us;

    ESP_ERROR_CHECK(rmt_new_dshot_esc_encoder(&encoder_config, &dshot_encoder));
}


void Rmt_dshot_esc::start_esc(bool is_the_last_motor) {
    ESP_LOGI("classe Rmt_dshot_esc", "Enable RMT TX channel and start ESC by sending zero throttle for a while...");
    
    ESP_ERROR_CHECK(rmt_enable(esc_chan));
    ESP_ERROR_CHECK(rmt_transmit(esc_chan, dshot_encoder, &throttle, sizeof(throttle), &tx_config));
    
    if (is_the_last_motor) vTaskDelay(pdMS_TO_TICKS(5000));
}


void Rmt_dshot_esc::define_throttle(uint16_t throttle_value) {
    throttle.throttle = throttle_value;

    (rmt_transmit(esc_chan, dshot_encoder, &throttle, sizeof(throttle), &tx_config));

    // the previous loop transfer is till undergoing, we need to stop it and restart,
    // so that the new throttle can be updated on the output
    ESP_ERROR_CHECK(rmt_disable(esc_chan));
    ESP_ERROR_CHECK(rmt_enable(esc_chan));
}

