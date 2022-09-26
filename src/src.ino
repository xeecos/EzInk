
#include <SPI.h>
#include "epd1in54.h"
#include "epdpaint.h"
// #include "imagedata.h"
// #include <driver/adc.h>
// #include <WiFi.h>
// #include <HTTPClient.h>
// #include "AHTxx.h"
// #include "spl06.h"
// AHTxx aht20(AHTXX_ADDRESS_X38, AHT2x_SENSOR);
// const char *ssid = "makeblock.cc";
// const char *password = "hulurobot";
#define COLORED 0
#define UNCOLORED 1

// //  delay(500);
// const char *host = "192.168.31.167";
unsigned char image[200 * 200];
Paint paint(image, 0, 0); // width should be the multiple of 8
Epd epd;
// unsigned long time_start_ms;
// unsigned long time_now_s;

// HWCDC USBSerial;
// void setup()
// {
//     Wire.begin(10, 8);
//     // put your setup code here, to run once:
//     USBSerial.begin(115200);
//     delay(1000);
//     SPL_init();
//     aht20.begin();
//     while (1)
//     {
//         USBSerial.print("Measured Air Pressure: ");
//         USBSerial.print(get_pressure(), 2);
//         USBSerial.println(" mb");

//         // ---- Altitude Values ----------------
//         double local_pressure = 1011.3; // Look up local sea level pressure on google // Local pressure from airport website 8/22
//         USBSerial.print("Local Airport Sea Level Pressure: ");
//         USBSerial.print(local_pressure, 2);
//         USBSerial.println(" mb");

//         USBSerial.print("altitude: ");
//         USBSerial.print(get_altitude(get_pressure(), local_pressure), 1);
//         USBSerial.println(" m");

//         USBSerial.print("altitude: ");
//         USBSerial.print(get_altitude_f(get_pressure(), local_pressure), 1); // convert from meters to feet
//         USBSerial.println(" ft");

//         USBSerial.println("\n");
//         USBSerial.print("temp: ");
//         USBSerial.print((get_temp_c() + aht20.readTemperature()) / 2);
//         USBSerial.print(" C, ");
//         USBSerial.print("humidity: ");
//         USBSerial.print(aht20.readHumidity());
//         USBSerial.println(" %");
//         delay(2000);
//     }
//     WiFi.begin(ssid, password);

//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(500);
//     }

//     // USBSerial.println("");
//     // USBSerial.println("WiFi connected");
//     // USBSerial.println("IP address: ");
//     // USBSerial.println(WiFi.localIP());

//     time_start_ms = millis();
// }

// void loop()
// {
//     adc1_config_width(ADC_WIDTH_BIT_12);
//     adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);
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
//         connectServer(200);
//         delay(500);
//     }
//     else
//     {
//     }
//     // put your main code here, to run repeatedly:
//     // time_now_s = (millis() - time_start_ms) / 1000;
//     // char time_string[] = {'0', '0', ':', '0', '0', '\0'};
//     // time_string[0] = time_now_s / 60 / 10 + '0';
//     // time_string[1] = time_now_s / 60 % 10 + '0';
//     // time_string[3] = time_now_s % 60 / 10 + '0';
//     // time_string[4] = time_now_s % 60 % 10 + '0';
// }

// void connectServer(int size)
// {

//     // We now create a URI for the request
//     String url = "http://192.168.31.167:3000/";
//     url += "?size=";
//     url += size;
//     url += "&font=";
//     url += "SimSun";

//     HTTPClient http;
//     http.begin(url);

//     // start get
//     int http_code = http.GET();

//     // handle http code
//     if (http_code != HTTP_CODE_OK)
//     {
//         // get fail.
//         // USBSerial.printf("GET fail, http code is %s\n", http.errorToString(http_code).c_str());
//         return;
//     }

//     // http response
//     String response = http.getString();
//     // USBSerial.printf("response:[%s]\n", response.c_str());

//     const uint8_t *bytes = (const uint8_t *)response.c_str();
//     // Read all the lines of the reply from server and print them to Serial
//     size = bytes[2];
//     // USBSerial.printf("size:%d %d\n", bytes[2], bytes[3]);
//     // USBSerial.println();
//     // USBSerial.println("closing connection");

//     paint.SetWidth(bytes[2]);
//     paint.SetHeight(bytes[3]);
//     paint.SetRotate(ROTATE_0);
//     paint.Clear(UNCOLORED);
//     for (int i = 4, len = size * size / 8 + 4; i < len; i++)
//     {
//         int idx = (i - 4) * 8;
//         int x = idx % size;
//         int y = (int)(idx / size);
//         int c = bytes[i];
//         for (int j = 0; j < 8; j++, x++)
//         {
//             bool b = (c >> (j)) & 0x1;
//             paint.DrawPixel(x, y, !b);
//         }
//     }
//     epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
//     epd.DisplayFrame();
//     epd.DisplayFrame();
// }

#include <Arduino.h>
#include <cppsrc/U8g2lib.h>
HWCDC USBSerial;
U8G2_NULL u8g2(U8G2_R0);
void setup()
{
    delay(1000);
    USBSerial.begin(115200);
    delay(1000);

    USBSerial.println("e-Paper start");
    if (epd.Init(lut_partial_update) != 0)
    {
        USBSerial.println("e-Paper init failed");
        return;
    }
    else
    {
        USBSerial.println("e-Paper init success");
    }
    epd.ClearFrameMemory(0xFF); // bit set = white, bit reset = black
    epd.DisplayFrame();
    epd.ClearFrameMemory(0xFF); // bit set = white, bit reset = black
    epd.DisplayFrame();

    paint.SetWidth(200);
    paint.SetHeight(200);
    paint.SetRotate(ROTATE_0);
    paint.Clear(UNCOLORED);
    int x = 0, y = 0, width = 200, height = 200;

    u8g2.initDisplay();
    u8g2.clearDisplay();
    u8g2.setPowerSave(0);

    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(50, 20, "Hello");
    uint8_t *buf = u8g2.getBufferPtr();
    uint8_t buf_out[5000];
    int i = 0;
    while (y < height)
    {
        int ym = 1 << (y % 8);                // Bitmask
        uint8_t *bp = &buf[width * (y >> 3)]; // Start pointer of the row
        x = 0;
        while (x < width)
        {
            for(int k=0;k<8;k++)
            {
                paint.DrawPixel(x+k, y, !(bp[k]&ym));
            }
            x += 8;
            bp += 8;
        }
        y++;
    }
    paint.DrawCircle(100,100,20,COLORED);
    epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame();
    epd.DisplayFrame();
}
void loop()
{
}