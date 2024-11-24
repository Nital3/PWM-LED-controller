#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/pwm.h"


#define GPIO_ON 1
#define GPIO_OFF 0
#define PWM_GPIO_PIN 14
#define BUTTON_GPIO_PIN 15

#define DIVIDER 10

int main(){

    //Initialize wifi module and turn on LED to indicate program is loaded and working
    cyw43_arch_init();
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, GPIO_ON);


    //Set GPIO 14 pin to PWM mode
    gpio_set_function(PWM_GPIO_PIN, GPIO_FUNC_PWM);

    //Get PWM channel for that pin;
    uint slice_number = pwm_gpio_to_slice_num(PWM_GPIO_PIN);

    //Turn PWM on
    pwm_set_enabled(slice_number, true);

    //Set the PWM wrap point for 2kHz
    int pwm_wrap_point = 62500;
    pwm_set_wrap(slice_number, pwm_wrap_point);


    //Mode_button setup
    stdio_init_all();
    gpio_init(BUTTON_GPIO_PIN);
    gpio_set_dir(BUTTON_GPIO_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_GPIO_PIN);

    
    int set_point = 0;
    int counter = 0;

    for(;;){

        //test button functionality
        if(!gpio_get(BUTTON_GPIO_PIN)){

            //when button pressed: set brightness of LED to 100%
            pwm_set_chan_level(slice_number, PWM_CHAN_A, pwm_wrap_point);

        }
        else{
            
            //if button isnt pressed then set brightness to 0%
            pwm_set_chan_level(slice_number, PWM_CHAN_A, 0);

        }
        sleep_ms(10);
    }

}
