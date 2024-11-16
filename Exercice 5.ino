// C++ code
//
#include <Servo.h>

//déclaration des variables pour savoir quand une photorésistance à détecter une présence
int nbtourp1 = 0;
int nbtourp2 = 0;

Servo servo_7;

void setup()
{
  //servomoteur sur le pin 7
  servo_7.attach(7, 500, 2500);
  //Photorésistances sur les entrées analogiques A0 et A1
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

void loop()
{
  if (nbtourp1 > 0) { 
    nbtourp1 += -1;
  }
  if (nbtourp2 > 0) {
    nbtourp2 += -1;
  }
  if (analogRead(A0) < 400) { // la valeur de luminosité est inférieur à 400 donc il y a quelque chose qui est passée par dessus
    nbtourp1 = 20; // l'utilisateur à 2 sec pour passer devant l'autre photorésistance
  }
  if (analogRead(A1) < 400) { // la valeur de luminosité est inférieur à 400 donc il y a quelque chose qui est passée par dessus
    nbtourp2 = 20; // l'utilisateur à 2 sec pour passer devant l'autre photorésistance
  }
  if ((nbtourp1 > 0 && nbtourp2 > 0) && nbtourp1 != nbtourp2) { // vérifie si l'utilisateur est passé au dessus des deux photorésistances
    if (nbtourp1 > nbtourp2) { // l'utilisateur à passé sa main de droite à gauche
      servo_7.write(180); // on positionne le servomoteur vers la gauche
    } else { // l'utilisateur à passé sa main de gauche à droite
      servo_7.write(0); // on positionne le servomoteur vers la droite
    }
    delay(2000); // Wait for 2000 millisecond(s)
    servo_7.write(90); // on repositionne le servomoteur à sa position d'origine
    nbtourp1 = 0; //réinitialisation du délais
    nbtourp2 = 0; //réinitialisation du délais
  }
  //affichage des valeurs des photorésistances dans la console
  Serial.print(analogRead(A0));
  Serial.print(" ");
  Serial.println(analogRead(A1));
  
  delay(100); // Wait for 100 millisecond(s)
}
