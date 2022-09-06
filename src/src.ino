/**
 *  @filename   :   epd1in54-demo.ino
 *  @brief      :   1.54inch e-paper display demo
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     September 5 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <SPI.h>
#include "epd1in54.h"
#include "epdpaint.h"
#include "imagedata.h"

#define COLORED 0
#define UNCOLORED 1

//  adc1_config_width(ADC_WIDTH_BIT_12);
//  adc1_config_channel_atten(ADC1_CHANNEL_4,ADC_ATTEN_DB_11);
//  int val = adc1_get_raw(ADC1_CHANNEL_4);
//  USBSerial.printf("%d\n",val);
//  delay(500);
/**
 * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
 * In this case, a smaller image buffer is allocated and you have to
 * update a partial display several times.
 * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
 */
unsigned char image[1024];
Paint paint(image, 0, 0); // width should be the multiple of 8
Epd epd;
unsigned long time_start_ms;
unsigned long time_now_s;

HWCDC USBSerial;
void setup()
{
    // put your setup code here, to run once:
    USBSerial.begin(115200);
    USBSerial.print("e-Paper init ");

    if (epd.Init(lut_partial_update) != 0) {
        USBSerial.print("e-Paper init failed");
        return;
    }
    else
    {
    USBSerial.print("e-Paper init success");
    }

    /**
     *  there are 2 memory areas embedded in the e-paper display
     *  and once the display is refreshed, the memory area will be auto-toggled,
     *  i.e. the next action of SetFrameMemory will set the other memory area
     *  therefore you have to clear the frame memory twice.
     */
    epd.ClearFrameMemory(0xFF); // bit set = white, bit reset = black
    epd.DisplayFrame();
    epd.ClearFrameMemory(0xFF); // bit set = white, bit reset = black
    epd.DisplayFrame();


    // paint.SetRotate(ROTATE_90);
    // paint.SetWidth(200);
    // paint.SetHeight(24);

    // /* For simplicity, the arguments are explicit numerical coordinates */
    // paint.Clear(COLORED);
    // paint.DrawStringAt(30, 4, "Hello world!", &Font16, UNCOLORED);
    // epd.SetFrameMemory(paint.GetImage(), 0, 10, paint.GetWidth(), paint.GetHeight());

    // paint.Clear(UNCOLORED);
    // paint.DrawStringAt(30, 4, "e-Paper Demo", &Font16, COLORED);
    // epd.SetFrameMemory(paint.GetImage(), 0, 30, paint.GetWidth(), paint.GetHeight());

    // paint.SetWidth(64);
    // paint.SetHeight(64);

    // paint.Clear(UNCOLORED);
    // paint.DrawRectangle(0, 0, 40, 50, COLORED);
    // paint.DrawLine(0, 0, 40, 50, COLORED);
    // paint.DrawLine(40, 0, 0, 50, COLORED);
    // epd.SetFrameMemory(paint.GetImage(), 16, 60, paint.GetWidth(), paint.GetHeight());

    // paint.Clear(UNCOLORED);
    // paint.DrawCircle(32, 32, 30, COLORED);
    // epd.SetFrameMemory(paint.GetImage(), 120, 60, paint.GetWidth(), paint.GetHeight());

    // paint.Clear(UNCOLORED);
    // paint.DrawFilledRectangle(0, 0, 40, 50, COLORED);
    // epd.SetFrameMemory(paint.GetImage(), 16, 130, paint.GetWidth(), paint.GetHeight());

    // paint.Clear(UNCOLORED);
    // paint.DrawFilledCircle(32, 32, 30, COLORED);
    // epd.SetFrameMemory(paint.GetImage(), 120, 130, paint.GetWidth(), paint.GetHeight());
    // epd.DisplayFrame();

    // /**
    //  *  there are 2 memory areas embedded in the e-paper display
    //  *  and once the display is refreshed, the memory area will be auto-toggled,
    //  *  i.e. the next action of SetFrameMemory will set the other memory area
    //  *  therefore you have to set the frame memory and refresh the display twice.
    //  */
    // epd.SetFrameMemory(IMAGE_DATA);
    // epd.DisplayFrame();
    // epd.SetFrameMemory(IMAGE_DATA);
    // epd.DisplayFrame();

    // epd.ClearFrameMemory(0xFF); // bit set = white, bit reset = black
    // epd.DisplayFrame();
    // epd.ClearFrameMemory(0xFF); // bit set = white, bit reset = black
    // epd.DisplayFrame();
    time_start_ms = millis();
    // epd.Sleep();
}


void loop()
{
    // put your main code here, to run repeatedly:
     time_now_s = (millis() - time_start_ms) / 1000;
     char time_string[] = {'0', '0', ':', '0', '0', '\0'};
     time_string[0] = time_now_s / 60 / 10 + '0';
     time_string[1] = time_now_s / 60 % 10 + '0';
     time_string[3] = time_now_s % 60 / 10 + '0';
     time_string[4] = time_now_s % 60 % 10 + '0';

     paint.SetWidth(96);
     paint.SetHeight(32);
     paint.SetRotate(ROTATE_0);

     paint.Clear(UNCOLORED);
    //  paint.DrawStringAt(0, 4, time_string, &Font24, COLORED);
    //  paint.DrawHanzi(0, 4, "我", COLORED);
    //  paint.DrawHanzi(16, 4, "们", COLORED);
     paint.DrawHanzi(0, 4, "我", COLORED);
     paint.DrawHanzi(20, 4, "国", COLORED);
     epd.SetFrameMemory(paint.GetImage(), 80, 72, paint.GetWidth(), paint.GetHeight());
     epd.DisplayFrame();

}