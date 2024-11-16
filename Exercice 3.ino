#include <LiquidCrystal_I2C.h>

//déclaration des variables
int seconds = 0;
int minutes = 0;
int heures = 0;

//déclaration de l'écran
LiquidCrystal_I2C lcd(0x27,20,4);

void setup()
{
  lcd.begin(20,4);
  lcd.backlight(); // active le rétroéclairage
  lcd.print("02/10/2024"); // affiche la date sur la première ligne
  lcd.setCursor(0, 2); //positionne le curseur au début de la troisième ligne
  lcd.print("Vincent GENTET"); // affiche le prénom et le nom sur l'écran
  lcd.setCursor(0, 3); //positionne le curseur au début de la quatrième ligne
  lcd.print("Alexis FIGERE"); // affiche le prénom et le nom sur l'écran
  
  heures = 16;
  minutes = 58;
  seconds = 57;
}

void loop()
{
  lcd.setCursor(0, 1); //positionne le curseur au début de la deuxième ligne
  lcd.print(heures);
  lcd.print("h ");
  lcd.print(minutes);
  lcd.print("min ");
  lcd.print(seconds);
  lcd.print("sec  ");
  delay(1000); // Wait for 1000 millisecond(s)
  seconds += 1;
  if (60 <= seconds) { // ajout d'une minute si les secondes sont supérieures à 59
    seconds = 0;
    minutes += 1;
    if (60 <= minutes) { // ajout d'une heure si les minutes sont supérieures à 59
      minutes = 0;
      heures += 1;
    }
  }
}
