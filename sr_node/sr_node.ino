/**
  A simple NodeMCU based internet radio receiver dedicated to my
  family. It is hardcoded to a single station. Just turn on and listen.
  
  Wiring:
  --------------------------------
  | VS1053  | ESP8266 |  Other   |
  --------------------------------
  |   SCK   |   D5    |    -     |
  |   MISO  |   D6    |    -     |
  |   MOSI  |   D7    |    -     |
  |   XRST  |    -    |    -     |
  |   CS    |   D1    |    -     |
  |   DCS   |   D0    |    -     |
  |   DREQ  |   D3    |    -     |
  |   5V    |    -    |   VCC    |
  |   GND   |    -    |   GND    |
  --------------------------------

  Dependencies:
  -VS1053 library by baldram (https://github.com/baldram/ESP_VS1053_Library)
  -ESP8266Wifi

  Instructions:
  -Build the hardware
  -Set the station in this file
  -Upload the program

  IDE Settings (Tools):
  -IwIP Variant: v2.0 Higher Bandwidth
  -CPU Frequency: 160Hz
*/

#include <VS1053.h>
#include <ESP8266WiFi.h>

#define VS1053_CS     D1
#define VS1053_DCS    D0
#define VS1053_DREQ   D3

#define VOLUME_KNOB   A0

// Default volume (will add setting later)
#define VOLUME  90

VS1053 player(VS1053_CS, VS1053_DCS, VS1053_DREQ);
WiFiClient client;

char* ssid = "TP-Link";
const char* password = "xxxxxxxx";
     
//  http://comet.shoutca.st:8563/1
const char *host = "comet.shoutca.st";
const char *path = "/1";
int httpPort = 8563;

uint8_t mp3buff[32];
int loopcounter = 0;
int currentvolume = VOLUME;

void setup () {
    Serial.begin(115200);

    // Wait for VS1053 and PAM8403 to power up
    // otherwise the system might not start up correctly
    delay(5000);

    // This can be set in the IDE no need for ext library
    // system_update_cpu_freq(160);
    
    Serial.println("\n\nSimple Radio Node WiFi Radio");
    
    SPI.begin();

    player.begin();
    player.switchToMp3Mode();
    player.setVolume(VOLUME);

    Serial.print("Connecting to SSID "); Serial.println(ssid);
    WiFi.begin(ssid, password);
      
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");  Serial.println(WiFi.localIP());

    Serial.print("connecting to ");  Serial.println(host);
      
    if (!client.connect(host, httpPort)) {
      Serial.println("Connection failed");
      return;
    }

    Serial.print("Requesting stream: ");
    Serial.println(path);
    
    client.print(String("GET ") + path + " HTTP/1.1\r\n" +
                  "Host: " + host + "\r\n" + 
                  "Connection: close\r\n\r\n");
}

void loop() {
    ++loopcounter;

    if(!client.connected()){
      Serial.println("Reconnecting...");
      if(client.connect(host, httpPort)){
        client.print(String("GET ") + path + " HTTP/1.1\r\n" +
                  "Host: " + host + "\r\n" + 
                  "Connection: close\r\n\r\n");
      }
    }
  
    if(client.available() > 0){
      uint8_t bytesread = client.read(mp3buff, 32);
      player.playChunk(mp3buff, bytesread);
    }

    if(loopcounter >= 300){
      loopcounter = 0;
      int volume = analogRead(VOLUME_KNOB);
      int newvolume = (1.0*volume / 111)*100;
      if(3 < abs(currentvolume - newvolume)){
        if(100 < newvolume)
          newvolume = 100;
        Serial.print("Volume changed to: ");
        Serial.println(newvolume);
        currentvolume = newvolume;
        player.setVolume(newvolume);
      }
    }
}
