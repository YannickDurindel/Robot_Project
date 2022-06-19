#include <Stepper.h>
#define STEPS 64 //nombre de pas du moteur sur un tour
#include <Servo.h>   // inclusion de la bibliothèque du servomoteur
Servo monservo;  // crée l’objet pour contrôler le servomoteur
const int stepPin_M1 = 3; // vitesse moteur 1  1 impulsion --> 1 pas
const int dirPin_M1 = 4;  // sens de rotation moteur 1
const int stepPin_M2 = 5; // vitesse moteur 2
const int dirPin_M2 = 6;  // sens de rotation moteur 2
int state = 0;
int counter = 0;
Stepper small_stepper_Mtri(STEPS, 29, 25, 27, 23);  // déclaration des pins de sortie
int  Steps2Take_Mtri = 0;  //Nombre de pas de rotation demandé au moteur
Stepper small_stepper_Mcup(STEPS, 37, 33, 35, 31);  // déclaration des pins de sortie
int  Steps2Take_Mcup = 0;  //Nombre de pas de rotation demandé au moteur

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
  // définit les numéros des 3 capteurs de ligne gauche centre droit comme entrées
  pinMode(capteur_g,INPUT); 
  pinMode(capteur_c,INPUT);
  pinMode(capteur_d,INPUT); 
  monservo.attach(0);  // utilise la broche 7 pour le contrôle du servomoteur
  monservo.write(90);    // positionne le servomoteur à 90°
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

void a_gauche() {
  digitalWrite(dirPin_M1,LOW); // Permet au moteur de se déplacer en avant
  digitalWrite(dirPin_M2,HIGH);
  // Donne 2000 impulsions pour effectuer une rotation d'un cycle complet
  digitalWrite(stepPin_M1,HIGH); 
  delayMicroseconds(3000);
  digitalWrite(stepPin_M1,LOW);
  delayMicroseconds(3000);
}

void a_droite() {
  digitalWrite(dirPin_M1,LOW); // Permet au moteur de se déplacer en avant
  digitalWrite(dirPin_M2,HIGH);
  // Donne 2000 impulsions pour effectuer une rotation d'un cycle complet
  digitalWrite(stepPin_M2,HIGH);
  delayMicroseconds(3000); 
  digitalWrite(stepPin_M2,LOW);
  delayMicroseconds(3000); 
 }

void demi_tour () {
  delay(2000);
  digitalWrite(dirPin_M1,HIGH);
  digitalWrite(dirPin_M2,HIGH);
  do {
    digitalWrite(stepPin_M1,HIGH);
    digitalWrite(stepPin_M2,HIGH);
    delayMicroseconds(2000); 
    digitalWrite(stepPin_M1,LOW);
    digitalWrite(stepPin_M2,LOW);
    delayMicroseconds(2000);
  }
  while (digitalRead(capteur_g)==0 or digitalRead(capteur_c)==1 or digitalRead(capteur_d) == 0) ;
  
  digitalWrite(stepPin_M1,LOW);
  digitalWrite(stepPin_M2,LOW);
  return ;
}

void tri () {
  Steps2Take_Mcup=6144;  //le moteur de tri fait 3 tours pour laisser passer 3*3 = 9 billes
  small_stepper_Mcup.step(Steps2Take_Mcup);
}

void grab_cup () {
  // acting like the is no gear btw the servo and the stick R=1
  Steps2Take_Mcup=-6144;  //le moteur de la courroie du verre fait 3 tours pour se déserrer
  small_stepper_Mcup.step(Steps2Take_Mcup);
  monservo.write(0);  // le bras se baisse
  Steps2Take_Mcup=6144;  //le moteur de la courroie du verre fait 3 tours pour se reserrer
  small_stepper_Mcup.step(Steps2Take_Mcup);
  monservo.write(110); // le bras se lève et déverse le verre
  delay(2000);
  monservo.write(0); // le bras se baisse pour poser le verre
  Steps2Take_Mcup=-6144;  //le moteur de la courroie du verre fait 3 tours pour se déserrer
  small_stepper_Mcup.step(Steps2Take_Mcup);
  monservo.write(90); //le bras se relève
}
  
void loop() {
  switch (state) {
    case 0:
      en_avant();
      if((digitalRead(capteur_g)==0&digitalRead(capteur_c)==0&digitalRead(capteur_d)==1)or(digitalRead(capteur_g)==0&digitalRead(capteur_c)==1&digitalRead(capteur_d)==1))
        state = 1;
      if((digitalRead(capteur_g)==1&digitalRead(capteur_c)==0&digitalRead(capteur_d)==0)or(digitalRead(capteur_g)==1&digitalRead(capteur_c)==1&digitalRead(capteur_d)==0))
        state = 2;
      if(digitalRead(capteur_g)==0&digitalRead(capteur_c)==0&digitalRead(capteur_d)==0)
        state = 3;
      break;
        
    case 1:
      a_gauche();
      if(digitalRead(capteur_g)==1&digitalRead(capteur_c)==0&digitalRead(capteur_d)==1)
        state = 0;
      if((digitalRead(capteur_g)==1&digitalRead(capteur_c)==0&digitalRead(capteur_d)==0)or(digitalRead(capteur_g)==1&digitalRead(capteur_c)==1&digitalRead(capteur_d)==0))
        state = 2;
      if(digitalRead(capteur_g)==0&digitalRead(capteur_c)==0&digitalRead(capteur_d)==0)
        state = 3;
      break;
      
    case 2:
      a_droite();
      if(digitalRead(capteur_g)==1&digitalRead(capteur_c)==0&digitalRead(capteur_d)==1)
        state = 0;
      if((digitalRead(capteur_g)==0&digitalRead(capteur_c)==0&digitalRead(capteur_d)==1)or(digitalRead(capteur_g)==0&digitalRead(capteur_c)==1&digitalRead(capteur_d)==1))
        state = 1;
      if(digitalRead(capteur_g)==0&digitalRead(capteur_c)==0&digitalRead(capteur_d)==0)
        state = 3;
      break;
      
    case 3:
      if(counter==1){
        demi_tour();
        counter = 0;
        delay(60000);
        state = 0;
        break;}
      counter = 1;
      grab_cup();
      demi_tour();
      if(digitalRead(capteur_g)==1&digitalRead(capteur_c)==0&digitalRead(capteur_d)==1)
        state = 0;
      if((digitalRead(capteur_g)==0&digitalRead(capteur_c)==0&digitalRead(capteur_d)==1)or(digitalRead(capteur_g)==0&digitalRead(capteur_c)==1&digitalRead(capteur_d)==1))
        state = 1;
      if((digitalRead(capteur_g)==1&digitalRead(capteur_c)==0&digitalRead(capteur_d)==0)or(digitalRead(capteur_g)==1&digitalRead(capteur_c)==1&digitalRead(capteur_d)==0))
        state = 2;
      break;

}
  }
