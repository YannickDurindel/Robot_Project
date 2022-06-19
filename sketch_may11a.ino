#include <Stepper.h>
#define STEPS 64 //nombre de pas du moteur sur un tour
const int stepPin_M1 = 3; // vitesse moteur 1  1 impulsion --> 1 pas
const int dirPin_M1 = 4;  // sens de rotation moteur 1
const int stepPin_M2 = 5; // vitesse moteur 2
const int dirPin_M2 = 6;  // sens de rotation moteur 2
int state = 0;
int counter = 0;
Stepper small_stepper_Mtri(STEPS, 29, 25, 27, 23);  // déclaration des pins de sortie
Stepper small_stepper_Mcup(STEPS, 37, 33, 35, 31);  // déclaration des pins de sortie
Stepper small_stepper_Mbras(STEPS, 45, 41, 43, 39);  // déclaration des pins de sortie
int  Steps2Take_Mtri = 0;  //Nombre de pas de rotation demandé au moteur
int  Steps2Take_Mcup = 0;  //Nombre de pas de rotation demandé au moteur
const int stepPin_Mbras = 10; // vitesse moteur bras
const int dirPin_Mbras = 11;  // sens de rotation moteur bras


// définit les numéros des 3 capteurs de ligne gauche centre droit
const int capteur_g = 7; 
const int capteur_c = 8; 
const int capteur_d = 9; 
 
void setup() {
  // Définit les quatre broches comme sorties
  pinMode(stepPin_M1,OUTPUT); 
  pinMode(dirPin_M1,OUTPUT);
  pinMode(stepPin_M2,OUTPUT); 
  pinMode(dirPin_M2,OUTPUT);
  pinMode(stepPin_Mbras,OUTPUT); 
  pinMode(dirPin_Mbras,OUTPUT);
  // définit les numéros des 3 capteurs de ligne gauche centre droit comme entrées
  pinMode(capteur_g,INPUT); 
  pinMode(capteur_c,INPUT);
  pinMode(capteur_d,INPUT); 
  small_stepper_Mtri.setSpeed(300);
  small_stepper_Mcup.setSpeed(300);
}

void en_avant() {
  digitalWrite(dirPin_M1,LOW); // Permet au moteur de se déplacer en avant
  digitalWrite(dirPin_M2,HIGH);
  // Donne 2000 impulsions pour effectuer une rotation d'un cycle complet
  digitalWrite(stepPin_M1,HIGH); 
  digitalWrite(stepPin_M2,HIGH);
  delayMicroseconds(3000); 
  digitalWrite(stepPin_M1,LOW); 
  digitalWrite(stepPin_M2,LOW);
  delayMicroseconds(3000); 
}

void tri () {
  Steps2Take_Mtri=6144;  //le moteur de tri fait 3 tours pour laisser passer 3tours*3trous = 9 billes
  small_stepper_Mtri.step(Steps2Take_Mcup);
}

void grab_cup () {
    
  digitalWrite(dirPin_Mbras,HIGH);    // le bras se baisse
  for(int x = 0; x < 180; x++) {
    digitalWrite(stepPin_Mbras,HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin_Mbras,LOW);}
    
  Steps2Take_Mcup=2048*4;
  small_stepper_Mcup.step(Steps2Take_Mcup);  //la courroie se ressère sur le verre
  
  digitalWrite(dirPin_Mbras,LOW);    // le bras se relève
  for(int x = 0; x < 210; x++) {
    digitalWrite(stepPin_Mbras,HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin_Mbras,LOW);}
    
  delay(2000);                           //attend que les billes se déversent

  digitalWrite(dirPin_Mbras,HIGH);    // le bras se rebaisse
  for(int x = 0; x < 210; x++) {
    digitalWrite(stepPin_Mbras,HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin_Mbras,LOW);}
    
  Steps2Take_Mcup=-2048*3.5;
  small_stepper_Mcup.step(Steps2Take_Mcup);  //la courroie se déserre
  
  digitalWrite(dirPin_Mbras,LOW);    // le bras se relève
  for(int x = 0; x < 180; x++) {
    digitalWrite(stepPin_Mbras,HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin_Mbras,LOW);}
}

void loop() {
  grab_cup();
  tri();
  delay(5000);
}
