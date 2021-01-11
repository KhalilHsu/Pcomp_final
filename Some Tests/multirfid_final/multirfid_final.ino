//这个完成了两个rfid reader的数据识别和比较
//接近最终的coding
//还需要添加其他input和output

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          
#define SS_1_PIN        10         
#define SS_2_PIN        8          
#define NR_OF_READERS   2

byte ssPins[] = {SS_1_PIN, SS_2_PIN};
String uidString0;
String uidString1;
int personOne;
int personTwo;

MFRC522 mfrc522[NR_OF_READERS];   


void setup() {

  Serial.begin(9600); 
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  SPI.begin();        // Init SPI bus

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
}



 
void loop() {

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    // Look for new cards

    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
      
      delay(100);

      uidString0 =  String(mfrc522[0].uid.uidByte[0]) + " " + String(mfrc522[0].uid.uidByte[1]) + " " + 
      String(mfrc522[0].uid.uidByte[2]) + " " + String(mfrc522[0].uid.uidByte[3]);

      delay(100);

      uidString1 =  String(mfrc522[1].uid.uidByte[0]) + " " + String(mfrc522[1].uid.uidByte[1]) + " " + 
      String(mfrc522[1].uid.uidByte[2]) + " " + String(mfrc522[1].uid.uidByte[3]);

      delay(100);

      String content0= "";
      String content1= "";
      
      content0.concat(uidString0);
      content1.concat(uidString1);

      Serial.println(uidString0);
      Serial.println(uidString1);
         
      if(uidString0 == "42 211 8 17")
      {

         personOne = 1;
         Serial.println("player1 test //get one point");
         Serial.println(personOne);

      }

      if(uidString1 == "107 92 60 12")
      {

         personTwo = 2;
         Serial.println("player2 test //get two point");
         Serial.println(personTwo);

      }
        

           if(personTwo>personOne && personOne != 0 && personTwo != 0){

        delay(100);

        Serial.println("Player2 win the game!");

        delay(100);

        personOne = personTwo = 0;



      }

      
      // Halt PICC
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
    } //if (mfrc522[reader].PICC_IsNewC
  } //for(uint8_t reader
}
