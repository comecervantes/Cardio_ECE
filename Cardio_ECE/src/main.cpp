#include <Arduino.h>

#define nombre_valeurs 4
#define seuil 4

int ledV = 2;
int ledJ = 4;
int ledR = 7;

int buzzer = 9; 

int iDuino = A7;

float valeurs[nombre_valeurs], somme, derniere_valeur, graphe, debut, premier, second, troisieme, valeur_precedente, bpm, liste_valeurs_bpm[2];
long int actuel, i, dernier_bpm;
int bpm_min = 50, bpm_max = 180, nombre_pics, n, note; 
bool pic;

void setup() {

  pinMode(ledV, OUTPUT);
  pinMode(ledJ, OUTPUT);
  pinMode(ledR, OUTPUT);

digitalWrite(ledV, LOW);
digitalWrite(ledJ, LOW);
digitalWrite(ledR, LOW);

    Serial.begin(9600);
}

void loop ()
{
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

    Serial.println(bpm);

delay(10);

    }
}