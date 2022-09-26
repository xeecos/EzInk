#include "key.h"
#include <driver/adc.h>
void key_init()
{
    
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);
//     int val = adc1_get_raw(ADC1_CHANNEL_4);
//     // //USBSerial.printf("%d\n", val);
//     if (val > 3000)
//     {
//         delay(20);
//     }
//     else if (val > 1000)
//     {
//     }
//     else if (val > 500)
//     {
//     }
//     else
//     {
//     }
}
void key_get_raw(int &raw)
{
    raw = adc1_get_raw(ADC1_CHANNEL_4);
}
void key_run()
{

}