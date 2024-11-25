#ifndef MODES_H
#define MODES_H

uint16_t fixed_brightness(int brightness_percentage, int wrap_point);
uint16_t breathing(int timer_ms, double speed_multiplier, int wrap_point);
uint16_t strobe(int timer_ms, int cycle_time, int wrap_point);


#endif