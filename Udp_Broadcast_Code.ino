#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "ESP_UDP";
const char *pass = "12345678";

IPAddress broadcastIP(192,168,4,255); //local ip 주소 선언
unsigned int localPort = 8266;

WiFiUDP udp; // wifi udp 통신 시작

void setup(){

  pinMode(2,INPUT);
  Serial.begin(9600);
  Serial.println();
  WiFi.softAP(ssid, pass);
  Serial.println(WiFi.softAPIP());
  udp.begin(localPort);
}

void loop(){

  udp.beginPacket(broadcastIP,8266);
  if(digitalRead(2) == HIGH){
    udp.write(1);
    udp.endPacket();
    delay(300);
  }
  delay(300);

}
