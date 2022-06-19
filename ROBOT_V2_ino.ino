// définit les numéros de broches des drivers des deux moteurs pas à pas suiveur de ligne
const int stepPin_M1 = 3; // vitesse moteur 1  1 impulsion --> 1 pas
const int dirPin_M1 = 4;  // sens de rotation moteur 1
const int stepPin_M2 = 5; // vitesse moteur 2
const int dirPin_M2 = 6;  // sens de rotation moteur 2
int state = 0;
int counter = 0;

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
  digitalWrite(dirPin_M1,LOW); // Permet au moteur de se déplacer en avant
  digitalWrite(dirPin_M2,HIGH);
  // Donne 2000 impulsions pour effectuer une rotation d'un cycle complet
  for(int x = 0; x < 6; x++) {
    digitalWrite(stepPin_M1,HIGH); 
    digitalWrite(stepPin_M2,HIGH);
    delayMicroseconds(3000); 
    digitalWrite(stepPin_M1,LOW); 
    digitalWrite(stepPin_M2,LOW);
    delayMicroseconds(3000); 
  }
}

  void a_gauche() {
  digitalWrite(dirPin_M1,LOW); // Permet au moteur de se déplacer en avant
  digitalWrite(dirPin_M2,HIGH);
  // Donne 2000 impulsions pour effectuer une rotation d'un cycle complet
  for(int x = 0; x < 6; x++) {
    digitalWrite(stepPin_M1,HIGH); 
    delayMicroseconds(3000);
    digitalWrite(stepPin_M1,LOW);
    delayMicroseconds(3000);
  }
}

  void a_droite() {
  digitalWrite(dirPin_M1,LOW); // Permet au moteur de se déplacer en avant
  digitalWrite(dirPin_M2,HIGH);
  // Donne 2000 impulsions pour effectuer une rotation d'un cycle complet
  for(int x = 0; x < 6; x++) {
    digitalWrite(stepPin_M2,HIGH);
    delayMicroseconds(3000); 
    digitalWrite(stepPin_M2,LOW);
    delayMicroseconds(3000); 
   }
 }

  void demi_tour () {
  delay(2000);
  digitalWrite(dirPin_M1,HIGH);
  digitalWrite(dirPin_M2,LOW);
  for(int x = 0; x < 70; x++) {
    digitalWrite(stepPin_M1,HIGH);
    digitalWrite(stepPin_M2,HIGH);
    delayMicroseconds(8000);
    digitalWrite(stepPin_M1,LOW);
    digitalWrite(stepPin_M2,LOW);
  }
  delay(500);
  digitalWrite(dirPin_M1,HIGH);
  digitalWrite(dirPin_M2,HIGH);
  for(int x = 0; x < 200; x++) {
    digitalWrite(stepPin_M1,HIGH);
    digitalWrite(stepPin_M2,HIGH);
    delayMicroseconds(8000); 
    digitalWrite(stepPin_M1,LOW);
    digitalWrite(stepPin_M2,LOW);
    delayMicroseconds(8000);
  }
  do {
    digitalWrite(stepPin_M1,HIGH);
    digitalWrite(stepPin_M2,HIGH);
    delayMicroseconds(8000); 
    digitalWrite(stepPin_M1,LOW);
    digitalWrite(stepPin_M2,LOW);
    delayMicroseconds(8000);
  }
  while (digitalRead(capteur_g)==0 or digitalRead(capteur_c)==1 or digitalRead(capteur_d) == 0) ;
  
  digitalWrite(stepPin_M1,LOW);
  digitalWrite(stepPin_M2,LOW);
  return ;
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
      if(counter==1)
        counter = 0;
        state = 4;
      demi_tour();
      if(digitalRead(capteur_g)==1&digitalRead(capteur_c)==0&digitalRead(capteur_d)==1)
        state = 0;
      if((digitalRead(capteur_g)==0&digitalRead(capteur_c)==0&digitalRead(capteur_d)==1)or(digitalRead(capteur_g)==0&digitalRead(capteur_c)==1&digitalRead(capteur_d)==1))
        state = 1;
      if((digitalRead(capteur_g)==1&digitalRead(capteur_c)==0&digitalRead(capteur_d)==0)or(digitalRead(capteur_g)==1&digitalRead(capteur_c)==1&digitalRead(capteur_d)==0))
        state = 2;
      break;
      
    case 4:
      delay(60000);
      demi_tour();
      state = 0;
}
  }
