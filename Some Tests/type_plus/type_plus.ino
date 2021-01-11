//Viral Science
//RFID
//这是一个rfid的实验，完成了使用卡片显示大小的代码
//但是问题在于需要多出一个输入装置去讲代码再次激活，就是boolean readcard = false
//同样尚未完成多rfid reader的接入

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
 
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

int total = 0;
boolean readcard = false;

void setup() 
{
  
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  

  content.toUpperCase();
  if (content.substring(1) == "6B 5C 3C 0C" && readcard == false and total !=1) 
  {
    readcard = true;
    
    /*
    Serial.println("Get onr point");
    Serial.println();
    delay(500);
    total++;
    Serial.println(total);
    Serial.println();
    delay(500);}
    */

  if(readcard) {
    
    Serial.println("Get one point");
    delay(500);
    total += 1;
    Serial.println(total);
    readcard = false;
    return;
    }
    
  }

      readcard = false;

    
    }
 
