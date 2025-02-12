#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Definições para o PWM
#define SERVO_PIN 22
#define LED_PIN 12
#define PWM_FREQ 50  // 50Hz = período de 20ms
#define WRAP_COUNT 62500  // Para obter 50Hz com clock de 125MHz

// Função para configurar o PWM
void pwm_setup(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint channel = pwm_gpio_to_channel(pin);
    
    // Configurar o PWM para 50Hz
    pwm_set_wrap(slice_num, WRAP_COUNT);
    pwm_set_clkdiv(slice_num, 40.0f);  // Clock divisor para obter 50Hz
    pwm_set_enabled(slice_num, true);
}

// Função para converter microssegundos em valor PWM
uint16_t us_to_pwm(float us) {
    return (uint16_t)((us / 20000.0f) * WRAP_COUNT);
}

// Função para mover o servomoto suavemente, para evitar movimentos bruscos
void move_servo_smooth(uint slice_num, uint16_t start_us, uint16_t end_us) {
    int step = (start_us < end_us) ? 5 : -5;
    
    for (int us = start_us; 
         (step > 0) ? (us <= end_us) : (us >= end_us); 
         us += step) {
        pwm_set_chan_level(slice_num, PWM_CHAN_A, us_to_pwm(us));
        sleep_ms(10);  // Atraso de 10ms para movimento suave
    }
}

int main() {
    stdio_init_all();
    
    // Configura PWM para o servo
    pwm_setup(SERVO_PIN);
    uint servo_slice = pwm_gpio_to_slice_num(SERVO_PIN);
    
    // Configura PWM para o LED RGB
    pwm_setup(LED_PIN);
    uint led_slice = pwm_gpio_to_slice_num(LED_PIN);
    
    while (true) {
        // Move para 180 graus (2400µs)
        pwm_set_chan_level(servo_slice, PWM_CHAN_A, us_to_pwm(2400));
        pwm_set_chan_level(led_slice, PWM_CHAN_A, us_to_pwm(2400));
        sleep_ms(5000);
        
        // Move para 90 graus (1470µs)
        pwm_set_chan_level(servo_slice, PWM_CHAN_A, us_to_pwm(1470));
        pwm_set_chan_level(led_slice, PWM_CHAN_A, us_to_pwm(1470));
        sleep_ms(5000);
        
        // Move para 0 graus (500µs)
        pwm_set_chan_level(servo_slice, PWM_CHAN_A, us_to_pwm(500));
        pwm_set_chan_level(led_slice, PWM_CHAN_A, us_to_pwm(500));
        sleep_ms(5000);
        
        // Movimento suave de 0 a 180 graus
        move_servo_smooth(servo_slice, 500, 2400);  // movimento inicial de 0° -> 180°
        sleep_ms(1000);
        move_servo_smooth(servo_slice, 2400, 500);  // movimento final de 180° -> 0°
        sleep_ms(1000);
    }
    
    return 0;
}