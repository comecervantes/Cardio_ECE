#include <Arduino.h>

//oled

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int pot = A3;
const int boutton = 6; 

int etatbt; 
int valeur_potentiometre; 

//oled 
//bpm 

#define nombre_valeurs 4
#define seuil 4

const int ledV = 2;
const int ledJ = 3;
const int ledR = 4;

const int buzzer = 5; 

const int iDuino = A7;

float valeurs[nombre_valeurs], somme, derniere_valeur, graphe, debut, premier, second, troisieme, valeur_precedente, bpm, liste_valeurs_bpm[2];
long int actuel, i, dernier_bpm;
int bpm_min = 50, bpm_max = 180, nombre_pics, n, note; 
bool pic;

//bpm 

void setup() {

  pinMode(ledV, OUTPUT);
  pinMode(ledJ, OUTPUT);
  pinMode(ledR, OUTPUT);

  pinMode(boutton, INPUT);

digitalWrite(ledV, LOW);
digitalWrite(ledJ, LOW);
digitalWrite(ledR, LOW);

  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
  for(;;);  } 
  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3D)) {
    Serial.println(F("SSD1306 allocation failed"));
  for(;;);  } 

    Serial.begin(115200);

}

void loop ()
{

  etatbt = digitalRead(boutton); 

    for (int i = 0; i < nombre_valeurs; i++)
      valeurs[i] = 0;
    somme = 0;
    i = 0;

    while(1)
    {
      n = 0;
      debut = millis();
      graphe = 0.;
      do
      {
        graphe += analogRead(iDuino);
        n++;
        actuel = millis();
      }
      while (actuel < debut + 20);  
      graphe /= n;  
      
      somme -= valeurs[i];
      somme += graphe;
      valeurs[i] = graphe;
      derniere_valeur = somme / nombre_valeurs;

      if (derniere_valeur > valeur_precedente)
      {
        nombre_pics++;
        if (!pic && nombre_pics > seuil)
        {
          pic = true;
          premier = millis() - dernier_bpm;
          dernier_bpm = millis();

          bpm = 60000. / (0.4 * premier + 0.3 * second + 0.3 * troisieme);

          troisieme = second;
          second = premier;
          
        }
      }
      
      else
      {
        pic = false;
        nombre_pics = 0;
      }
      valeur_precedente = derniere_valeur;
      
      i++;
      i %= nombre_valeurs;

  if( bpm <= bpm_min){
    bpm = bpm_min;
  }
  else if(bpm >= bpm_max){
    bpm = bpm_max;
  }

  for(int i = 0; i < 2; i++){
    liste_valeurs_bpm[i] = bpm; 

    if( liste_valeurs_bpm[1] >= liste_valeurs_bpm[0] + 10) {
      Serial.println(liste_valeurs_bpm[0]);
    }
        if( liste_valeurs_bpm[1] <= liste_valeurs_bpm[0] + 10) {
      Serial.println(liste_valeurs_bpm[0]);
    }
  }

  if(bpm < 60){
    digitalWrite(ledV, HIGH);
    digitalWrite(ledJ, LOW);
    digitalWrite(ledR, LOW);
    tone(buzzer, 359);
  }
  else if(bpm > 100){
    digitalWrite(ledV, LOW);
    digitalWrite(ledJ, LOW);
    digitalWrite(ledR, HIGH);
    tone(buzzer, 1782);

  }
  else {
    digitalWrite(ledV, LOW);
    digitalWrite(ledJ, HIGH);
    digitalWrite(ledR, LOW);
    tone(buzzer, 1489);

  }
  display.clearDisplay(); 

  Wire.beginTransmission(0x3C);
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
 
    display.setTextSize(1); //je definie la taille du texte et la position de celui ci 
    display.setTextColor(WHITE);
        display.setCursor(15,35);

        display.print("Tension: ");
            display.setTextSize(2);
  Wire.endTransmission();

  display.begin(SSD1306_SWITCHCAPVCC,0x3D);
  Wire.beginTransmission(0x3D);

    display.setTextSize(1); //je definie la taille du texte et la position de celui ci 
    display.setTextColor(WHITE);
        display.setCursor(15,35);

        display.print("Voltage: ");
            display.setTextSize(2);
  Wire.endTransmission();

    Serial.println(bpm);

delay(10);

    }
  
    display.clearDisplay(); 

  Wire.beginTransmission(0x3C);
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
 
    display.setTextSize(1); //je definie la taille du texte et la position de celui ci 
    display.setTextColor(WHITE);
        display.setCursor(15,35);

        display.print("Tension: ");

  Wire.endTransmission();

  display.begin(SSD1306_SWITCHCAPVCC,0x3D);
  Wire.beginTransmission(0x3D);

    display.setTextSize(1); //je definie la taille du texte et la position de celui ci 
    display.setTextColor(WHITE);
        display.setCursor(15,35);

        display.print("Voltage: ");

  Wire.endTransmission();

}