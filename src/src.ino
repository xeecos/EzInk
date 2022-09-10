
#include <SPI.h>
#include "epd1in54.h"
#include "epdpaint.h"
#include "imagedata.h"
#include <driver/adc.h>
#include <WiFi.h>
#include <HTTPClient.h>
const char *ssid = "makeblock.cc";
const char *password = "hulurobot";
#define COLORED 0
#define UNCOLORED 1

//  delay(500);
/**
 * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
 * In this case, a smaller image buffer is allocated and you have to
 * update a partial display several times.
 * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
 */
const char *host = "192.168.31.167";
unsigned char image[200 * 200];
Paint paint(image, 0, 0); // width should be the multiple of 8
Epd epd;
unsigned long time_start_ms;
unsigned long time_now_s;

HWCDC USBSerial;
void setup()
{
    // put your setup code here, to run once:
    //USBSerial.begin(115200);
    delay(1000);
    // while(1);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        //USBSerial.print(".");
    }

    //USBSerial.println("");
    //USBSerial.println("WiFi connected");
    //USBSerial.println("IP address: ");
    //USBSerial.println(WiFi.localIP());
    if (epd.Init(lut_partial_update) != 0)
    {
        //USBSerial.println("e-Paper init failed");
        return;
    }
    else
    {
        //USBSerial.println("e-Paper init success");
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
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);
    int val = adc1_get_raw(ADC1_CHANNEL_4);
    // //USBSerial.printf("%d\n", val);
    if (val > 3000)
    {
        delay(20);
    }
    else if (val > 1000)
    {
    }
    else if (val > 500)
    {
        connectServer(200);
        delay(500);
    }
    else
    {
    }
    // put your main code here, to run repeatedly:
    // time_now_s = (millis() - time_start_ms) / 1000;
    // char time_string[] = {'0', '0', ':', '0', '0', '\0'};
    // time_string[0] = time_now_s / 60 / 10 + '0';
    // time_string[1] = time_now_s / 60 % 10 + '0';
    // time_string[3] = time_now_s % 60 / 10 + '0';
    // time_string[4] = time_now_s % 60 % 10 + '0';
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
    //USBSerial.printf("response:[%s]\n", response.c_str());

    const uint8_t *bytes = (const uint8_t *)response.c_str();
    // Read all the lines of the reply from server and print them to Serial
    size = bytes[2];
    //USBSerial.printf("size:%d %d\n", bytes[2], bytes[3]);
    //USBSerial.println();
    //USBSerial.println("closing connection");

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