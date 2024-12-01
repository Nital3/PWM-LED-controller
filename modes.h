#ifndef MODES_H
#define MODES_H

const inline void switch_mode(int* current_mode_pointer, int* timer_pointer);
const inline uint16_t fixed_brightness(int brightness_percentage, int wrap_point);
const inline uint16_t breathing(int timer_ms, double speed_multiplier, int wrap_point);
const inline uint16_t strobe(int timer_ms, int cycle_time, int wrap_point);



#endif