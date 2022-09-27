#include "display.h"

#include <SPI.h>
#include "epd1in54.h"
#include "epdpaint.h"
#include <cppsrc/U8g2lib.h>
#define COLORED 0
#define UNCOLORED 1
// U8G2_NULL u8g2(U8G2_R0);

// unsigned char image[200 * 200];
// Paint paint(image, 0, 0); // width should be the multiple of 8
// Epd epd;
// USBSerial.println("e-Paper start");
// if (epd.Init(lut_partial_update) != 0)
// {
//     USBSerial.println("e-Paper init failed");
//     return;
// }
// else
// {
//     USBSerial.println("e-Paper init success");
// }
// epd.ClearFrameMemory(0xFF); // bit set = white, bit reset = black
// epd.DisplayFrame();
// epd.ClearFrameMemory(0xFF); // bit set = white, bit reset = black
// epd.DisplayFrame();

// paint.SetWidth(200);
// paint.SetHeight(200);
// paint.SetRotate(ROTATE_0);
// paint.Clear(UNCOLORED);
// int x = 0, y = 0, width = 200, height = 200;

// u8g2.initDisplay();
// u8g2.clearDisplay();
// u8g2.setPowerSave(0);

// u8g2.setFont(u8g2_font_ncenB14_tr);
// u8g2.drawStr(50, 20, "Hello");
// uint8_t *buf = u8g2.getBufferPtr();
// uint8_t buf_out[5000];
// int i = 0;
// while (y < height)
// {
//     int ym = 1 << (y % 8);                // Bitmask
//     uint8_t *bp = &buf[width * (y >> 3)]; // Start pointer of the row
//     x = 0;
//     while (x < width)
//     {
//         for(int k=0;k<8;k++)
//         {
//             paint.DrawPixel(x+k, y, !(bp[k]&ym));
//         }
//         x += 8;
//         bp += 8;
//     }
//     y++;
// }
// paint.DrawCircle(100,100,20,COLORED);
// epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
// epd.DisplayFrame();
// epd.DisplayFrame();
void display_init()
{

}