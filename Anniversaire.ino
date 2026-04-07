#include <LiquidCrystal.h>

int codes[4] = {0, 0, 0, 0};         //c1 à c4
int boutons[4] = {3, 4, 5, 6};       //btn1 à btn4
int confirm = 2;
String mdp = "7 8 1 7";
int buzz = 7;
int tones[10] = {500, 600, 700, 800, 900, 1000, 1200, 1500, 1700, 1900};
int delays[10] = {900, 800, 700, 600, 500, 400, 300, 200, 150, 100};

LiquidCrystal lcd(12, 11, 10, 8, 9, 13);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Wpisz kod");
  for (int i = 0; i < 4; i++) {
    pinMode(boutons[i], INPUT);
  }
  pinMode(buzz, OUTPUT);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(boutons[i]) == HIGH) {
      codes[i]++;
      if (codes[i] > 9) codes[i] = 0; 
      delay(200);
    }
  }

  //Affichage
  String mess = String(codes[0]) + " " + codes[1] + " " + codes[2] + " " + codes[3];

  if (digitalRead(confirm) == HIGH) {
  if (mess == mdp) {
    lcd.setCursor(0, 0);
    lcd.print("                ");  
    lcd.setCursor(0, 0);
    lcd.print("urodziny !");
    lcd.setCursor(0, 1);
    delay(1000);
    lcd.print("Otwór...");
    for (int i = 0; i < 10; i++) {
      tone(buzz, tones[i]);     
      delay(100);                    
      noTone(buzz);        
      delay(delays[i]);
      }
    for (int i = 0; i < 3; i++) {
    tone(buzz, 200); delay(100);
    tone(buzz, 1500); delay(100);
  }
  noTone(buzz);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("Nieprawidłowy");
    delay(2000);
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("Wpisz kod");
  }
}
  
  lcd.setCursor(0, 1);
  lcd.print("                ");  //effacer la ligne avec 16 espaces
  lcd.setCursor(0, 1);
  lcd.print(mess);
  delay(150);
}
