/*
  Google Form Utility for Wi-Fi Boards and Arduino MRK GSM 1400
  Powered by Filo Connesso - Created by Mirko Pacioni
  Contributed by Ubi De Feo, Edoardo Sassi and Manuel Penna
  For Arduino IDE Boards - Created 23/02/2020 - Updated 04/12/2020
********************************************************************
  Tested Boards :
  Wroom32
  ESP32 DevKit V1n
  NodeMCU (0.9)
  Wemos D1 Mini
  ESP01
  Arduino MKR Wi-Fi 1010
  Arduino MRK GSM 1400
  Arduino Nano 33 Iot
  ESP8266 (ESP-12)
  Arduino UNO Wi-Fi Rev.2
  Arduino Oplà IoT Kit (Arduino MKR Wi-Fi 1010)
********************************************************************
  License : GPL 3.0 https://github.com/filoconnesso/FCGF/blob/main/LICENSE
  Italian Documentation : https://www.filoconnesso.it/fcgf-it/ by Mirko Pacioni, Edoardo Sassi, Manuel Penna
  English Documentation : https://www.filoconnesso.it/fcgf-en/ by Edoardo Sassi
*/

#ifndef FCGF_H
#define FCGF_H

//Include Arduino.h Library
#include <Arduino.h>

//Include Wi-Fi library for current board
#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_AVR_UNO_WIFI_REV2)
//For Arduino MKR Wi-Fi 1010, Arduino NANO 33 IoT and Arduino UNO Wi-Fi Rev.2
#include "WiFiNINA.h"
#include "WiFiSSLClient.h"
WiFiSSLClient client;
#elif defined(ARDUINO_SAMD_MKRGSM1400)

//For Arduino MKR GSM 1400
#include "MKRGSM.h"
GSMSSLClient client;
GSMModem modem;
GPRS gprs;
GSM gsmAccess;
#elif defined(ESP32) || defined(ARDUINO_ARCH_ESP32)

//For ESP32
#include "WiFi.h"
#include "WiFiClientSecure.h"
WiFiClientSecure client;
#elif defined(ESP8266)

//For ESP8266
#include "ESP8266WiFi.h"
#include "WiFiClientSecure.h"
BearSSL::WiFiClientSecure client;
#endif

//define params
#define FCGF_VERSION "0.0.4"
#define FCGF_PRINT Serial

//define wifi and client params
#define FCGF_TIMEOUT_HTTP 10000
#define FCGF_WIFI_CONNECTED_STATUS WL_CONNECTED
#define FCGF_HTTPS_PORT 443

//set google docs host
const char *FCGF_GOOGLE_HOST = "google.com";

//declare user strings
String FCGF_LANG;
String FCGF_WEB_AGENT = "FCGFIotDevice";
bool FCGF_SUBMIT_CALLBACK;

//time var
unsigned long FCGF_INITIAL_TIME = 0;
int FCGF_MS_IN_MINUTE = 60000;

//counter var
long FCGF_SUCCESSFUL_SUBMITIONS = 0;
long FCGF_FAILED_SUBMISSIONS = 0;
long FCGF_FAILED_CONNECTIONS = 0;

//begin bool
bool FCGF_BEGIN = false;
bool FCGF_GSM_CONNECTED = false;

//debug bool
bool FCGF_DEBUG = false;

//url encoding function
String curValuePostData;
String FCGF_ENCODE_STRING;
String FCGF_URL_ENCODE(String FCGF_STRING)
{
  FCGF_ENCODE_STRING = "";
  char charSingle;
  char charRef_a;
  char charRef_b;
  char charRef_c;
  for (int i = 0; i < FCGF_STRING.length(); i++)
  {
    charSingle = FCGF_STRING.charAt(i);
    if (charSingle == ' ')
    {
      FCGF_ENCODE_STRING += '+';
    }
    else if (isalnum(charSingle))
    {
      FCGF_ENCODE_STRING += charSingle;
    }
    else
    {
      charRef_b = (charSingle & 0xf) + '0';
      if ((charSingle & 0xf) > 9)
      {
        charRef_b = (charSingle & 0xf) - 10 + 'A';
      }
      charSingle = (charSingle >> 4) & 0xf;
      charRef_a = charSingle + '0';
      if (charSingle > 9)
      {
        charRef_a = charSingle - 10 + 'A';
      }
      charRef_c = '\0';
      FCGF_ENCODE_STRING += '%';
      FCGF_ENCODE_STRING += (String)charRef_a;
      FCGF_ENCODE_STRING += (String)charRef_b;
      FCGF_ENCODE_STRING += (String)charRef_c;
    }
  }
  return FCGF_ENCODE_STRING;
}

