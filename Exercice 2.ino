int button1State = 0;
int button2State = 0;

void setup()
{
  for(int i = 9; i <= 13; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(2, INPUT);
  pinMode(3, INPUT);
}

void stop() {
  // Éteint toutes les LEDs
  for (int i = 9; i <= 13; i++) {
    digitalWrite(i, LOW);
  }
}

void loop() {
  // Lis l'état des boutons
  button1State = digitalRead(2);
  button2State = digitalRead(3);

// Fonction ET
  if (button1State && button2State) {
    digitalWrite(13, HIGH);  // LED 13 ON
  }

  // Fonction OU
  if (button1State || button2State) {
    digitalWrite(12, HIGH);  // LED 12 ON
  }

  // Fonction NOR
  if (!(button1State || button2State)) {  // NOR
    digitalWrite(11, HIGH);  // LED 11 ON
  }

  // Fonction NAND
  if (!(button1State && button2State)) {  // NAND
    digitalWrite(10, HIGH);  // LED 10 ON
  }

  // Fonction XOR
  if (button1State ^ button2State) {  // XOR
    digitalWrite(9, HIGH);  // LED 9 ON
  }

  stop();
}
