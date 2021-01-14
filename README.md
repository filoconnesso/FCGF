# Google Form Library by Filo Connesso
1. License : GNU General Public License v3.0
2. Italian Documentation Here : https://www.filoconnesso.it/fcgf-it/
3. English Documentation Here (old version, the new version coming soon) : https://www.filoconnesso.it/fcgf-en/
4. New Simple ToolKit : https://www.filoconnesso.it/developers/FCGFToolKit/
# Changelog 0.0.4 : 
1. Added support for Arduino UNO Wi-Fi Rev.2
2. Fixed stability issues with Google server connection
3. Fixed an issue that prevented the connection to Google if the submit delay with a value greater than 0 was set
4. Added example for Arduino Oplà IoT Kit
5. Added feature to enable or disable serial debugging with the FCGF_DEBUG variable (true or false).
# Changelog 0.0.3 : 
1. Added support for Arduino MRK GSM 1400 and Arduino Nano 33 Iot
2. Now it is possible to submit data with a delay that does not block the LOOP cycle.  
3. Addeded counter to count failed and correct submissions. (eg. gf.counter(index);) :
index = 0 (for successful submissions)
index = 1 (for failed sumissions)
index = 2 (for failed connections to google host)
4. Added function for convert dot to comma (eg. gf.commaForDot(string);) for Italian Google Sheet settings :
float origin = 1.5; 
String new = gf.commaForDot(String(origin));
Serial.println(new); //1,5
5. Fixed minor problems.
# Changelog 0.0.2 : 
1. Now you can send special symbols (e.g. | \! "£ $% & / () =? ^ * + [] {} -_;:,. <>)
2. Callback feature added.
3. Fixed minor problems.
# Thanks for using FCGF!
