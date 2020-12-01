/*
   GSM Example for FCGF Library (Google Form for all Wi-Fi Boards and Arduino MKR GSM 1400)
   Documentation here :
   https://www.filoconnesso.it/fcgf-it/ (italian)
   https://www.filoconnesso.it/fcgf-en/ (english)
   Online ToolKit :
   https://www.filoconnesso.it/developers/FCGFToolKit/?lang=it (italian) 
   https://www.filoconnesso.it/developers/FCGFToolKit/?lang=en (english)
   Thank you for use and share with original creator reference
   By Filo Connesso https://www.filoconnesso.it
   License : http://creativecommons.org/licenses/by-nc-sa/4.0/
*/

//Include library
#include "FCGF.h"

//Call Google Form class
GoogleForm gf;

//Your GSM credentials
const char* your_apn = "";
const char* your_pin = "";
const char* your_user = "";
const char* your_password = "";

int num_of_inputs = 0; 
String myform_privateid = ""; 
String myform_inputs[] = {}; 
String myform_values[] = {};

void setup() {
  //Start hardware serial
  Serial.begin(9600);
  //Start GSM and Secure client for your specific board and inizialize Google Form Lib
  gf.beginGSM(your_apn, your_pin, your_user, your_password);
  //Submit data to Google Form
  gf.submit(myform_privateid, myform_inputs, myform_values, num_of_inputs);
  //Finish code
}

void loop() {
}
