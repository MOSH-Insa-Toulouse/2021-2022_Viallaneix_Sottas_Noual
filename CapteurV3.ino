
//Programme de base : 
//PROJET MOSH - CAPTEUR GRANULOMETRIQUE
//

int sense = 0;

// Encodeur rotatoire
#define encoder0PinA 2
#define encoder0PinB 4
#define Switch 3
volatile unsigned int encoder0Pos = 0;

//Potentiomètre
#include <SPI.h>

//OLED
#include <Adafruit_SSD1306.h>
#define nombredDePixelsEnLargeur 128
#define nombredePixelsEnHauteur 64
#define brocheResetOLED -1
#define adresseI2CecranOLED 0x3C
Adafruit_SSD1306 ecranOLED(nombredDePixelsEnLargeur, nombredePixelsEnHauteur, &Wire, brocheResetOLED);
int l=0;

const byte csPin = 10;
const int maxPositions = 256;
const long rAB = 46300;

const byte rWiper = 125;
const byte pot0 = 0x11;
const byte pot0Shutdown  = 0x21;
long resistanceWB;

int potar=6;


#define PRINCIPAL 0
#define TEST 1
#define CHECK 2
#define INFO 3
int clic=1;
int menu=0;

void setup() {
  Serial.begin(9600);

  digitalWrite(csPin, HIGH);
  pinMode(csPin, OUTPUT);
  SPI.begin();


  if(!ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED)){
    while(1);
  }
  ecranOLED.setTextSize(2); //mettre t pour faire zoomer
  ecranOLED.setTextColor(SSD1306_WHITE);

  //pour l'encodeur rotatoire
  pinMode(encoder0PinA, INPUT);
  digitalWrite(encoder0PinA, HIGH);
  
  pinMode(encoder0PinB, INPUT);
  digitalWrite(encoder0PinB, HIGH);

  attachInterrupt(0,doEncoder,RISING);
  pinMode(Switch, INPUT_PULLUP);
  attachInterrupt(1,doSwitch,FALLING);
}




void loop() {
  clic=1;
  encoder0Pos = 0;
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

  
  // Partie OLED
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 0);
  ecranOLED.setTextColor(SSD1306_WHITE);
  
  if(encoder0Pos==1) // le faire sous forme de tableaux 
  {
    if (l<2){l+=1;}
    else {l=0;}
  }
  
  if (menu==PRINCIPAL)
  {
    if(l==0)
    {
      ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      ecranOLED.println("TEST");
      ecranOLED.setTextColor(SSD1306_WHITE);
      ecranOLED.println("CHECK");
      ecranOLED.println("INFO");
      if(clic==0){menu=TEST;}
    }
    else if(l==1)
    {
      ecranOLED.println("TEST");
      ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      ecranOLED.println("CHECK");
      ecranOLED.setTextColor(SSD1306_WHITE);
      ecranOLED.println("INFO");
      if(clic==0){menu=CHECK;}
    }
    else
    {
      ecranOLED.println("TEST");
      ecranOLED.println("CHECK");
      ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      ecranOLED.println("INFO");
      if(clic==0){menu=INFO;}
    }
  }

  else if (menu==TEST)
  {
    ecranOLED.println("Version 3");
    ecranOLED.println("Test ?");
    if(clic==0){menu=PRINCIPAL;}
  }

  else if (menu==CHECK)
  {
    ecranOLED.println("Ampli OK");
    if(clic==0){menu=PRINCIPAL;}
  }
  
  else if (menu==INFO)
  {
    ecranOLED.println("Output : ");
    ecranOLED.print(output);
    ecranOLED.println(" V");
    ecranOLED.println("R2 : ");
    ecranOLED.print(resistanceWB);
    ecranOLED.print(" Ohms");
    if(clic==0){menu=PRINCIPAL;}
  }

  
  ecranOLED.display();
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


void doSwitch()
{
  clic = 0;
}


void doEncoder()
{
  encoder0Pos=1;
}
