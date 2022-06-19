// définit les numéros de broches des drivers des deux moteurs pas à pas suiveur de ligne
const int stepPin_M1 = 3; // vitesse moteur 1  1 impulsion --> 1 pas
const int dirPin_M1 = 4;  // sens de rotation moteur 1
const int stepPin_M2 = 5; // vitesse moteur 2
const int dirPin_M2 = 6;  // sens de rotation moteur 2

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
}
void en_avant() {
  digitalWrite(dirPin_M1,HIGH); // Permet au moteur de se déplacer en avant
  digitalWrite(dirPin_M2,LOW);
  // Donne 2000 impulsions pour effectuer une rotation d'un cycle complet
  for(int x = 0; x < 12; x++) {
    digitalWrite(stepPin_M1,HIGH); 
    digitalWrite(stepPin_M2,HIGH);
    delayMicroseconds(3000); 
    digitalWrite(stepPin_M1,LOW); 
    digitalWrite(stepPin_M2,LOW);
    delayMicroseconds(3000); 
 }
  }

  void a_gauche() {
  digitalWrite(dirPin_M1,HIGH); // Permet au moteur de se déplacer en avant
  digitalWrite(dirPin_M2,LOW);
  // Donne 2000 impulsions pour effectuer une rotation d'un cycle complet
  
    for(int x = 0; x < 12; x++) {
    digitalWrite(stepPin_M1,HIGH); 
    delayMicroseconds(3000);
    digitalWrite(stepPin_M1,LOW);
    delayMicroseconds(3000);
    }
   //  for(int x = 0; x < 6; x++) {
  //  digitalWrite(stepPin_M2,HIGH);
   // delayMicroseconds(3000); 
   // digitalWrite(stepPin_M2,LOW);
   // delayMicroseconds(3000); 
// }
  }

  void a_droite() {
  digitalWrite(dirPin_M1,HIGH); // Permet au moteur de se déplacer en avant
  digitalWrite(dirPin_M2,LOW);
  // Donne 2000 impulsions pour effectuer une rotation d'un cycle complet
 
   // for(int x = 0; x < 6; x++) {
   // digitalWrite(stepPin_M1,HIGH); 
   // delayMicroseconds(3000);
   // digitalWrite(stepPin_M1,LOW);
    //delayMicroseconds(3000);
 //   }
     for(int x = 0; x < 12; x++) {
    digitalWrite(stepPin_M2,HIGH);
    delayMicroseconds(3000); 
    digitalWrite(stepPin_M2,LOW);
    delayMicroseconds(3000); 
 }
 }
  
  
  void loop() {
int num1,num2,num3;
num1=digitalRead(capteur_g);
num2=digitalRead(capteur_c);
num3=digitalRead(capteur_d);

if(num1==1&num2==0&num3==1)
{
  en_avant();
  delay(2);}
  
  else if(num1==1&num2==0&num3==0)
{
  a_gauche();
  delay(2);
    
}

else if(num1==0&num2==0&num3==1)
{
  a_droite();
  delay(2);
  
}

  
  }
