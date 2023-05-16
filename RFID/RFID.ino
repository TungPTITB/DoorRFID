// Viral Science www.viralsciencecreativity.com www.youtube.com/c/viralscience
//ESP8266 Blynk RFID Door Lock Access Control System
//177 219 02 06
//19 201 167 167
//76 104 195 90
#include <SPI.h>
#include <MFRC522.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
 
#define SS_PIN 4  // sda
#define RST_PIN 2

Servo servo;
 
int lock = 0;    
 
MFRC522 mfrc522(RST_PIN, SS_PIN);        // Create MFRC522 instance.
char auth[] ="l4q7krXxizL_2CSA4ysNX7tlt4iwgjJL";    //Blynk Authentication Token -- sent via Email from Blynk
 
char ssid[] = "thaingo";   //Enter WiFi Name
char pass[] = "aichacha";   //Enter Wifi Password
 
SimpleTimer timer;
int fflag = 0; 
int eflag = 0; 
int jflag = 0; 
WidgetTerminal terminal(V3);
 
void setup() {
        Serial.begin(9600);        // Initialize serial communications with the PC
        Blynk.begin(auth, ssid, pass);
        SPI.begin();                // Init SPI bus
        mfrc522.PCD_Init();        // Init MFRC522 card
        //Serial.println("Scan a MIFARE Classic PICC to demonstrate Value Blocks.");
          timer.setInterval(1000L, iot_rfid);
          servo.attach(5);  //D1
          servo.write(90);
}
 
void loop() {
        
  timer.run(); // Initiates SimpleTimer
  Blynk.run();
       
}
 
void iot_rfid()
{
 
        // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
        MFRC522::MIFARE_Key key;
        for (byte i = 0; i < 6; i++) {
                key.keyByte[i] = 0xFF;
        }
        // Look for new cards
        if ( ! mfrc522.PICC_IsNewCardPresent()) {
                return;
        }
 
        // Select one of the cards
        if ( ! mfrc522.PICC_ReadCardSerial()) {
                return;
        }
        // Now a card is selected. The UID and SAK is in mfrc522.uid.
        
        // Dump UID
        Serial.print("Card UID:");
        for (byte i = 0; i < mfrc522.uid.size; i++) {
               Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
               Serial.print(mfrc522.uid.uidByte[i], DEC);
        } 
        Serial.println();
 
        // Dump PICC type
        byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    //    Serial.print("PICC type: ");
//Serial.println(mfrc522.PICC_GetTypeName(piccType));
        if (        piccType != MFRC522::PICC_TYPE_MIFARE_MINI 
                &&        piccType != MFRC522::PICC_TYPE_MIFARE_1K
                &&        piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
                //Serial.println("This sample only works with MIFARE Classic cards.");
                return;
        }
        
        // Enter RFID Tag ID here 
        //177 219 02 06
        if( ((mfrc522.uid.uidByte[0] == 177) && (mfrc522.uid.uidByte[1] == 219) && (mfrc522.uid.uidByte[2] == 02) && (mfrc522.uid.uidByte[3] == 06)) && (fflag == 1) )
        {
         Serial.println("Tung");   //Enter User1 Name
         Blynk.virtualWrite(V3, "Tung " );   //Enter User1 Name
         if(lock==1){
           servo.write(0);
           lock=0;
         }else{
           servo.write(160);
           lock=1;
         }

        //  digitalWrite(lock, LOW); 
        }
        //19 201 167 167
        else
        if(( (mfrc522.uid.uidByte[0] == 19) && (mfrc522.uid.uidByte[1] == 201) && (mfrc522.uid.uidByte[2] == 167) && (mfrc522.uid.uidByte[3] == 167))&& (eflag == 1) )
        {
         Serial.println("Trung");   //Enter User2 Name 
         Blynk.virtualWrite(V3, "Trung " );   //Enter User2 Name 
         if(lock==1){
           servo.write(0);
           lock=0;
         }else{
           servo.write(160);
           lock=1;
         }
        }
        //76 104 195 90
        else
        if( ((mfrc522.uid.uidByte[0] == 76) && (mfrc522.uid.uidByte[1] == 104) && (mfrc522.uid.uidByte[2] == 195) && (mfrc522.uid.uidByte[3] == 90))&& (jflag == 1) )
        {
         Serial.println("Co");   //Enter User3 Name
         Blynk.virtualWrite(V3, "Co " );   //Enter User3 Name
         if(lock==1){
           servo.write(0);
           lock=0;
         }else{
           servo.write(160);
           lock=1;
         }
        }
 
        else {
          Serial.println("Unregistered User");
        }
        
   }
 
// in Blynk app writes values to the Virtual Pin 3
BLYNK_WRITE(V0)
{
   fflag = param.asInt(); // assigning incoming value from pin V3 to a variable
  // Blynk.virtualWrite(V2, fflag );
 
}
 
 
// in Blynk app writes values to the Virtual Pin 4
BLYNK_WRITE(V1)
{
   eflag = param.asInt(); // assigning incoming value from pin V4 to a variable
   
}
 
BLYNK_WRITE(V2)
{
   jflag = param.asInt(); // assigning incoming value from pin V5 to a variable
  
}
