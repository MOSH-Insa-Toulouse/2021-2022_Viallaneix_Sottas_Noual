//Programme de base : 
//PROJET MOSH - CAPTEUR GRANULOMETRIQUE
//Version 4 - 15/04

//#include<Servo.h>


////////////////////  ENCODEUR ROTATOIRE
#define encoder0PinA 2
#define Switch 3
volatile unsigned int encoder0Pos = 0;



////////////////////  POTENTIOMETRE R2
#include <SPI.h>
const byte csPin = 10;
const int maxPositions = 256;
const long rAB = 46300;
const byte rWiper = 125;
const byte pot0 = 0x11;
const byte pot0Shutdown  = 0x21;
long resistanceWB;


////////////////////  OLED
#include <Adafruit_SSD1306.h>
#define nombredDePixelsEnLargeur 128
#define nombredePixelsEnHauteur 64
#define brocheResetOLED -1
#define adresseI2CecranOLED 0x3C
Adafruit_SSD1306 ecranOLED(nombredDePixelsEnLargeur, nombredePixelsEnHauteur, &Wire, brocheResetOLED);


////////////////////  CAPTEUR
int sense = 0;
int potar=100;
int R1=100;
float R2=(((rAB*potar)/maxPositions) + rWiper)/1000;
int R3=100;
int R5=10;
int R6=1;
float Rsensor;


////////////////////  MENU ET NAVIGATION
#define PRINCIPAL 0
#define QUICKSENSE 1
#define SERIALSENSE 2
#define INFOS 3
int clic=1;
int menu=0;
int ligne=0;


////////////////////  BLUETOOTH
#include <SoftwareSerial.h>
#define rxPin 9
#define txPin 8
SoftwareSerial mySerial(rxPin, txPin);


///////////////////// VARIABLES BANC DE TEST
int theta0=-85;
int theta;
int pastheta;
int cycles;
int AnalogTrig = 7; // pin pour trigger banc de test




void setup() {
  
  Serial.begin(9600);
  mySerial.begin(9600);


  ////////////////////  BLUETOOTH
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);


  ////////////////////  POTENTIOMETRE R2
  digitalWrite(csPin, HIGH);
  pinMode(csPin, OUTPUT);
  SPI.begin();


  ////////////////////  OLED
  if(!ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED))
  {
    while(1);
  }
  ecranOLED.setTextSize(2);
  ecranOLED.setTextColor(SSD1306_WHITE);


  ////////////////////  ENCODEUR ROTATOIRE
  pinMode(encoder0PinA, INPUT);
  digitalWrite(encoder0PinA, HIGH);
  attachInterrupt(0,doEncoder,RISING);
  pinMode(Switch, INPUT_PULLUP);
  attachInterrupt(1,doSwitch,FALLING);

  /////////////////// SETUP BANC DE TEST
  pinMode(AnalogTrig, OUTPUT);
  digitalWrite(AnalogTrig, LOW);
  
}




void loop() {

  ////////////////////  INITIALISATION MENU
  clic=1;
  encoder0Pos = 0;
  delay(50);


  ////////////////////  MESURE DE LA TENSION ET ADAPTATION POTENTIOMETRE R2
  float output = analogRead(sense);
  output=output*5/1024;
  Serial.print("Tension mesurée : ");
  Serial.print(output);
  Serial.print(" V");
  
  if(output<0.9)
  {
    potar-=1;
  }
  else if(output>1.1)
  {
    potar+=1;
  }
  
  potar = constrain(potar,0,255);
  setPotWiper(pot0, potar);
  R2 = (((rAB*potar)/maxPositions) + rWiper)/1000;
  Rsensor = ((1+R3/R2)*R1*(5/output)-R1-R5)/1000;
  Serial.print("\t\t\tRsensor : ");
  Serial.print(Rsensor);
  Serial.print(" MOhms");

  
  ////////////////////  MENU ET NAVIGATION
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 0);
  ecranOLED.setTextColor(SSD1306_WHITE);
  
  
  if (menu==PRINCIPAL)
  {
    
    if(encoder0Pos==1)
    {
    if (ligne<2){ligne+=1;}
    else {ligne=0;}
    }
    
    if(ligne==0)
    {
      ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      ecranOLED.println("MESURE");
      ecranOLED.setTextColor(SSD1306_WHITE);
      ecranOLED.println("REPETITION");
      ecranOLED.println("INFOS");
      if(clic==0){menu=QUICKSENSE;}
    }
    else if(ligne==1)
    {
      ecranOLED.println("MESURE");
      ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      ecranOLED.println("REPETITION");
      ecranOLED.setTextColor(SSD1306_WHITE);
      ecranOLED.println("INFOS");
      if(clic==0){
        menu=SERIALSENSE;
        theta=theta0;
        pastheta=1;
        cycles=0;
      }
    }
    else
    {
      ecranOLED.println("MESURE");
      ecranOLED.println("REPETITION");
      ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      ecranOLED.println("INFOS");
      if(clic==0){menu=INFOS;}
    }
  }

  else if (menu==QUICKSENSE)
  {
    ecranOLED.println("Output : ");
    ecranOLED.print(output);
    ecranOLED.println(" V");
    ecranOLED.println("Rsensor : ");
    ecranOLED.print((int) Rsensor);
    ecranOLED.print(" MOhms");
    mySerial.print((int) Rsensor);
    while(mySerial.available())
    {
      Serial.print((char) mySerial.read());
    }
    if(clic==0){menu=PRINCIPAL;}
  }

  else if (menu==SERIALSENSE)
  {
    ecranOLED.println("Mode Cycle");
    digitalWrite(AnalogTrig, HIGH);
    
    Serial.print("\t\t\tTheta :");
    Serial.print(theta);
    theta+=pastheta;
    if(theta==85){pastheta=-1;}
    if(theta==-85){
      pastheta=1;
      cycles+=1;
      }

    digitalWrite(AnalogTrig, LOW);
    
    if(clic==0||cycles==3){
      menu=PRINCIPAL;
      digitalWrite(AnalogTrig, LOW);
      }
  }
  
  else if (menu==INFOS)
  {
    ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    ecranOLED.println("Capteur V4");
    ecranOLED.setTextColor(SSD1306_WHITE);
    ecranOLED.println("Sottas,");
    ecranOLED.println("Noual,");
    ecranOLED.println("Viallaneix");
    if(clic==0){menu=PRINCIPAL;}
  }

  
  ecranOLED.display();
  Serial.println(" ");
}




////////////////////  POTENTIOMETRE R2
void setPotWiper(int addr, int pos)
{
  digitalWrite(csPin,LOW);
  SPI.transfer(addr);
  SPI.transfer(pos);
  digitalWrite(csPin, HIGH);
  
  resistanceWB = ((rAB*pos)/maxPositions) + rWiper;
  Serial.print("\t\t\tPosition sur 256 : ");
  Serial.print(pos);
  Serial.print("\t\t\tR2 : ");
  Serial.print(resistanceWB);
  Serial.print(" Ohms");
}



////////////////////  ENCODEUR ROTATOIRE POUR LE CLIC
void doSwitch()
{
  static unsigned long tempsprecedent = 0;
  unsigned long temps = millis();
  if (temps - tempsprecedent > 100) 
  {
    clic = 0;
  }
  tempsprecedent=temps;
}


////////////////////  ENCODEUR ROTATOIRE POUR LA ROTATION
void doEncoder()
{
  encoder0Pos=1;
}
