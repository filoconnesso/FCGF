/*
   Arduino Oplà IoT Kit Example for FCGF Library (Arduino MKR Wi-Fi 1010)
   Documentation here :
   https://www.filoconnesso.it/fcgf-it/ (italian)
   https://www.filoconnesso.it/fcgf-en/ (english)
   Online ToolKit :
   https://www.filoconnesso.it/developers/FCGFToolKit/
   Thanks for using!
   By Filo Connesso https://www.filoconnesso.it
   License : GPL 3.0 https://github.com/filoconnesso/FCGF/blob/main/LICENSE
   Example writted by Mirko Pacioni
*/

//Include libraries
#include <FCGF.h>
#include <Arduino_MKRIoTCarrier.h>

//Include graphics file
#include "graphics.h"

//Your Wi-Fi credentials
#define wifiSSID ""
#define wifiPASS ""

//You use the Oplà IoT Kit case ?
bool CARRIER_CASE = true;

//Define classes
MKRIoTCarrier carrier;
GoogleForm gf;

//Define led colors
uint32_t red = carrier.leds.Color(0, 255, 0);
uint32_t green = carrier.leds.Color(255, 0, 0);

//Declare sensors variables
float temperature, humidity, pressure;

//Declare light sensor variabiles
int r, g, b, light;

//Define other variables
int num_of_inputs = 4;

//Define form id and fields name
String myform_privateid = "";
String myform_inputs[] = {"", "", "", ""};

void setup()
{
  //Disable/Enable Serial debug
  FCGF_DEBUG = true;

  //Begin Serial
  Serial.begin(9600);

  //Wait for native usb connection
  while(!Serial);

  //Begin Google Form Libray and MKR IoT Carrier
  gf.beginWiFi(wifiSSID, wifiPASS);
  carrier.begin();

  //View Filo Connesso Logo on OLED
  carrier.display.fillScreen(ST77XX_RED);
  carrier.display.drawBitmap(0, -10, filoconnesso, 250, 250, 0xFFFF);

  delay(2000);

  //View FCGF Logo on OLED
  carrier.display.fillScreen(ST77XX_WHITE);
  carrier.display.drawBitmap(0, 0, fcgf, 250, 250, ST77XX_MAGENTA);

  //End setup
}

void loop()
{

  //Update capacitive buttons status
  carrier.Buttons.update();

  //Update sensor variables
  temperature = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();
  pressure = carrier.Pressure.readPressure();

  //Wait 5ms if the brightness sensor is not active
  while (!carrier.Light.colorAvailable())
  {
    delay(5);
  }

  //Update light value
  carrier.Light.readColor(r, g, b, light);

  //If you press button 3 of the carrier
  if (carrier.Button3.onTouchUp())
  {

    //View FCGF Sending logo on OLED
    carrier.display.fillScreen(ST77XX_WHITE);
    carrier.display.drawBitmap(0, 0, fcgf_sending, 250, 250, ST77XX_MAGENTA);

    //Updates array values ​​with sensor data
    String myform_values[] = {String(temperature), String(humidity), String(light), String(pressure)};

    //Send the collected data to your google form
    gf.submit(myform_privateid, myform_inputs, myform_values, num_of_inputs, 0);

    //Check if the sending went well
    if (FCGF_SUBMIT_CALLBACK)
    {
      //Shows green leds if sending is ok
      carrier.leds.setBrightness(125);
      carrier.leds.fill(green, 0, 5);
      carrier.leds.show();
    }
    else
    {
      //Shows red leds if sending is unsuccessful
      carrier.leds.setBrightness(125);
      carrier.leds.fill(red, 0, 5);
      carrier.leds.show();
    }

    //View FCGF Logo on OLED
    carrier.display.fillScreen(ST77XX_WHITE);
    carrier.display.drawBitmap(0, 0, fcgf, 250, 250, ST77XX_MAGENTA);

    //Turn off all the leds
    carrier.leds.setBrightness(0);
    carrier.leds.show();
  }

  //Finish loop
}
