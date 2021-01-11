//这是final01的尝试，使用了两个rfid reader，一个lcd，一个按钮，同样还有一排led灯。
//oled的添加
//无源蜂鸣器的添加

//library and set up for Oled
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI 


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


//74hc595
int big = 5;
int push = 6;
int shuju = 4;
byte leds = 0;

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


  //led folw 74hc595
  pinMode(big, OUTPUT);
  pinMode(push, OUTPUT);  
  pinMode(shuju, OUTPUT);


    Serial.begin(9600); 
    while (!Serial);    
    SPI.begin();   



       
    //按钮的setup
    pinMode(JOYSTICK_X, INPUT);
    pinMode(JOYSTICK_Y, INPUT);
    pinMode(JOYSTICK_SW, INPUT_PULLUP);


    //LCD的部分的setup
    lcd.init();                     

  //rfid reader
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
 
void loop() {

    //按钮部分赋值
    value_x=analogRead(JOYSTICK_X);  
    value_y=analogRead(JOYSTICK_Y);  
    value_sw=digitalRead(JOYSTICK_SW);

    
    if(value_sw == 0 )
{
    delay(10);
    work = true;
    Serial.println("start the rfid");
    delay(100);
}

    if(value_y == 0 )
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
    
    u8g.firstPage();  
    do {
    draw2();
    } while( u8g.nextPage() );
    delay(500);
  



  //card value compare 
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
        lcd.print("Congratulation!");
        lcd.setCursor(0 ,1); 
        lcd.print("You Wiiiiiiiin!");

      //oled set up 2
         u8g.firstPage();  
         do {
         draw1();
         } while( u8g.nextPage() );
         delay(500);
  
        
        //led flow
          leds = 0;
      updateShiftRegister();
      delay(300);

  for (int i = 0; i < 8; i++)
  {
      bitSet(leds, i);
      updateShiftRegister();
      delay(300);
  }
  
    digitalWrite(big, LOW);
    putvalue1 ();
    digitalWrite(big, HIGH);
    delay(300);
    digitalWrite(big, LOW);
    putvalue2 ();
    digitalWrite(big, HIGH);
    delay(300);
    digitalWrite(big, LOW);
    putvalue3 ();
    digitalWrite(big, HIGH);
    delay(300);
    digitalWrite(big, LOW);
    putvalue4 ();
    digitalWrite(big, HIGH);
    delay(300);
  
        delay(10000);
        //lcd.noDisplay();
        //lcd.noBacklight();
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



//function for oled print
void draw1(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(1, 16); 
  u8g.print("You are very");
  u8g.setPrintPos(1, 34); 
  u8g.print("   close to win!");
  u8g.setPrintPos(1, 58); 
  u8g.print("keep in low key!");  
  u8g.setPrintPos(2, 58); 
  u8g.print("keep in low key!");  
}

void draw2() {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(1, 16); 
  u8g.print("Your card has");
  u8g.setPrintPos(1, 36); 
  u8g.print("a big value");
    u8g.setPrintPos(2, 36); 
  u8g.print("a big value");
  u8g.setPrintPos(1, 58); 
  u8g.print("   Go for it!");  
  u8g.setPrintPos(2, 58); 
  u8g.print("   Go for it!");  
  
}

void updateShiftRegister()
{
   digitalWrite(big, LOW);
   shiftOut(shuju, push, LSBFIRST, leds);
   digitalWrite(big, HIGH);
}


void putvalue1 ()
{
  digitalWrite(push, LOW);
  digitalWrite(shuju, 1);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 1);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
}

void putvalue2 ()
{
  
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 1);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 1);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  
}

void putvalue3 ()
{
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 1);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 1);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
}

void putvalue4 ()
{ 
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 1);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 0);
  digitalWrite(push, HIGH);
  digitalWrite(push, LOW);
  digitalWrite(shuju, 1);
  digitalWrite(push, HIGH); 
}
  
