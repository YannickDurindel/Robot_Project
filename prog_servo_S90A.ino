#include <Servo.h>   // inclusion de la bibliothèque du servomoteur
 Servo monservo;  // crée l’objet pour contrôler le servomoteur
 
void setup()
{
  monservo.attach(7);  // utilise la broche 7 pour le contrôle du servomoteur
  monservo.write(0);    // positionne le servomoteur à 0°
}
 
void loop()
{
  monservo.write(0);
  delay(1000);                     // pause 1 seconde
  monservo.write(10);      // positionne le servo à 20°
  delay(1000);
  monservo.write(20);      // positionne le servo à 20°
  delay(1000);
  monservo.write(70);       // positionne le servo à 70°
  delay(1000);
  monservo.write(150);    // positionne le servo  à  150°
  delay(1000);
}
 


