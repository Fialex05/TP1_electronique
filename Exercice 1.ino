int k = 4;
int valuesBPstop = 0;
int valuesBPstart = 0;

void setup() {
  //définition des pins 2 et 3 comme des entrées (boutons)
  pinMode(2, INPUT); // bouton stop
  pinMode(3, INPUT); // bouton start

  //Définition des pins 4 à 13 comme des sorties (leds)
  for(int i = 4; i <= 13; i++){
    pinMode(i, OUTPUT);
  }
}

void stop(){
  // attend que le bouton start soit préssé
  while(valuesBPstart == 0){
    valuesBPstart = digitalRead(3);
  }
  valuesBPstart = 0; // remise de la valeurs à 0
}

void loop() {
  //On allume les leds successivements avec un delais de 0.5 sec
  for(; k < 13; k++){
    //Lecture de l'état du bouton
    valuesBPstop = digitalRead(2);
    //Si le bouton est pressé (=1), on arrete la lumière
    if (valuesBPstop == 1){
      stop();
    }
    //La led s'allume
    digitalWrite(k, HIGH);
    delay(500);
    //La led s'éteint
    digitalWrite(k, LOW);
  }

  //On éteind les leds successivements avec un delais de 0.5 sec
  for(; k > 4; k--){
    //Lecture de l'état du bouton
    valuesBPstop = digitalRead(2);
    //Si le bouton est pressé (=1), on arrete la lumière
    if (valuesBPstop == 1){
      stop();
    }
    //La led s'allume
    digitalWrite(k, HIGH);
    delay(500);
    //La led s'éteint
    digitalWrite(k, LOW);
  }
}
