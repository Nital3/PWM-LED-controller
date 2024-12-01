#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/pwm.h"
#include "modes.h"


#define GPIO_ON 1
#define GPIO_OFF 0
#define PWM_GPIO_PIN 14
#define BUTTON_GPIO_PIN 15
#define WRAP_POINT_2KHZ 62500


    //Set initial vales for variables
    int mode = 0;
    int timer_ms = 0;
    int debounce_timer_ms = 0;


    //Irq callback handler
    void button_callback_handler(uint gpio, uint32_t event){

        //switch mode
        if(debounce_timer_ms == 0){
            switch_mode(&mode, &timer_ms);
        }
        debounce_timer_ms = 300;
    }

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
    pwm_set_wrap(slice_number, WRAP_POINT_2KHZ);




    //Mode_button setup
    stdio_init_all();
    gpio_init(BUTTON_GPIO_PIN);
    gpio_set_dir(BUTTON_GPIO_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_GPIO_PIN);


    //turn on irq on button
    gpio_set_irq_enabled_with_callback(BUTTON_GPIO_PIN, GPIO_IRQ_EDGE_FALL, true, button_callback_handler);




    for(;;){

        switch (mode){

        case 0: //Brightness 0%
            pwm_set_chan_level(slice_number, PWM_CHAN_A, fixed_brightness(0, WRAP_POINT_2KHZ));
            break;

        case 1: //Brightness 25%
            pwm_set_chan_level(slice_number, PWM_CHAN_A, fixed_brightness(25, WRAP_POINT_2KHZ));
            break;

        case 2: //Brightness 50%
            pwm_set_chan_level(slice_number, PWM_CHAN_A, fixed_brightness(50, WRAP_POINT_2KHZ));
            break;

        case 3: //Brightness 100%
            pwm_set_chan_level(slice_number, PWM_CHAN_A, fixed_brightness(100, WRAP_POINT_2KHZ));
            break;

        case 4: //Breathing normal
            pwm_set_chan_level(slice_number, PWM_CHAN_A, breathing(timer_ms, 1, WRAP_POINT_2KHZ));
            break;
            
        case 5: //Breathing slow
            pwm_set_chan_level(slice_number, PWM_CHAN_A, breathing(timer_ms, 0.2f, WRAP_POINT_2KHZ));
            break;

        case 6: //Strobe
            pwm_set_chan_level(slice_number, PWM_CHAN_A, strobe(timer_ms, 50, WRAP_POINT_2KHZ));
            break;

        default:
            break;

        }

        //progress timer with wrap
        sleep_ms(1);
        if(timer_ms<5000){
            timer_ms++;
        }
        else{
            timer_ms = 0;
        }
        
        if(debounce_timer_ms>0){
            debounce_timer_ms--;
        }

    }    

}
