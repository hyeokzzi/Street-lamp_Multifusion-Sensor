#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
// 입출력 데이터핀을 RX, TX핀으로 동작할 수 있게 해주는 라이브러리
// 하지만 모든 핀이 RX, TX를 지원하는 것은 아님

#define Pir1 2
#define Pir2 3
#define Pir3 4
#define Pir4 5
#define relay_module 6
HUSKYLENS huskylens;
HUSKYLENS huskylens_2;
SoftwareSerial mySerial(12,13); 
void printResult(HUSKYLENSResult result);

void setup() {
    Serial.begin(9600);
    Wire.begin();
    mySerial.begin(9600);
    pinMode(Pir1,INPUT);
    pinMode(Pir2,INPUT);
    pinMode(Pir3,INPUT);
    pinMode(Pir4,INPUT);
    pinMode(relay_module, OUTPUT);
    pinMode(32,OUTPUT);
    digitalWrite(32,LOW);
//    while(!huskylens.begin(mySerial)&&!huskylens_2.begin(Wire))
//    {
//        Serial.println(F("Begin failed!"));
//        //Serial.println(F("Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
//        //Serial.println(F("Please recheck the connection."));
//        delay(100);
//    }
}

void loop() {
    if (!huskylens.begin(mySerial)){
        Serial.println(F("Begin failed!"));
        //Serial.println(F("Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
        //Serial.println(F("Please recheck the connection."));
        delay(100);
    }
    if (!huskylens_2.begin(Wire)){
      Serial.println(F("Begin failed!"));
      delay(100);
    }
    if (!huskylens.request()) Serial.println(F("1_Fail to request data from HUSKYLENS, recheck the connection!"));
    else if(!huskylens.isLearned()) Serial.println(F("1_Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if(!huskylens.available()) Serial.println(F("1_No block or arrow appears on the screen!"));
    else
    {
        Serial.println(F("#####Left Side Detected!#####"));
        if ((huskylens.available()&&digitalRead(Pir1))||(huskylens.available()&&digitalRead(Pir2)))
        {
            HUSKYLENSResult result = huskylens.read();
            printResult(result);
        }    
    }
    if (!huskylens_2.request()) Serial.println(F("2_Fail to request data from HUSKYLENS, recheck the connection!"));
    else if(!huskylens_2.isLearned()) Serial.println(F("2_Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if(!huskylens_2.available()) Serial.println(F("2_No block or arrow appears on the screen!"));
    else
    {
        Serial.println(F("####Right Side Detected!#####"));
        if ((huskylens_2.available()&&digitalRead(Pir3))||(huskylens_2.available()&&digitalRead(Pir4)))
        {
            HUSKYLENSResult result = huskylens_2.read();
            printResult(result);
        }    
    }
}

void printResult(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
      Serial.println(result.ID);
      digitalWrite(32,HIGH);
      digitalWrite(relay_module,LOW);
      delay(1000);
      digitalWrite(relay_module,HIGH);
      digitalWrite(32,LOW);
    }
    else{
        Serial.println("Object unknown!");
    }
}
