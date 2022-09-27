#pragma once

// #include <WiFi.h>
// #include <HTTPClient.h>
// const char *ssid = "makeblock.cc";
// const char *password = "hulurobot";
// //  delay(500);
// const char *host = "192.168.31.167";
// unsigned long time_start_ms;
// unsigned long time_now_s;

// HWCDC USBSerial;
// void setup()
// {
//     // put your setup code here, to run once:
//     USBSerial.begin(115200);
//     delay(1000);

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
void service_init()
{

}
void service_get_location(float &longitude, float &latitude, float &altitude)
{

}
void service_get_timestamp(long &timestamp)
{

}
void service_get_weather()
{
    
}
void service_run()
{

}