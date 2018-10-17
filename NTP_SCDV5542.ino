#include <5x5MatrixLIB.h>
#include <ESP8266WiFi.h>
#include <Time.h>
MatrixLIB Disp(2, 0, 4); //SDCLK DATA LOAD
const char* ssid = "jiamjarapun2";  //  your network SSID (name)
const char* password = "226142abcd";       // your network password
int timezone = 7 * 3600;
int dst = 0;

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
  // initialize the display library:
  Disp.begin();
  Disp.setBrightness(100);
}

void loop() {
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  Serial.print(p_tm->tm_hour);
  Serial.print(":");
  Serial.print(p_tm->tm_min);
  Serial.print(":");
  Serial.print(p_tm->tm_sec);
  Serial.println("");
  int timE = (p_tm->tm_hour * 100) + p_tm->tm_min ;
  String str = String(timE);
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

  //set the 0 infront of the hour less than 10 AM
  if ((p_tm->tm_hour < 10) && (p_tm->tm_hour >= 0))
  {
    str = "   0" + str;
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
      str = "  0 " + str;
      int l = str.length() + 1;
      byte b[l];
      str.getBytes(b, l);
      for (int i = 0; i < l - 4; i++) {
        Disp.writeCharacter(0, b[0 + i]);
        Disp.writeCharacter(1, b[1 + i]);
        Disp.writeCharacter(2, b[2 + i]);
        Disp.writeCharacter(3, b[3 + i]);

      }
    }else
      {
        str = "   0" + str;
        int l = str.length() + 1;
        byte b[l];
        str.getBytes(b, l);
        for (int i = 0; i < l - 4; i++) {
          Disp.writeCharacter(0, b[0 + i]);
          Disp.writeCharacter(1, b[1 + i]);
          Disp.writeCharacter(2, b[2 + i]);
          Disp.writeCharacter(3, b[3 + i]);
        }
      }
  }
delay(1000);
}
