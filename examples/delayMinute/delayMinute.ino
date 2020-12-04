/*
   Delay Minute Example for FCGF Library (Google Form for all Wi-Fi Boards)
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

//Your Wi-Fi credentials
const char *your_wifi_ssid = "";
const char *your_wifi_password = "";

//Data for your Google Form
int num_of_inputs;
int submit_delay = 0;
String myform_privateid = "";
String myform_inputs[] = {};

void setup()
{
  //Disable/Enable Serial debug
  FCGF_DEBUG = true;

  //Start hardware serial
  Serial.begin(9600);

  //Wait for native usb connection
  while(!Serial);

  //Start Wi-Fi and Secure client for your specific board and inizialize Google Form Lib
  gf.beginWiFi(your_wifi_ssid, your_wifi_password);

  //End setup
}

void loop()
{
  //Array of Values
  String myform_values[] = {};

  //Submit data and receive callback from your Google Form gf.submit(privateid,arrayinputs,arrayvalues,numofinputs,submitdelay);
  gf.submit(myform_privateid, myform_inputs, myform_values, num_of_inputs, 0);

  //Send values another values to Google Form after 2 minute
  gf.delayMinute(2);
}
