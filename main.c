#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"


#define GPIO_ON 1
#define GPIO_OFF 0


int main(){

    stdio_init_all();
    if(cyw43_arch_init()){
        return -1;
    }


    for(;;){

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, GPIO_ON);
        sleep_ms(1000);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, GPIO_OFF);
        sleep_ms(1000);

    }
}