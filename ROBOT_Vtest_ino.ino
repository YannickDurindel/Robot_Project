#include <Stepper.h>
#define STEPS 64 //nombre de pas du moteur sur un tour
int state = 0;
Stepper small_stepper_Mtri(STEPS, 29, 25, 27, 23);  // déclaration des pins de sortie
int  Steps2Take_Mtri = 0;  //Nombre de pas de rotation demandé au moteur
const int interruptin = 51;
const int interruptout = 53;
 
void setup() {
  pinMode(interruptin,INPUT);
  pinMode(interruptout,OUTPUT); 
  small_stepper_Mtri.setSpeed(300);
}

void tri () {
  Steps2Take_Mtri=2048;  //le moteur de tri fait 3 tours pour laisser passer 3tours*3trous = 9 billes
  small_stepper_Mtri.step(Steps2Take_Mtri);
}

void loop() {
  switch (state) {
    case 0:
      digitalWrite(interruptout,HIGH);
      if (digitalRead(interruptin)==1)
        state = 1;
      break;
        
    case 1:
      tri();
      state = 0;
      break;
  }
}
