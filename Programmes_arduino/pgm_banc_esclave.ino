#include<Servo.h>
Servo myservo;// create servo object to control a servo
// 

///////////////////// VARIABLES BANC DE TEST
int nbCycles = 5; // nombre de cycles
int iCase = 0; // variable pour le switch case de la fonction cycle()
int cycleAccomplis = 0;
int deltaTheta = 5;
int SortieAngle = 4;
int y =0;
int x = deltaTheta; // incrément de degrés pour banc

//////////////////// VARIABLES Flex sensor
const int flexPin = A1;
float Vflex = 0;
const float VCC = 5;
const float R_DIV = 46500.0;
const float flatResistance = 26500.0;//resistance à plat
const float bendResistance = 53000.0; //resistance à 90°

/////////// TRIGGER
#define trigger 3
bool drapeau;



void setup() {
  
  pinMode(trigger, INPUT);
  attachInterrupt(1,cycle,RISING);
  
  myservo.attach(6); // connexion servo sur pin 6
  Serial.begin(9600); //serial port ini
  pinMode(flexPin, INPUT);
  myservo.write(x);

}

void loop() {
//MesureFlexSensor();
//cycle();
}



void cycle() {

  
  switch (iCase) {
    case 0:
      x = x + 1;
      myservo.write(x);
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
        if (x <= deltaTheta) {
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

//void MesureFlexSensor() {
//
//  //Flex
// int ADCflex = analogRead(flexPin);
// float Vflex = ADCflex * VCC /1023.0;
// float Rflex = R_DIV * (VCC / Vflex -1.0);
// Serial.println("resistance : " + String(Rflex) + "ohms");
// float angle = map(Rflex, flatResistance, bendResistance, 0, 90);
// Serial.println("Bend : " + String(angle) + " degrés");
// }