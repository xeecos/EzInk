/**
 * @file src.ino
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-26
 * 
 * @copyright Copyright (c) 2022
 * 气象页  https://www.52stl.com/wp-content/uploads/52stl.com_hero-wparts.jpg
 * 日期
 * 时间
 * 天气/气温
 * 72小时天气
 * 日出日落时间 月相  月出月落时间
 * 实时数据页
 * 温度曲线
 * 湿度曲线
 * 气压曲线
 * 观星指数页
 * 指数  月相
 * 天气 湿度  温度  风速
 * 光污染等级
 * 无月时间
 * 银河时间
 */
#include <Arduino.h>
HWCDC USBSerial;
void setup()
{
    delay(1000);
    USBSerial.begin(115200);
    delay(1000);

}
void loop()
{
}