#include <LiquidCrystal_I2C.h>
#include <Keypad.h>


// Définition de l'écran LCD (20 colonnes, 4 lignes)
LiquidCrystal_I2C lcd(0x27,20,4);

// Définition du pavé numérique
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {4, 5, 6, 7};
byte colPins[COLS] = {8, 9, 10, 11};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Initialisation des codes maître et esclave
String codeMaitre = "0000";
String codeEsclave = "1111";
String inputCode = ""; // Code actuellement saisi

// LED qui s'allume lors de l'ouverture de la porte
int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  lcd.begin(20, 4);
  lcd.backlight(); //activation du rétroéclairage

  //affichage demander dans l'énoncer sur l'écran LCD
  lcd.setCursor(0, 0);
  lcd.print("123A  Code:");
  lcd.setCursor(0, 1);
  lcd.print("456B");
  lcd.setCursor(0, 2);
  lcd.print("789C");
  lcd.setCursor(0, 3);
  lcd.print("*0#D");
  lcd.setCursor(0,10);
  
  // Démarrer la communication avec le moniteur série
  Serial.begin(9600);
  Serial.println("Enter Code:");
}

void loop() {
  char key = customKeypad.getKey(); // récupère le bouton appuyé par l'utilisateur
  if (key) { // vérifie que le bouton appuyé soit valide
    if (key == 'A') {
      // Vérification du code pour ouverture
      lcd.setCursor(11,1); // positionne le curseur pour afficher "open" ou "error"
      if (inputCode == codeMaitre || inputCode == codeEsclave) { // si le code entré est correct
        lcd.print("OPEN"); // affichage de "OPEN" sur l'écran
        Serial.println("OPEN");  // Affichage dans le moniteur série
        digitalWrite(ledPin, HIGH); // Allume la LED
      } else {
        lcd.print("ERROR"); // affichage de "ERROR" sur l'écran
        Serial.println("ERROR");  // Affichage dans le moniteur série
      }
      delay(3000); // wait for 3000 milliseconds
      digitalWrite(ledPin, LOW); // Éteint la LED
      //efface les messages
      lcd.setCursor(11,0);
	    lcd.print("        ");
      lcd.setCursor(11,1);
      lcd.print("      ");
      Serial.println("Enter Code:");  // Affichage dans le moniteur série
      inputCode = ""; // Réinitialise le code saisi
    } 
    else if (key == 'B') {
      // le code maitre rentré est mauvais
      if (inputCode != codeMaitre){
        lcd.setCursor(11,1);
        lcd.print("ERROR");
      	Serial.println("Le Master code est mauvais");
      }
      else{
        // Changement des codes (si le code maître est correct)
        lcd.setCursor(11,0);
		    lcd.print("        ");
        lcd.setCursor(11, 0);
        Serial.println("Enter Master Code:");  // Affichage dans le moniteur série
        
        //récupère les 4 prochaines entrées pour vérifier de nouveau le code maitre
        inputCode = ""; // Réinitialisation avant saisie
        while (inputCode.length() < 4) {
          key = customKeypad.getKey();
          if (key) {
            inputCode += key;
            lcd.print(key);
            Serial.print(key);  // Affichage dans le moniteur série
          }
        }
        lcd.setCursor(11, 0);
        delay(300);
        if (inputCode == codeMaitre) {
          // Demande du nouveau code maître
          lcd.setCursor(11,0);
		      lcd.print("      ");
          // l'utilisateur doit entrer 1 pour le code maitre et 2 pour le code esclave
          Serial.println("\nMaster Code : 1\nSlaved Code : 2");
          inputCode = "";
          while (inputCode.length() < 1) {
            key = customKeypad.getKey();
            if (key) {
              inputCode += key;
              lcd.print(key);
              Serial.print(key);  // Affichage dans le moniteur série
            }
          }
          lcd.setCursor(11, 0);
          if (inputCode == "1"){
            //si l'utilisateur veut changer le code maitre
            lcd.setCursor(11,0);
			      lcd.print("        ");
            Serial.println("\nNew Master Code:");  // Affichage dans le moniteur série
            inputCode = ""; // Réinitialisation avant saisie
            lcd.setCursor(11, 0);
            while (inputCode.length() < 4) {
              key = customKeypad.getKey();
              if (key) {
                inputCode += key;
                lcd.print(key);
                Serial.print(key);  // Affichage dans le moniteur série
              }
            }
            
			      String input = "";
            while (input.length() < 1) {
              key = customKeypad.getKey();
              if (key) {
                input += key;
              }
            }
            //l'utilisateur valide son nouveau code maitre en appuyant sur "C", sinon il garde l'ancien
            if(input == "C"){
              codeMaitre = inputCode;
              lcd.setCursor(11,0);
			        lcd.print("        ");
              Serial.println("\nMaster Code Updated");  // Affichage dans le moniteur série
              delay(1000);
            }
            inputCode = "";
            lcd.setCursor(11, 0);
          }
          else if (inputCode == "2"){
            //l'utilisateur veut changer le code esclave
            lcd.setCursor(11,0);
			      lcd.print("        ");
            lcd.setCursor(11,0);
            Serial.println("\nNew slave Code:");  // Affichage dans le moniteur série
            inputCode = ""; // Réinitialisation avant saisie
            while (inputCode.length() < 4) {
              key = customKeypad.getKey();
              if (key) {
                inputCode += key;
                lcd.print(key);
                Serial.print(key);  // Affichage dans le moniteur série
              }
            }
            String input = "";
            while (input.length() < 1) {
              key = customKeypad.getKey();
              if (key) {
                input += key;
              }
            }
            //l'utilisateur valide son nouveau code esclave en appuyant sur "C", sinon il garde l'ancien
            if(input == "C"){
              codeEsclave = inputCode;
              lcd.setCursor(11,0);
			        lcd.print("        ");
              Serial.println("\Slave Code Updated");  // Affichage dans le moniteur série
              delay(1000);
            }
            inputCode = "";
            lcd.setCursor(11, 0);
          }
        } 
        else {
          //le code maitre resaisie est le mauvais
          lcd.setCursor(11, 1);
          lcd.print("ERROR");
          Serial.println("ERROR");  // Affichage dans le moniteur série
        }
      }
      //réinitialisation de l'affichage
      delay(1000);
      lcd.setCursor(11,0);
	    lcd.print("        ");
      lcd.setCursor(11,1);
	    lcd.print("        ");
      inputCode = ""; // Réinitialisation
      Serial.println("Enter Code:");  // Affichage dans le moniteur série
    }
    else {
      // Ajout des touches dans le code actuel
      inputCode += key;
      lcd.setCursor(11,0);;
      lcd.print(inputCode);
      Serial.println(inputCode);  // Affichage dans le moniteur série
    }
  }
}
