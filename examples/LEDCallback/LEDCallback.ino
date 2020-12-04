/*
   Led Callback Example for FCGF Library (Google Form for all Wi-Fi Boards)
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

//Include library
#include <FCGF.h>

//Call Google Form class
GoogleForm gf;

//Define led pins
#define RED_LED 6
#define GREEN_LED 7

//Your Wi-Fi credentials
const char *your_wifi_ssid = "";
const char *your_wifi_password = "";

//Data for your Google Form
int num_of_inputs;
int submit_delay = 0;
String myform_privateid = "";
String myform_inputs[] = {};
String myform_values[] = {};

void setup()
{
  //Disable/Enable Serial debug
  FCGF_DEBUG = true;

  //Start hardware serial
  Serial.begin(9600);

  //Wait for native usb connection
  while(!Serial);

  //Prepare led pins
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);

  //Start Wi-Fi and Secure client for your specific board and inizialize Google Form Lib
  gf.beginWiFi(your_wifi_ssid, your_wifi_password);

  //Submit data and receive callback from your Google Form gf.submit(privateid,arrayinputs,arrayvalues,numofinputs);
  gf.submit(myform_privateid, myform_inputs, myform_values, num_of_inputs, submit_delay);

  //Check if the data is really send to Google Docs (Green led for successful and red led for failed)
  if (FCGF_SUBMIT_CALLBACK)
  {
    digitalWrite(GREEN_LED, LOW);
  }
  else
  {
    digitalWrite(RED_LED, LOW);
  }

  //End setup
}

void loop()
{

  //Put your loop code
}
