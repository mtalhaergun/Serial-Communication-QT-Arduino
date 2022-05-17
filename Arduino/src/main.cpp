
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
      if(sayi != 0)
      {
        for(int i=0;i<sayi+i;i++)
        {
          sayi--;
          Serial.print(sayi);
          Serial.flush();
          for(int j=0;j<1000;j++)
          {
            delay(1);
            char ledchar = Serial.read();
            if(ledchar == 'a')
            {
              analogWrite(ledPin, 255);
            }
            else if(ledchar == 'k')
            { 
              analogWrite(ledPin, 0);
            }    
          }  
        }       
      }
      else{
        char ledchar = Serial.read();
        if(ledchar == 'a')
        {
          analogWrite(ledPin, 255);
        }
        else if(ledchar == 'k')
        {
          analogWrite(ledPin, 0);
        }
      }
}
