# Implementação do Protocolo DSHOT300 com ESP32

Este repositório contém a implementação do protocolo DSHOT300 (pode ser adaptado para outras versões do DSHOT) utilizando o periférico RMT do ESP32. Este projeto permite o controle simultâneo de diversos motores com interferência mínima da CPU, uma vez que o periférico RMT é configurado para trabalhar em loop totalmente controlado pelo hardware, enviando os frames DSHOT continuamente até que um novo valor seja definido pelo programa.

## Ferramentas Utilizadas

- **PlatformIO IDE (Core 6.1.15)** no **VSCODE**
- **Framework ESP-IDF (5.2.1)**

O projeto foi baseado no exemplo ["dshot_esc" da Espressif](https://github.com/espressif/esp-idf/tree/master/examples/peripherals/rmt/dshot_esc).

## Como Usar

Para cada motor que você desejar controlar, siga os passos abaixo:

1. Crie uma instância da classe `Rmt_dshot_esc`.
2. Invoque o método `create_rmt_tx_channel` passando como parâmetros os argumentos `RMT_CLK_SRC_DEFAULT`, `PIN_MOTOR_1`, `64`, `DSHOT_ESC_RESOLUTION_HZ`, `10`.
3. Invoque o método `install_dshot_esc_encoder` passando como parâmetros os argumentos `DSHOT_PROTOCOL_HZ`, `DSHOT_PROTOCOL_POST_DELAY_US`.
4. Invoque o método `start_esc` passando como parâmetro o booleano `is_the_last_motor` para que o delay de inicialização seja aplicado a todos os ESCs.
5. Invoque o método `define_throttle` passando como parâmetro a aceleração desejada sempre que desejar (48 <= `uint16_t throttle` <= 2047).

## Exemplo (arquivo `main.cpp`)

```cpp
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
