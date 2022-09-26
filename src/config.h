#pragma once
#include <stdint.h>
enum CONFIG_TYPE
{
    CONFIG_LONGITUDE = 0,
    CONFIG_LATTITUDE,
    CONFIG_WIFI_NAME,
    CONFIG_WIFI_PASSWORD,
};
void config_init();
void config_set(CONFIG_TYPE type, float value);
void config_set(CONFIG_TYPE type, long value);
void config_set(CONFIG_TYPE type, char* value, int size);
void config_get(CONFIG_TYPE type, float &value);
void config_get(CONFIG_TYPE type, long &value);
void config_get(CONFIG_TYPE type, char* value, int size);