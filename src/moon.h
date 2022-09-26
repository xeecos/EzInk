#pragma once
#include <stdint.h>
void moon_init();
void moon_set_time(long timestamp);
float moon_get_day();
void moon_get_bitmap(int size, uint8_t *bitmap);
void moon_get_rise_and_set(long &risetime, long &settime);