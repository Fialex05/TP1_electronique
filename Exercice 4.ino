#include <Wire.h>
#include <LiquidCrystalI2C.h>
#include <RTClib.h>
 
LiquidCrystalI2C lcd(0x27, 20, 4);  // Initialisation de l'écran LCD (adresse 0x27, 20x4)
RTCDS1307 rtc;                      // Initialisation du module RTC DS1307
 
void setup() {
  lcd.init();            // Initialise l'écran LCD
  lcd.backlight();       // Allume le rétroéclairage de l'écran
  Wire.begin();          // Initialise la communication I2C
  rtc.begin();           // Initialise le module RTC
 
  // Vérifie si le RTC est en marche, sinon initialise avec la date et l'heure de compilation
  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(_DATE), F(__TIME)));
  }
}
 
void loop() {
  DateTime now = rtc.now();  // Permet d'obtenir l'heure et la date en temps réels
 
  // Affichage de la date
  lcd.setCursor(0, 0);
  lcd.print("Date: ");
  lcd.print(formatDeuxChiffres(now.day()));
  lcd.print("/");
  lcd.print(formatDeuxChiffres(now.month()));
  lcd.print("/");
  lcd.print(now.year(), DEC);
 
  // affichage de l'heure
  lcd.setCursor(0, 1);
  lcd.print("Heure: ");
  lcd.print(formatDeuxChiffres(now.hour()));
  lcd.print(":");
  lcd.print(formatDeuxChiffres(now.minute()));
  lcd.print(":");
  lcd.print(formatDeuxChiffres(now.second()));
 
  // Affiche les noms
  lcd.setCursor(0, 2);
  lcd.print("Vincent GENTET");
  lcd.setCursor(0, 3);
  lcd.print("Alexis FIGERE");
 
  delay(1000);  // attends 1 secondes
}
 
// Fonction pour afficher les nombres sur deux chiffres
String formatDeuxChiffres(int nombre) {
  if (nombre < 10) {
    return "0" + String(nombre); // Ajoute un 0 avant le nombre s'il est est inférieur à 10
  } else {
    return String(nombre);
  }
}
