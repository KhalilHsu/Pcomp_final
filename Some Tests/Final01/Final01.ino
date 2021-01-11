//这是final01的尝试，使用了两个rfid reader，一个lcd，一个按钮，同样还有一排led灯。
//下一个使用的难度就是led灯的排列


#include <SPI.h>
#include <MFRC522.h>


//这是LCD
#include <Wire.h> 
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27,16,2); 


//这是添加的按钮define
#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define JOYSTICK_SW A2
int value_x,value_y,value_sw;

//这是led的define
//#define LED_ENTER    8   
#define LED1     5   
#define LED2      6  
#define LED3   12  
#define LED4    13  


//rfid reader
#define RST_PIN         9          
#define SS_1_PIN        10         
#define SS_2_PIN        8          
#define NR_OF_READERS  2
boolean work = false;
boolean play1 = false;
byte ssPins[] = {SS_1_PIN, SS_2_PIN};
MFRC522 mfrc522[NR_OF_READERS];


//设置积分
String uidString0;
String uidString1;
int personOne;
int personTwo;


///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {

    Serial.begin(9600); 
    while (!Serial);    
    SPI.begin();   

//灯的setup
    pinMode(LED1,OUTPUT); 
    pinMode(LED2,OUTPUT);
    pinMode(LED3,OUTPUT);
    pinMode(LED4,OUTPUT);

       
  //按钮的setup
    pinMode(JOYSTICK_X, INPUT);
    pinMode(JOYSTICK_Y, INPUT);
    pinMode(JOYSTICK_SW, INPUT_PULLUP);





   //LCD的部分的setup
    lcd.init();                     

    //lcd.backlight();
    //lcd.setCursor(2,0); // go to start of 2nd line
   // lcd.print("Hello, world!");
   // lcd.setCursor(4,1); // go to start of 2nd line
   // lcd.print("--khalil123");




//rfid reader
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
 
void loop() {

  //按钮部分赋值
    value_x=analogRead(JOYSTICK_X);  
    value_y=analogRead(JOYSTICK_Y);  
    value_sw=digitalRead(JOYSTICK_SW);

    allOn();
    delay(200);
    allOff();
    delay(200);
    
    if(value_sw == 0 )
{
    delay(10);
    work = true;
    Serial.println("start the rfid");
    delay(100);

}

    if(value_x == 0 )
{
    play1 = true;
    Serial.println("let player1 put the card");
    delay(10);

}

if (play1){

   lcd.display();
    lcd.backlight();
    lcd.setCursor(0 ,0);
    lcd.print("FINAL BATTLE");
    lcd.setCursor(0 ,1); 
    lcd.print("SET YOUR CARD");
    delay(5000);
    play1 = false;

}



if (work){

    //work = true;
    lcd.display();
    lcd.backlight();
    lcd.setCursor(0 ,0);
    lcd.print("Who's winner?");
    lcd.setCursor(0 ,1); 
    lcd.print("Wait a second!");
    allOn();
    delay(1000);
    allOff();
    delay(1000);


  
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
         Serial.println("player1 get one point");
         Serial.println(personOne);

      }

      if(uidString1 == "107 92 60 12")
      {

         personTwo = 2;
         Serial.println("player2 get two point");
         Serial.println(personTwo);

      }
        
           if(personTwo>personOne && personOne != 0 && personTwo != 0){

        delay(100);

        Serial.println("Player2 win the game!");
        
        lcd.clear();
        lcd.backlight();
        lcd.setCursor(0 ,0);
        lcd.print("YOU WIN!");
        lcd.setCursor(0 ,1); 
        lcd.print("YOU WIN!");
        //常量led//或者流水灯
        allOn();

        delay(10000);
        lcd.noDisplay();
        lcd.noBacklight();
        work = false;

      }

      // Halt PICC
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
    } //if (mfrc522[reader].PICC_IsNewC
  }//for(uint8_t reader
}//if (work = true)


}
void allOn() 
{
        digitalWrite(LED1,HIGH);
        digitalWrite(LED2,HIGH);
        digitalWrite(LED3,HIGH);
        digitalWrite(LED4,HIGH);
  }

  
void allOff() 
{
        digitalWrite(LED1,LOW);
        digitalWrite(LED2,LOW);
        digitalWrite(LED3,LOW);
        digitalWrite(LED4,LOW);
}
  
