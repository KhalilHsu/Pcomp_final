int big = 5;
int push = 6;
int shuju = 4;

byte leds = 0;

//int allRvalue[8] = { 1,0,0,0,1,0,0,0 };



void setup() 
{
  pinMode(big, OUTPUT);
  pinMode(push, OUTPUT);  
  pinMode(shuju, OUTPUT);
}
 
void loop() 
{
  
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
 
