
#include <Arduino.h>


int ledPin = 13;  
int sayi;

void setup() {
  
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 0);
  Serial.begin(9600);
}

void loop() 
{
      sayi = Serial.parseInt();
      while(sayi > -1)
      {
        if(sayi != 0)
        {
            sayi--;
            Serial.print(sayi);
            Serial.flush(); 
            if(sayi == 0)return; 
        }

        for(int j=0;j<1000;j++)
        {
          char ledchar = Serial.read();
          if(ledchar == 'a')
          {
            analogWrite(ledPin, 255);
          }
          else if(ledchar == 'k')
          { 
            analogWrite(ledPin, 0);
          }   
          if(sayi == 0)return; 
          delay(1);
        }
      }          
}