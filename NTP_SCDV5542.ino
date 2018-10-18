#include <5x5MatrixLIB.h>
#include <ESP8266WiFi.h>
#include <Time.h>
MatrixLIB Disp(2, 0, 4); //SDCLK DATA LOAD
const char* ssid = "yourssid";  //  your network SSID (name)
const char* password = "password";       // your network password
int timezone = X * 3600; // change to your timezone (X can only be - or + integer number).
int dst = 0;//set the DST 
 
void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
  // initialize the display library:
  Disp.begin();//init the display
  Disp.setBrightness(100);//set to maximum brightness
}
int blinkDisp = 1;//for blinking the display 
void loop() {
  time_t now = time(nullptr);//get the current time 
  struct tm* p_tm = localtime(&now);//structure of p_tm
  Serial.print(p_tm->tm_hour);//print hour
  Serial.print(":");//:
  Serial.print(p_tm->tm_min);//print minute
  Serial.print(":");//:
  Serial.print(p_tm->tm_sec);//print second
  Serial.println("");//blank
  int timE = (p_tm->tm_hour * 100) + p_tm->tm_min ;//timE=hour time 100 and plus with minute 
  String str = String(timE);//convert timE (int) to str (string)
  if ((p_tm->tm_hour >= 21) || (p_tm->tm_hour <=6)){//check if 9PM or later but not more than 6 AM  
    Disp.setBrightness(50);//yes == set brightness to half (It wont burn your eyes at the night)
  }else {//else
    Disp.setBrightness(100);//no == set maximum brightness !!!
  }
  /*str = "    " + str;
    int l = str.length() + 1;

    byte b[l];
    str.getBytes(b, l);
    for (int i = 0; i < l - 4; i++) {
    Disp.writeCharacter(0, b[0 + i]);
    Disp.writeCharacter(1, b[1 + i]);
    Disp.writeCharacter(2, b[2 + i]);
    Disp.writeCharacter(3, b[3 + i]);
    }
  */
  if (blinkDisp == 1) {//Display on 
    //set the 0 infront of the hour less than 10 AM
    if ((p_tm->tm_hour < 10) && (p_tm->tm_hour >= 0))
    {
      str = "   0" + str; // to make the 0 at the top digit of the display 
      int l = str.length() + 1;
      byte b[l];
      str.getBytes(b, l);
      for (int i = 0; i < l - 4; i++) {
        Disp.writeCharacter(0, b[0 + i]);
        Disp.writeCharacter(1, b[1 + i]);
        Disp.writeCharacter(2, b[2 + i]);
        Disp.writeCharacter(3, b[3 + i]);
      }

    } else
    {
      str = "    " + str;
      int l = str.length() + 1;
      byte b[l];
      str.getBytes(b, l);
      for (int i = 0; i < l - 4; i++) {
        Disp.writeCharacter(0, b[0 + i]);
        Disp.writeCharacter(1, b[1 + i]);
        Disp.writeCharacter(2, b[2 + i]);
        Disp.writeCharacter(3, b[3 + i]);
      }

      //set the 0 infront of the minute less than 10 minutes
      if ((p_tm->tm_min < 10) && (p_tm->tm_min >= 0))
      {
        str = "  0 " + str;//to make the 0  at the second digit (counted from bottom of the display)
        int l = str.length() + 1;
        byte b[l];
        str.getBytes(b, l);
        for (int i = 0; i < l - 4; i++) {
          Disp.writeCharacter(0, b[0 + i]);
          Disp.writeCharacter(1, b[1 + i]);
          Disp.writeCharacter(2, b[2 + i]);
          Disp.writeCharacter(3, b[3 + i]);

        }
      } else
      {
        str = "    " + str;
        int l = str.length() + 1;
        byte b[l];
        str.getBytes(b, l);
        for (int i = 0; i < l - 4; i++) {
          Disp.writeCharacter(0, b[0 + i]);
          Disp.writeCharacter(1, b[1 + i]);
          Disp.writeCharacter(2, b[2 + i]);
          Disp.writeCharacter(3, b[3 + i]);
        }//for line92
      }//else line86
    }//else line59
    blinkDisp = 0 ;
    delay(500);
  } else // Display off
  { // blinkDisp line44
    Disp.setBrightness(10);
    blinkDisp = 1;
    delay(500);
  }//else line 102
}//void loop line21
