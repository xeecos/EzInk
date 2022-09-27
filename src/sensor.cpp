#include "sensor.h"
#include "AHTxx.h"
#include "spl06.h"

void sensor_init()
{
//    Wire.begin(10, 8);
//    AHTxx aht20(AHTXX_ADDRESS_X38, AHT2x_SENSOR);
//    SPL_init();
//    aht20.begin();
/*
        USBSerial.print("Measured Air Pressure: ");
        USBSerial.print(get_pressure(), 2);
        USBSerial.println(" mb");

        // ---- Altitude Values ----------------
        double local_pressure = 1011.3; // Look up local sea level pressure on google // Local pressure from airport website 8/22
        USBSerial.print("Local Airport Sea Level Pressure: ");
        USBSerial.print(local_pressure, 2);
        USBSerial.println(" mb");

        USBSerial.print("altitude: ");
        USBSerial.print(get_altitude(get_pressure(), local_pressure), 1);
        USBSerial.println(" m");

        USBSerial.print("altitude: ");
        USBSerial.print(get_altitude_f(get_pressure(), local_pressure), 1); // convert from meters to feet
        USBSerial.println(" ft");

        USBSerial.println("\n");
        USBSerial.print("temp: ");
        USBSerial.print((get_temp_c() + aht20.readTemperature()) / 2);
        USBSerial.print(" C, ");
        USBSerial.print("humidity: ");
        USBSerial.print(aht20.readHumidity());
        USBSerial.println(" %");
*/
}
void sensor_get(float&temperature,float&humidity,float&pressure)
{

}