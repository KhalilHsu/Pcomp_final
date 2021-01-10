//This is our final program. The LCD and OLED parts are done by Siru Li (files oled _ print and lcd _ print)
//The epidemic made it impossible for us to get enough parts.
//We got all of the CCI inventory（RFID READER and RFID CARD）.It's still not enough.
//But we have completed the development of all core functions. 


//library and set up for Oled
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI 


//rfid reader
#include <SPI.h>
#include <MFRC522.h>


//lcd
#include <Wire.h> 
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27,16,2); 


//button
#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define JOYSTICK_SW A2
int value_x,value_y,value_sw;


//74hc595 for leds
int big = 5;
int push = 6;
int shuju = 4;
byte leds = 0;


//rfid reader
#define RST_PIN         9          
#define SS_1_PIN        10         
#define SS_2_PIN        8          
#define NR_OF_READERS   2
boolean work = false;
boolean play1 = false;
byte ssPins[] = {SS_1_PIN, SS_2_PIN};
MFRC522 mfrc522[NR_OF_READERS];


//set values and points storage
String uidString0;
String uidString1;
int personOne;
int personTwo;


/*************************************************
 * Public Constants
 *************************************************/
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define melodyPin 9
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup() {
  
  //piezo
  pinMode(9,OUTPUT);
  
  //led folw 74hc595
  pinMode(big, OUTPUT);
  pinMode(push, OUTPUT);  
  pinMode(shuju, OUTPUT);

  
  Serial.begin(9600); 
  while (!Serial);    
  SPI.begin();   

 
  //Botton setup
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  pinMode(JOYSTICK_SW, INPUT_PULLUP);

  
  //LCD setup
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

    //value for botton
    value_x=analogRead(JOYSTICK_X);  
    value_y=analogRead(JOYSTICK_Y);  
    value_sw=digitalRead(JOYSTICK_SW);
    sing(1);
    
    if(value_sw == 0 )//push button 
    {
    delay(10);
    work = true;//let boolean true to run code
    Serial.println("start the rfid");
    delay(100);
    }

    if(value_y == 0 )//button left
    {
    delay(10);
    play1 = true;//let boolean true to run code
    Serial.println("let player1 put the card");
    delay(100);
    
    //oled draw
    u8g.firstPage();  
    do {
    draw2();
    } while( u8g.nextPage() );
    delay(500);   
    }

    if (play1){
      
    //lcd
    lcd.display();
    lcd.backlight();
    lcd.setCursor(0 ,0);
    lcd.print("FINAL BATTLE");
    lcd.setCursor(0 ,1); 
    lcd.print("SET YOUR CARD");
    delay(5000);
    play1 = false;
    }

    ////////////////IMPORTANT
    if (work)
    {
    

      lcd.display();
      lcd.backlight();
      lcd.setCursor(0 ,0);
      lcd.print("Who's winner?");
      lcd.setCursor(0 ,1); 
      lcd.print("Wait a second!");
    


      u8g.firstPage();  
      do {
      draw1();
      } while( u8g.nextPage() );
      delay(500);
 
      //IMPORTANT card value compare 
      for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {

        
      // Look for new cards
      if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
      delay(100);
      
      //IMPORTANT get the first rfid reader' s card value
      uidString0 =  String(mfrc522[0].uid.uidByte[0]) + " " + String(mfrc522[0].uid.uidByte[1]) + " " + 
      String(mfrc522[0].uid.uidByte[2]) + " " + String(mfrc522[0].uid.uidByte[3]);
      delay(100);
      
      //IMPORTANT get the second rfid reader' s card value
      uidString1 =  String(mfrc522[1].uid.uidByte[0]) + " " + String(mfrc522[1].uid.uidByte[1]) + " " + 
      String(mfrc522[1].uid.uidByte[2]) + " " + String(mfrc522[1].uid.uidByte[3]);
      delay(100);

      //IMPORTANT make the values compareable
      String content0= "";
      String content1= "";
      
      content0.concat(uidString0);
      content1.concat(uidString1);
      
      //IMPORTANT print it to make sure it does work
      Serial.println(uidString0);
      Serial.println(uidString1);

      //IMPORTANT compare it
      if(uidString0 == "42 211 8 17")
      {
         personOne = 1;
         Serial.println("player1 get one point");
         Serial.println(personOne);
      }

      if(uidString0 == "107 92 60 12")
      {
         personOne = 2;
         Serial.println("player1 get two point");
         Serial.println(personOne);
      }

      if(uidString1 == "107 92 60 12")
      {
         personTwo = 2;
         Serial.println("player2 get two point");
         Serial.println(personTwo);
      }

      if(uidString1 == "42 211 8 17")
      {
         personTwo = 1;
         Serial.println("player2 get one point");
         Serial.println(personTwo);
      }

      //IMPORTANT which plafer is the winner
      if(personTwo>personOne && personOne != 0 && personTwo != 0){

      delay(100);

      Serial.println("Player2 win the game!");
        
      lcd.clear();
      lcd.backlight();
      lcd.setCursor(0 ,0);
      lcd.print("Congratulation!");
      lcd.setCursor(0 ,1); 
      lcd.print("You Wiiiiiiiin!");
      delay(100);
      sing(1);
      sing(1);
      sing(1);

      //oled set up 2
       u8g.firstPage();  
       do {
       draw1();
       } while( u8g.nextPage() );
       delay(500);
  
        
      //led flow for the winner
      leds = 0;
      updateShiftRegister();
      delay(300);

      //LED!!!
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
        lcd.clear();
        lcd.backlight();
        lcd.setCursor(0 ,0);
        lcd.print("GAME OVER");
        lcd.setCursor(0 ,1); 
        lcd.print("PUSH THE BUTTON");
        delay(200);
        sing(2);
        


        if(value_sw == 0 )
        {
        work = false;
        return;
        }

      }


      
      if(personTwo<personOne && personOne != 0 && personTwo != 0){

      delay(100);

      Serial.println("Player1 win the game!");
        
      lcd.clear();
      lcd.backlight();
      lcd.setCursor(0 ,0);
      lcd.print("Congratulation!");
      lcd.setCursor(0 ,1); 
      lcd.print("You Wiiiiiiiin!");
      delay(100);
      sing(1);
      sing(1);
      sing(1);

      //oled set up 2
       u8g.firstPage();  
       do {
       draw1();
       } while( u8g.nextPage() );
       delay(500);
  
        
      //led flow for the winner
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
        lcd.clear();
        lcd.backlight();
        lcd.setCursor(0 ,0);
        lcd.print("GAME OVER");
        lcd.setCursor(0 ,1); 
        lcd.print("PUSH THE BUTTON");
        delay(200);
        sing(2);


        if(value_sw == 0 )
        {
        work = false;
        return;
        }

      }

      mfrc522[reader].PICC_HaltA();
      mfrc522[reader].PCD_StopCrypto1();
    } 
  }
}


}



/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////



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

//led 
void updateShiftRegister()
{
   digitalWrite(big, LOW);
   shiftOut(shuju, push, LSBFIRST, leds);
   digitalWrite(big, HIGH);
}

//led function
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


//piezo function
int song = 0;
void sing(int s) {
  song = s;
  if (song == 2) {
    Serial.println(" 'Underworld Theme'");
    int size = sizeof(underworld_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
      int noteDuration = 1000 / underworld_tempo[thisNote];
      buzz(melodyPin, underworld_melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      buzz(melodyPin, 0, noteDuration);
    }
  } else {
    Serial.println(" 'Mario Theme'");
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
      int noteDuration = 1000 / tempo[thisNote];
      buzz(melodyPin, melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      buzz(melodyPin, 0, noteDuration);
    }
  }
}
void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000 / frequency / 2; 
  long numCycles = frequency * length / 1000; 
  for (long i = 0; i < numCycles; i++) { 
    digitalWrite(targetPin, HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(targetPin, LOW);
    delayMicroseconds(delayValue);
  }
}
  