//ip to string function
String FCGF_IP_TO_STRING(IPAddress ip)
{
  String s = "";
  for (int i = 0; i < 4; i++)
  {
    s += i ? "." + String(ip[i]) : String(ip[i]);
  }
  return s;
}

//start function
class GoogleForm
{

public:
//dummy begin Wi-Fi function
#if defined(ESP8266) || defined(ESP32) || defined(ARDUINO_ARCH_ESP32)
  void dummyBegin()
  {
    if (FCGF_DEBUG)
    {
      FCGF_PRINT.println("*****FCGF LIBRARY - FILO CONNESSO GOOGLE FORM LIBRARY*****");
      FCGF_PRINT.print("Version : " + String(FCGF_VERSION));
      FCGF_PRINT.println();
      FCGF_PRINT.print("Connecting to wifi...");
    }
    while (WiFi.status() != FCGF_WIFI_CONNECTED_STATUS)
    {
      delay(200);
    }
    if (FCGF_DEBUG)
    {
      FCGF_PRINT.print("[OK]");
      FCGF_PRINT.println();
      FCGF_PRINT.print("Board type : ");
#if defined(ESP8266)
      FCGF_PRINT.print("ESP8266 Board");
#elif defined(ESP32) || defined(ARDUINO_ARCH_ESP32)
      FCGF_PRINT.print("ESP32 Board");
#endif
      FCGF_PRINT.println();
      FCGF_PRINT.println("Board IP Address : " + FCGF_IP_TO_STRING(WiFi.localIP()));
    }
#if defined(ESP8266)
    client.setInsecure(); //for ESP8266
#endif
    client.setTimeout(FCGF_TIMEOUT_HTTP);
    FCGF_BEGIN = true;
  }
#endif

//begin Wi-Fi function
#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_AVR_UNO_WIFI_REV2) || defined(ESP8266) || defined(ESP32) || defined(ARDUINO_ARCH_ESP32)
  void beginWiFi(const char *wifiName, const char *wifiPassword)
  {
    WiFi.begin(wifiName, wifiPassword);
    if (FCGF_DEBUG)
    {
      FCGF_PRINT.println("*****FCGF LIBRARY - FILO CONNESSO GOOGLE FORM LIBRARY*****");
      FCGF_PRINT.print("Version : " + String(FCGF_VERSION));
      FCGF_PRINT.println();
      FCGF_PRINT.print("Connecting to wifi...");
    }
    while (WiFi.status() != FCGF_WIFI_CONNECTED_STATUS)
    {
      delay(200);
    }
    if (FCGF_DEBUG)
    {
      FCGF_PRINT.print("[OK]");
      FCGF_PRINT.println();
      FCGF_PRINT.print("Board type : ");
#if defined(ARDUINO_SAMD_MKRWIFI1010)
      FCGF_PRINT.print("Arduino MKR Wi-Fi 1010");
#elif defined(ARDUINO_SAMD_NANO_33_IOT)
      FCGF_PRINT.print("Arduino Nano 33 Iot");
#elif defined(ARDUINO_AVR_UNO_WIFI_REV2)
      FCGF_PRINT.print("Arduino UNO Wi-Fi Rev.2");
#elif defined(ESP8266)
      FCGF_PRINT.print("ESP8266 Board");
#elif defined(ESP32) || defined(ARDUINO_ARCH_ESP32)
      FCGF_PRINT.print("ESP32 Board");
#endif
      FCGF_PRINT.println();
      FCGF_PRINT.println("Board IP Address : " + FCGF_IP_TO_STRING(WiFi.localIP()));
    }
#if defined(ESP8266)
    client.setInsecure(); //for ESP8266
#endif
    client.setTimeout(FCGF_TIMEOUT_HTTP);
    FCGF_BEGIN = true;
  }
#endif

//begin GSM function
#if defined(ARDUINO_SAMD_MKRGSM1400)
  void beginGSM(const char *apn, const char *pin, const char *user, const char *password)
  {
    if (FCGF_DEBUG)
    {
      FCGF_PRINT.println("*****FCGF LIBRARY - FILO CONNESSO GOOGLE FORM LIBRARY*****");
      FCGF_PRINT.print("Version : " + String(FCGF_VERSION));
      FCGF_PRINT.println();
      FCGF_PRINT.print("Start GSM modem...");
    }
    if (modem.begin())
    {
      if (FCGF_DEBUG)
      {
        FCGF_PRINT.print("[OK]");
      }
    }
    else
    {
      if (FCGF_DEBUG)
      {
        FCGF_PRINT.print("[FAILED]");
      }
    }
    if (FCGF_DEBUG)
    {
      FCGF_PRINT.println();
      FCGF_PRINT.print("Board type : ");
#if defined(ARDUINO_SAMD_MKRGSM1400)
      FCGF_PRINT.print("Arduino MKR GSM 1400");
#endif
      FCGF_PRINT.println();
      if (modem.getIMEI() != NULL)
      {
        FCGF_PRINT.print("Board IMEI Address : " + String(modem.getIMEI()));
      }
      else
      {
        FCGF_PRINT.print("Board IMEI Address error!");
      }
      FCGF_PRINT.println();
      FCGF_PRINT.print("Connecting to GSM...");
    }
    while (!FCGF_GSM_CONNECTED)
    {
      if ((gsmAccess.begin(pin) == GSM_READY) && (gprs.attachGPRS(apn, user, password) == GPRS_READY))
      {
        FCGF_GSM_CONNECTED = true;
      }
    }
    if (FCGF_DEBUG)
    {
      FCGF_PRINT.print("[OK]");
      FCGF_PRINT.println();
    }
    FCGF_BEGIN = true;
  }
#endif

