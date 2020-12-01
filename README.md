# This Library is an Open Source Library created by Filo Connesso
# License Here : http://creativecommons.org/licenses/by-nc-sa/4.0/
# Documentation Here : https://www.filoconnesso.it/fcgm-it/ (Italian)
# Documentation Here : https://www.filoconnesso.it/fcgm-en/ (English)
# New Simple ToolKit : https://www.filoconnesso.it/developers/FCGFToolKit/
# Changelog 0.0.3 : 
1. Added support for Arduino MRK GSM 1400 and Arduino Nano 33 Iot
2. Now it is possible to submit data with a delay that does not block the LOOP cycle.  
3. Addeded counter to count failed and correct submissions. (eg. gf.counter(index);) :
index = 0 (for successful submissions), index = 1 (for failed sumissions), index = 2 (for failed connections to google host)
4. Added function for convert dot to comma (eg. gf.commaForDot(string);) for Italian Google Sheet settings :
float origin = 1.5; 
String new = gf.commaForDot(String(origin));
Serial.println(new); //1,5
5. Fixed minor problems.
# Changelog 0.0.2 : 
1. Now you can send spacial symbols (e.g. | \! "£ $% & / () =? ^ * + [] {} -_;:,. <>)
2. Callback feature added.
3. Fixed minor problems.
# Share this contents with original creator reference
# Thanks for use
