 #include <Stepper.h>
 #define STEPS 64 //nombre de pas du moteur sur un tour
  
Stepper small_stepper_Mtri(STEPS, 29, 25, 27, 23);  // déclaration des pins de sortie
Stepper small_stepper_Mcup(STEPS, 37, 33, 35, 31);  // déclaration des pins de sortie
Stepper small_stepper_Mbras(STEPS, 45, 41, 43, 39);  // déclaration des pins de sortie
int  Steps2Take_Mtri = 0;  //Nombre de pas de rotation demandé au moteur
int  Steps2Take_Mcup = 0;  //Nombre de pas de rotation demandé au moteur
int  Steps2Take_Mbras = 0;  //Nombre de pas de rotation demandé au moteur
  
void setup() 
 {      
  small_stepper_Mtri.setSpeed(300);
  small_stepper_Mcup.setSpeed(300);
  small_stepper_Mbras.setSpeed(100);   
 }  
 
 void loop()
 {
  Steps2Take_Mbras=-2048*0.75;
  small_stepper_Mbras.step(Steps2Take_Mbras);  // le bras se baisse
  delay(2000),
  Steps2Take_Mbras=2048*0.75;
  small_stepper_Mbras.step(Steps2Take_Mbras);  // le bras se baisse
 }
