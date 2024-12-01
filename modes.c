#include <math.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/pwm.h"
#include "modes.h"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif  


/** \brief Handles interupt button advancing mode to next one and resets the timer
*
*
* \param current_mode_pointer pointer to variable holding current mode id
* \param timer_pointer pointer to timer used in different modes
*/
void switch_mode(int* current_mode_pointer, int* timer_pointer){

    //advance mode by one on interupt, wrap on 6
    if((*current_mode_pointer)<6){
        (*current_mode_pointer)++;
    }
    else{
        (*current_mode_pointer) = 0;
    }


    //resets timer
    (*timer_pointer) = 0;

}








/** \brief Returns channel level for given brightness and pwm wrap point
*
*
* \param brightness_percentage desired brightness level (0-100)
* \param wrap_point wrap point of pwm slice
*/
uint16_t fixed_brightness(int brightness_percentage, int wrap_point){
    return((wrap_point*brightness_percentage)/100);
}



/** \brief Returns channel level for given timer and speed multiplier
*
*
* \param timer_ms timer in miliseconds
* \param speed_multiplier speed cycle multiplier, 1 cycle/s for 1
* \param wrap_point wrap point of pwm slice
*/
uint16_t breathing(int timer_ms, double speed_multiplier, int wrap_point){

    //convert 1000ms scale into 2pi scale
    double t = ((timer_ms*2*M_PI)/1000)*speed_multiplier;

    //calculate channel level
    double y = ((sin(t)+1)*wrap_point)/2;

    //return desired channel level
    return(y);

}



/** \brief Returns channel level for given timer and strobe cycle time
*
*
* \param timer_ms timer in miliseconds
* \param cycle_time lenght of strobe on-off cycle in ms
* \param wrap_point wrap point of pwm slice
*/
uint16_t strobe(int timer_ms, int cycle_time, int wrap_point){

    //get current cycle half return 
    if((timer_ms % cycle_time)<(cycle_time/2)){
        return(wrap_point);
    }
    else{
        return(0);
    }


}