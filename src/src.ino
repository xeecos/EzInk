
#include <SPI.h>
#include "epd1in54.h"
#include "epdpaint.h"
#include "imagedata.h"
#include <driver/adc.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "AHTxx.h"
#include "spl06.h"
const char *ssid = "makeblock.cc";
const char *password = "hulurobot";
#define COLORED 0
#define UNCOLORED 1

#include "u8g2_wqy.h"
#include <cppsrc/U8g2lib.h>
//  delay(500);
const char *host = "192.168.31.167";
unsigned char image[200 * 200];
Paint paint(image, 0, 0); // width should be the multiple of 8
Epd epd;
unsigned long time_start_ms;
unsigned long time_now_s;

AHTxx aht20(AHTXX_ADDRESS_X38, AHT2x_SENSOR);
HWCDC USBSerial;
U8G2_NULL u8g2(U8G2_R0);
void setup()
{
    Wire.begin(10, 8);
    // put your setup code here, to run once:
    USBSerial.begin(115200);
    delay(1000);
    u8g2.begin();
    u8g2.enableUTF8Print();
    
    delay(1000);
    SPL_init();
    aht20.begin();
    // while (1)
    // {
    //     USBSerial.print("Measured Air Pressure: ");
    //     USBSerial.print(get_pressure(), 2);
    //     USBSerial.println(" mb");

    //     // ---- Altitude Values ----------------
    //     double local_pressure = 1011.3; // Look up local sea level pressure on google // Local pressure from airport website 8/22
    //     USBSerial.print("Local Airport Sea Level Pressure: ");
    //     USBSerial.print(local_pressure, 2);
    //     USBSerial.println(" mb");

    //     USBSerial.print("altitude: ");
    //     USBSerial.print(get_altitude(get_pressure(), local_pressure), 1);
    //     USBSerial.println(" m");

    //     USBSerial.print("altitude: ");
    //     USBSerial.print(get_altitude_f(get_pressure(), local_pressure), 1); // convert from meters to feet
    //     USBSerial.println(" ft");

    //     USBSerial.println("\n");
    //     USBSerial.print("temp: ");
    //     USBSerial.print((get_temp_c() + aht20.readTemperature()) / 2);
    //     USBSerial.print(" C, ");
    //     USBSerial.print("humidity: ");
    //     USBSerial.print(aht20.readHumidity());
    //     USBSerial.println(" %");
    //     delay(2000);
    // }
    // WiFi.begin(ssid, password);

    // while (WiFi.status() != WL_CONNECTED)
    // {
    //     delay(500);
    // }

    // USBSerial.println("");
    // USBSerial.println("WiFi connected");
    // USBSerial.println("IP address: ");
    // USBSerial.println(WiFi.localIP());
    if (epd.Init(lut_partial_update) != 0)
    {
        USBSerial.println("e-Paper init failed");
        return;
    }
    else
    {
        // USBSerial.println("e-Paper init success");
    }
    epd.ClearFrameMemory(0xff); // bit set = white, bit reset = black
    epd.DisplayFrame();
    epd.ClearFrameMemory(0xff); // bit set = white, bit reset = black
    epd.DisplayFrame();
    paint.SetRotate(ROTATE_0);
    paint.SetWidth(200);
    paint.SetHeight(24);

    /* For simplicity, the arguments are explicit numerical coordinates */
    paint.Clear(COLORED);
    paint.DrawStringAt(30, 4, "Hello world!", &Font16, UNCOLORED);
    epd.SetFrameMemory(paint.GetImage(), 0, 10, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame();
    epd.DisplayFrame();
    u8g2.clearBuffer();                  // clear the internal memory
    u8g2.setFont(u8g2_font_6x10_tf);  // choose a suitable font
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(0);
    u8g2.drawRFrame(0,0,200,200,0);
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
    u8g2.drawStr(20,20,"hello");
    u8g2.drawCircle(10,10,10);
    int w = u8g2.getDisplayWidth();
    int h = u8g2.getDisplayHeight();
    USBSerial.printf("w:%d\n", w);
    uint8_t* buf = u8g2.getBufferPtr();
    paint.SetWidth(w);
    paint.SetHeight(h);
    paint.SetRotate(ROTATE_0);
    paint.Clear(UNCOLORED);
    
    for (int i = 0, len = w * h / 8; i < len; i++)
    {
        int idx = i * 8;
        int x = idx % w;
        int y = (int)(idx / w);
        int c = buf[i];
        for (int j = 0; j < 8; j++, x++)
        {
            bool b = (c >> (j)) & 0x1;
            paint.DrawPixel(x, y, !b);
        }
    }
    epd.SetFrameMemory(paint.GetImage(), 0, 0, w,h);
    epd.DisplayFrame();
    epd.DisplayFrame();
    time_start_ms = millis();
}

void loop()
{
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);
    int val = adc1_get_raw(ADC1_CHANNEL_4);
    USBSerial.printf("%d\n", val);
    delay(1000);
    // if (val > 3000)
    // {
    //     delay(20);
    // }
    // else if (val > 1000)
    // {
    // }
    // else if (val > 500)
    // {
    //     connectServer(200);
    //     delay(500);
    // }
    // else
    // {
    // }
}

void connectServer(int size)
{

    // We now create a URI for the request
    String url = "http://192.168.31.167:3000/";
    url += "?size=";
    url += size;
    url += "&font=";
    url += "SimSun";

    HTTPClient http;
    http.begin(url);

    // start get
    int http_code = http.GET();

    // handle http code
    if (http_code != HTTP_CODE_OK)
    {
        // get fail.
        // USBSerial.printf("GET fail, http code is %s\n", http.errorToString(http_code).c_str());
        return;
    }

    // http response
    String response = http.getString();
    // USBSerial.printf("response:[%s]\n", response.c_str());

    const uint8_t *bytes = (const uint8_t *)response.c_str();
    // Read all the lines of the reply from server and print them to Serial
    size = bytes[2];
    // USBSerial.printf("size:%d %d\n", bytes[2], bytes[3]);
    // USBSerial.println();
    // USBSerial.println("closing connection");

    paint.SetWidth(bytes[2]);
    paint.SetHeight(bytes[3]);
    paint.SetRotate(ROTATE_0);
    paint.Clear(UNCOLORED);
    for (int i = 4, len = size * size / 8 + 4; i < len; i++)
    {
        int idx = (i - 4) * 8;
        int x = idx % size;
        int y = (int)(idx / size);
        int c = bytes[i];
        for (int j = 0; j < 8; j++, x++)
        {
            bool b = (c >> (j)) & 0x1;
            paint.DrawPixel(x, y, !b);
        }
    }
    epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame();
    epd.DisplayFrame();
}