// tb6612.c

/*
2 PWMA    PWM A channel
6 AIN2    input 2 A chan
7 AIN1    input 1 A chan
STBY    standby
8 BIN1    input 1 B chan
9 BIN2    input 2 B chan
3 PWMB    PWM B channel
GND     logic ground
VCC     logic source voltage
Vmotor
MOT A
GND
MOT B
*/

/*  IN1 IN2
    H   H   short brake
    L   H   CCW
    H   L   CW
    L   L   stop
*/

//#include <bits/types.h>
#ifndef __unused
#define __unused __attribute__((unused))
#endif

#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "pico/printf.h"
#include "hardware/pwm.h"

// motor driver inputs AIN1,AIN2,BIN1,BIN2
// pins
#define PWMA 3
#define AIN1 7
#define AIN2 6
#define PWMB 2
#define BIN1 8
#define BIN2 9

// set up GPIO pins for motor driver inputs
static const uint32_t gpio_mask = 1 << AIN1 | 1 << AIN2 | 1 << BIN1 | 1 << BIN2;
static const uint32_t forward = 1 << AIN2 | 1 << BIN2;
static const uint32_t reverse = 1 << AIN1 | 1 << BIN1;
static const uint32_t left = 1 << AIN2 | 1 << BIN1;
static const uint32_t right = 1 << AIN1 | 1 << BIN2;

typedef enum {
    STOP,
    FORWARD,
    REVERSE,
    LEFT,
    RIGHT
} motion_t;

volatile motion_t current_motor_command = STOP;

// PWM
const uint16_t set_duty = 80;
uint slice_num1;
uint slice_num2;

// function prototypes
uint setup_pwm(uint gpio, uint duty);
void motor_control(motion_t current_motor_command);

// rotate motors
int main() {

    stdio_init_all();
    sleep_ms(1000);
    printf("LD293D demo\n");

    gpio_init_mask(gpio_mask);
    gpio_set_dir_out_masked(gpio_mask);
    gpio_put_masked(gpio_mask, 0);

    // configure pwm output for LD293D enable pins
    slice_num1 = setup_pwm(PWMA, set_duty);
    slice_num2 = setup_pwm(PWMB, set_duty);

    while(1) {

        // buggy forward
        printf("forward 2s\n");
        motor_control(FORWARD);
        sleep_ms(2000);

        // stop
        printf("stop .5s 1\n");
        motor_control(STOP);
        sleep_ms(500);
    
    /**********************************
        // buggy left
        printf("left 2s\n");
        motor_control(LEFT);
        sleep_ms(2000);

        // stop
        printf("stop .5s 2\n");
        motor_control(STOP);
        sleep_ms(500);

        // buggy right
        printf("right 2s\n");
        motor_control(RIGHT);
        sleep_ms(2000);

        // stop
        printf("stop .5s 3\n");
        motor_control(STOP);
        sleep_ms(500);
    
    *********************************************/
        // buggy reverse
        printf("reverse 2s\n");
        motor_control(REVERSE);
        sleep_ms(2000);

        // stop
        printf("stop .5s 4\n");
        motor_control(STOP);
        sleep_ms(500);
    }

    return 0;
}

// set up pwm function
uint setup_pwm(uint gpio, uint duty) {
    gpio_set_function(gpio, GPIO_FUNC_PWM); // Set the Pico GP pin to PWM function
    uint slice_num = pwm_gpio_to_slice_num(gpio); // Get the PWM slice number
    pwm_config config = pwm_get_default_config(); // Get a set of default values for PWM configuration
    pwm_config_set_clkdiv(&config, 4.0f); // Adjust based on Pico’s default clock
    pwm_init(slice_num, &config, false); // Initialize the PWM with the default config
    pwm_set_wrap(slice_num, 9999); // 25 kHz
    pwm_set_gpio_level(gpio, 12500 * duty / 100);  // duty cycle
    return slice_num;
}

// motor control
void motor_control(motion_t current_motor_command) {
    motion_t cmd = current_motor_command;
    switch (cmd) {
        case FORWARD:
            pwm_set_enabled(slice_num1, true);
            pwm_set_enabled(slice_num2, true);
            gpio_put_masked(gpio_mask, forward);
            break;
        case REVERSE:
            pwm_set_enabled(slice_num1, true);
            pwm_set_enabled(slice_num2, true);
            gpio_put_masked(gpio_mask, reverse);
            break;
        case LEFT:
            pwm_set_enabled(slice_num1, true);
            pwm_set_enabled(slice_num2, true);
            gpio_put_masked(gpio_mask, left);
            break;
        case RIGHT:
            pwm_set_enabled(slice_num1, true);
            pwm_set_enabled(slice_num2, true);
            gpio_put_masked(gpio_mask, right);
            break;
        case STOP:
            pwm_set_enabled(slice_num1, false);
            pwm_set_enabled(slice_num2, false);
            gpio_put_masked(gpio_mask, 0);
            break;
        default:
            pwm_set_enabled(slice_num1, false);
            pwm_set_enabled(slice_num2, false);
            gpio_put_masked(gpio_mask, 0);
            break;
    }
}

/*
uint setup_pwm(uint gpio, uint duty) {
    gpio_set_function(gpio, GPIO_FUNC_PWM); // Set the Pico GP pin to PWM function
    uint slice_num = pwm_gpio_to_slice_num(gpio); // Get the PWM slice number

    pwm_config config = pwm_get_default_config(); // Get a set of default values for PWM configuration

    // Set the clock divider to achieve 500 Hz
    //pwm_config_set_clkdiv(&config, (float)clock_get_hz(clk_sys) / 500.0f / 1000.0f);  // 500 Hz frequency
    pwm_config_set_clkdiv(&config, 250.0f);  // 125 MHz system clock / 250 = 500 Hz

    pwm_init(slice_num, &config, false); // Initialize the PWM with the default config

    // Set the wrap value to match the frequency, 500 Hz -> 2000 cycles
    pwm_set_wrap(slice_num, 2000 - 1); // Wrap value for 500 Hz

    // Set the duty cycle (duty is a value between 0 and 100)
    pwm_set_gpio_level(gpio, 2000 * duty / 100); // Duty cycle scaling

    return slice_num;
}
*/
/*
uint setup_pwm(uint gpio, uint duty) {
    gpio_set_function(gpio, GPIO_FUNC_PWM); // Set the Pico GP pin to PWM function
    uint slice_num = pwm_gpio_to_slice_num(gpio); // Get the PWM slice number

    pwm_config config = pwm_get_default_config(); // Get a set of default values for PWM configuration

    // Set the clock divider for 25 Hz frequency (125 MHz / 25 Hz / 1000)
    pwm_config_set_clkdiv(&config, 5000.0f);  // 125 MHz system clock / 5000 = 25 Hz

    pwm_init(slice_num, &config, false); // Initialize the PWM with the default config

    // Set the wrap value to match the frequency, 25 Hz -> 5000 cycles
    pwm_set_wrap(slice_num, 5000 - 1); // Wrap value for 25 Hz

    // Set the duty cycle (duty is a value between 0 and 100)
    pwm_set_gpio_level(gpio, 5000 * duty / 100); // Duty cycle scaling

    return slice_num;
}
*/