  //submit function
  void submit(String moduleId, String moduleInputs[], String moduleValues[], int numOfInputs, int delayMinute = 0)
  {
    if (FCGF_BEGIN)
    {
      if (millis() >= FCGF_INITIAL_TIME + (delayMinute * FCGF_MS_IN_MINUTE))
      {
        if (client.connect(FCGF_GOOGLE_HOST, FCGF_HTTPS_PORT))
        {
          if (FCGF_DEBUG)
          {
            FCGF_PRINT.println();
            FCGF_PRINT.print("Submit data to " + moduleId + "...");
          }
          numOfInputs--;
          String urlPost = "/forms/d/" + moduleId + "/formResponse";
          String urlPostData = "submit=Submit&ifq";
          for (int i = 0; i <= numOfInputs; i++)
          {
            if (moduleInputs[i] != "\0")
            {
              curValuePostData = moduleValues[i];
              urlPostData += "&" + moduleInputs[i] + "=" + FCGF_URL_ENCODE(curValuePostData);
            }
          }
          if (FCGF_LANG.length() > 0)
          {
            urlPostData += "&" + FCGF_LANG;
          }
          client.println("POST " + urlPost + " HTTP/1.1");
          client.println("Host: docs.google.com");
          client.println("User-Agent: " + FCGF_WEB_AGENT + "/1.0");
          client.println("Connection: close");
          client.println("Content-Type: application/x-www-form-urlencoded;");
          client.print("Content-Length: ");
          client.println(urlPostData.length());
          client.println();
          client.println(urlPostData);
          String header = client.readStringUntil('\n');
          if (header.indexOf("200") > 0)
          {
            if (FCGF_DEBUG)
            {
              FCGF_PRINT.print("[OK]");
            }
            FCGF_SUBMIT_CALLBACK = true;
            FCGF_SUCCESSFUL_SUBMITIONS++;
          }
          else if (header.indexOf("400") > 0 || header.indexOf("404") > 0 || header.indexOf("500") > 0)
          {
            if (FCGF_DEBUG)
            {
              FCGF_PRINT.print("[FAILED]");
            }
            FCGF_SUBMIT_CALLBACK = false;
            FCGF_FAILED_SUBMISSIONS++;
          }
        }
        else
        {
          if (FCGF_DEBUG)
          {
            FCGF_PRINT.println();
            FCGF_PRINT.print("#HOST UNAVAILABLE");
          }
          FCGF_SUBMIT_CALLBACK = false;
          FCGF_FAILED_CONNECTIONS++;
        }
        FCGF_INITIAL_TIME = millis();
        client.stop();
      }
    }
  }

  //commafordot function
  String commaForDot(String stringText)
  {
    if (FCGF_BEGIN)
    {
      if (stringText.length() != 0)
      {
        stringText.replace(".", ",");
        return stringText;
      }
    }
  }

  //counter function
  long counter(int indexSelect)
  {
    if (FCGF_BEGIN)
    {
      switch (indexSelect)
      {
      case 0:
        return FCGF_SUCCESSFUL_SUBMITIONS;
        break;
      case 1:
        return FCGF_FAILED_SUBMISSIONS;
        break;
      case 2:
        return FCGF_FAILED_CONNECTIONS;
        break;
      }
    }
  }

  //classic delay for minutes
  void delayMinute(int minutes)
  {
    if (FCGF_BEGIN)
    {
      delay(minutes * FCGF_MS_IN_MINUTE);
    }
  }

  //language function
  void setLanguage(String lang)
  {
    if (FCGF_BEGIN)
    {
      FCGF_LANG = lang;
    }
  }

  //web agent function
  void setWebAgent(String webAgent)
  {
    if (FCGF_BEGIN)
    {
      FCGF_WEB_AGENT = webAgent;
    }
  }
};
#endif
