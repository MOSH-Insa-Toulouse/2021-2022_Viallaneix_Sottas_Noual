
//Programme de test HARDWARE LIE CAPTEUR
//PROJET MOSH - CAPTEUR GRANULOMETRIQUE
//

int sense = 0;


//Potentiomètre
#include <SPI.h>

const byte csPin = 10;
const int maxPositions = 256;
const long rAB = 46300;

const byte rWiper = 125;
const byte pot0 = 0x11;
const byte pot0Shutdown  = 0x21;
long resistanceWB;

int potar=6;


void setup() {
  Serial.begin(9600);

  digitalWrite(csPin, HIGH);
  pinMode(csPin, OUTPUT);
  SPI.begin();

}




void loop() {

  setPotWiper(pot0, potar);
  delay(50);

  float output = analogRead(sense);
  output=output*5/1024;
  Serial.print("\t");
  Serial.print(output);
  Serial.println(" V");
  
  if(output<0.8)
  {
    potar-=1;
  }
  else if(output>1.2)
  {
    potar+=1;
  }

}


void setPotWiper(int addr, int pos)
{
  pos = constrain(pos,0,255);
  digitalWrite(csPin,LOW);
  SPI.transfer(addr);
  SPI.transfer(pos);
  digitalWrite(csPin, HIGH);

 resistanceWB = ((rAB*pos)/maxPositions) + rWiper;
 Serial.print("Wiper position: ");
 Serial.print(pos);
 Serial.print("\tResistance wiper to B terminal: ");
 Serial.print(resistanceWB);
 Serial.print(" ohms");
}


