/*
   GSM Example for FCGF Library (Arduino MKR GSM 1400)
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

//Your GSM credentials
const char *your_apn = "";
const char *your_pin = "";
const char *your_user = "";
const char *your_password = "";

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

  //Start GSM and Secure client for your specific board and inizialize Google Form Lib
  gf.beginGSM(your_apn, your_pin, your_user, your_password);

  //Submit data to Google Form
  gf.submit(myform_privateid, myform_inputs, myform_values, num_of_inputs, submit_delay);

  //End setup
}

void loop()
{

  //Put your loop code
}
