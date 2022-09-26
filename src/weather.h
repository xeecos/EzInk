#pragma once
#include <stdint.h>
void weather_init();
void weather_get_realtime(float &temperature, float &humidity, float &pressure);
void weather_data_at(int index,float &temperature, float &humidity, float &pressure);
int weather_total_count();
void weather_run();