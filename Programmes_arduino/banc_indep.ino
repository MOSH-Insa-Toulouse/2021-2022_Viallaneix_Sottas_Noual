#include<Servo.h>
Servo myservo;// create servo object to control a servo
// a maximum of eight servo objects can be created


///////////////////// VARIABLES BANC DE TEST
int nbCycles = 5; // nombre de cycles
int iCase = 0; // variable pour le switch case de la fonction cycle()
int x = 0; // incrément de degrés pour banc
int cycleAccomplis = 0;
int deltaTheta = 5;

//////////////////// VARIABLES Flex sensor
const int flexPin = A1;
float Vflex = 0;
const float VCC = 5;
const float R_DIV = 46500.0;
const float flatResistance = 26500.0;//resistance à plat
const float bendResistance = 53000.0; //resistance à 90°

/////////// TRIGGER
#define trigger 13
bool drapeau;



void setup() {
  myservo.attach(6); // connexion servo sur pin 6
  pinMode(trigger, INPUT);
   Serial.begin(9600); //serial port ini
   //setup flex
   pinMode(flexPin, INPUT);
   

}

void loop() {
 delay(50);

drapeau = digitalRead(trigger);
if (drapeau == HIGH){
  cycle();
  Serial.print("flag : \t");
  Serial.print(drapeau);
}
//MesureFlexSensor();

//cycle();
 
}


void cycle() {

  
  switch (iCase) {
    case 0:
      x = x + 1;
      myservo.write(x);
      Serial.print(cycleAccomplis);
      Serial.print("\t theta : ");
      Serial.print(x-90);
      Serial.println(" degrés");
        if (x >= ((90-deltaTheta)*2)) {iCase = 1;} // 
     //return x;
      break;
    case 1:
      x = x - 1;
      myservo.write(x-deltaTheta);
      Serial.print(cycleAccomplis);
      Serial.print("\t theta : ");
      Serial.print(x-deltaTheta);
      Serial.println(" degrés");
        if (x <= 0) {
          iCase = 0;
          cycleAccomplis += 1;}
        //if (nbcycle = nbmax){
          //iCase = 2;
        //}
       //break;
    //case 2:
      // break;
    default:
      break;
  }
}

void MesureFlexSensor() {

  //Flex
 int ADCflex = analogRead(flexPin);
 float Vflex = ADCflex * VCC /1023.0;
 float Rflex = R_DIV * (VCC / Vflex -1.0);
 Serial.println("resistance : " + String(Rflex) + "ohms");
 float angle = map(Rflex, flatResistance, bendResistance, 0, 90);
 Serial.println("Bend : " + String(angle) + " degrés");
 }





  
