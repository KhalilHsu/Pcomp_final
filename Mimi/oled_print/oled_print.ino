#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI 

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

void setup() {
  // flip screen, if required
  // u8g.setRot180();
}

void loop() {

  u8g.firstPage();  
  do {
    draw2();
  } while( u8g.nextPage() );
  
  delay(500);
}
