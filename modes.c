#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/pwm.h"
#include "modes.h"

/** \brief Returns chanell level for given brightness and pwm wrap point
*
*
* \param brightness_percentage desired brightness level (0-100)
* \param wrap_point wrap point of pwm slice
*/
uint16_t fixed_brightness(int brightness_percentage, int wrap_point){
    return((wrap_point*brightness_percentage)/100);
}