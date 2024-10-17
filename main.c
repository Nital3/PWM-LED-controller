#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/pwm.h"


#define GPIO_ON 1
#define GPIO_OFF 0
#define PWM_GPIO_PIN 0


int main(){

    //Initialize wifi module and turn on LED to indicate program is loaded and working
    cyw43_arch_init();
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, GPIO_ON);


    //Set GPIO 0 pin to PWM mode
    gpio_set_function(PWM_GPIO_PIN, GPIO_FUNC_PWM);

    //Get PWM chanell for that pin;
    uint slice_number = pwm_gpio_to_slice_num(PWM_GPIO_PIN);

    //Turn PWM on
    pwm_set_enabled(slice_number, true);

    //Set the PWM wrap point for 2kHz
    int pwm_wrap_point = 65000;
    pwm_set_wrap(slice_number, pwm_wrap_point);

    
    int set_point = 0;
    float brightness_percentage = 0;


    for(;;){

        //set the set point
        pwm_set_chan_level(slice_number, PWM_CHAN_A, (pwm_wrap_point*brightness_percentage));
        sleep_ms(1000);

        for(;;){

            brightness_percentage += 0.1;

            if (brightness_percentage>1){

                brightness_percentage = 0;

            }

        }

    }

}