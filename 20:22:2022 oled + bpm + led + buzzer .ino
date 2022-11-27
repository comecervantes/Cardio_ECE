 /*/
                                CARDIO - ECE 2022 
                                   _         _
                       __   ___.--'_`.     .'_`--.___   __
                      ( _`.'. -   'o` )   ( 'o`   - .`.'_ )
                      _\.'_'      _.-'     `-._      `_`./_
                     ( \`. )    //\`         '/\\    ( .'/ )
                      \_`-'`---'\\__,       ,__//`---'`-'_/
                       \`        `-\         /-'        '/
                       `                               '   
              Ce projet vous est proposé par ces quatre héros : 

Côme Cervantes ---- Florian Bonelli ---- Marco Ferrante ---- Jean-Félix Bertrand

21/11/2022

/*/

//===================================================================================//|
//                                                                                   //|
//                              BRANCHEMENTS :                                       //|
//                                                                                   //|
//                              Potentionmètre 1 -> A1                               //|
//                              Potentionmètre 2 -> A0                               //|
//                              Boutton 1 -> D11                                     //|
//                              Boutton 2 -> D7                                      //|
//                              Boutton 3 -> D5                                      //|
//                              Buzzer -> D6                                         //|
//                              Led V  -> D2                                         //|
//                              Led J  -> D3                                         //|
//                              Led R  -> D4                                         //|
//                              Oled 1 / 2  SDA  -> SDA A4                           //|
//                              Oled 1 / 2  SCL  -> SCL A5                           //|
//                              RTC CLK -> D10                                       //|
//                              RTC DAT -> D9                                        //|
//                              RTC RST -> D8                                        //|
//                              Capteur Iduino -> A2                                 //|
//                                                                                   //|
//===================================================================================//|

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerifItalic12pt7b.h>
#include <virtuabotixRTC.h>
#include <EEPROM.h>

// partie oled + menus 

  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 64

  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
  Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

  #define largeurDeLimage           20          // Largeur de l'image à afficher, en pixels
  #define hauteurDeLimage           20          // Hauteur de l'image à afficher, en pixels

  const int pot1 = A1; 
  int pot1_val; 
  int val_menu;
  int boutton = 11; 
  int ym1; 
  int state = 0; 
  int lg; 

  int afh; 
  int jj = 12; 
  int mm = 10; 
  int aa = 2022; 
  int hh; 
  int mnmn; 

  int pos;

  const unsigned char coeur [] PROGMEM = {
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0e, 0x00, 0x1f, 0x9f, 0x80, 0x1f, 
	  0x9f, 0x80, 0x3f, 0xff, 0xc0, 0x3f, 0xff, 0xc0, 0x3f, 0xff, 0xc0, 0x3f, 0xff, 0xc0, 0x1f, 0xff, 
	  0x80, 0x07, 0xfe, 0x00, 0x07, 0xfe, 0x00, 0x03, 0xfc, 0x00, 0x00, 0xf8, 0x00, 0x00, 0xf0, 0x00, 
	  0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };

  const int epd_bitmap_allArray_LEN = 1;
  const unsigned char* epd_bitmap_allArray[1] = {coeur};

// 

// partie capteur bpm + led + buzzer 

  #define nombre_valeurs 4
  #define seuil 4

  int ledV = 2;
  int ledJ = 3;
  int ledR = 4;

  int buzzer = 6; 
  int note_buz; 
  int tps;
  int der = 0;  
  int vol = 1; 

  int iDuino = A2;

  float valeurs[nombre_valeurs];
  float liste_valeurs_bpm[2];
  float somme;
  float derniere_valeur;
  float valeur_precedente;
  float graphe;
  float debut, premier, second, troisieme;
  float bpm;
  long int actuel; 
  long int i; 
  long int dernier_bpm;
  int bpm_min = 50, bpm_max = 180; 
  int nombre_pics, n;  
  bool pic;

//

// partie graphique

  int pot2 = A0; 
  int pot2_val; 
  int val_menu2; 

  int boutton2 = 7; 
  int state2 = 0; 

  int enr; 

  int ech; 
  int tai; 
  int hauteur; 
  int hi = 0; 

  int der2; 
  int tps2; 

  int val_graphe[14];

  int val_grapheEn1[14]; 
  int val_grapheEn2[14]; 
  int val_grapheEn3[14]; 
  int val_grapheEn4[14]; 
  int val_grapheEn5[14]; 

  int eng = 1; 
//

// partie clock
  virtuabotixRTC myRTC(10, 9, 8);
//

// partie enregistrement
  int boutton3 = 5; 
  int state3; 

  int hen1;  
  int mien1; 
  int jen1;
  int moien1; 
  int anen1; 

  int hen2;  
  int mien2; 
  int jen2;
  int moien2; 
  int anen2; 

  int hen3;  
  int mien3; 
  int jen3;
  int moien3; 
  int anen3; 

  int hen4;  
  int mien4; 
  int jen4;
  int moien4; 
  int anen4; 

  int numm; 
//

void setup() {

 // partie led + buzzer

  pinMode(ledV, OUTPUT);
  pinMode(ledJ, OUTPUT);
  pinMode(ledR, OUTPUT);

  digitalWrite(ledV, LOW);
  digitalWrite(ledJ, LOW);
  digitalWrite(ledR, LOW);

  Serial.begin(115200);

 //

 // partie bpm

  for (int i = 0; i < nombre_valeurs; i++)
      valeurs[i] = 0;
    somme = 0;
    i = 0;

 //

 // partie oled + menu + intro 

  afh = 24;
  lg = 2;  

  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3D)) {
    Serial.println(F("SSD1306 allocation failed"));
  for(;;);  } 

  if(!display2.begin(SSD1306_SWITCHCAPVCC,0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
  for(;;);  } 

    Serial.begin(9600);

  display.setTextColor(WHITE);
  display.clearDisplay(); 

  display2.setTextColor(WHITE);
  display2.clearDisplay(); 
  
  intro();

 //

 // partie graphe 

   for(int i = 0; i < 13; i++){
    val_graphe[i] = 58; 
  }

 //

 // partie clock
  //myRTC.setDS1302Time(0, 45, 21, 1, 27, 11, 2022); 
 //

}

void loop() {

 // partie bpm 

  while(1){ 

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

          bpm = 60000. / (0.4 * premier + 0.3 * second + 0.3 * troisieme) + 40;

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
    
  if(bpm <= bpm_min){
    bpm = bpm_min; 
  }
  if(bpm >= bpm_max){
    bpm = bpm_max; 
  }

 // 

 // partie led + buzzer 

  tps = millis();

  if ( (tps - der) >= (60000/bpm) && analogRead(iDuino) > 800){
    tone(buzzer, note_buz);
    delay(10);
    noTone(buzzer);
    der = millis();  
  }

  if (analogRead(iDuino) < 800){
    digitalWrite(ledV, LOW);
    digitalWrite(ledJ, LOW);
    digitalWrite(ledR, LOW);
    noTone(buzzer);
  }
  else if(bpm < 60){
    digitalWrite(ledV, HIGH);
    digitalWrite(ledJ, LOW);
    digitalWrite(ledR, LOW);
    note_buz = 359;
  }
  else if(bpm > 100){
    digitalWrite(ledV, LOW);
    digitalWrite(ledJ, LOW);
    digitalWrite(ledR, HIGH);
    note_buz = 1782;
  }
  else {
    digitalWrite(ledV, LOW);
    digitalWrite(ledJ, HIGH);
    digitalWrite(ledR, LOW);
    note_buz = 1489;
  }

    Serial.print(bpm);
 //

 // partie clock
  myRTC.updateTime();
 //

 // partie oled + menu 
  pot1_val = analogRead(pot1); 
  val_menu = map(pot1_val, 0, 1023, 0, 4);
  state = digitalRead(boutton); 

    display.clearDisplay(); 

    display.setTextSize(2); 
    display.setCursor(30,32);

    if(analogRead(iDuino) > 800){
    display.print(bpm, 0);
    }
    if(analogRead(iDuino) <= 800){
    display.print("--");
      digitalWrite(ledV, LOW);
      digitalWrite(ledJ, LOW);
      digitalWrite(ledR, LOW);
      bpm = 0; 
    }

    display.setTextSize(1); 
    display.setCursor(68,36);
    display.print("bpm");

    display.drawBitmap(85 , 25 , coeur, largeurDeLimage,  hauteurDeLimage, WHITE);

    display.setTextSize(1); 
    display.setCursor(0,1);
    display.print(myRTC.hours);
    display.print(":");
    display.print(myRTC.minutes);

    display.setTextSize(1); 
    display.setCursor(105,-2);
    display.print("...");

    display.drawRect(-1, -1, 35, 12, WHITE);

    display.drawRect(100, -1, 129, 12, WHITE);

    if(lg == 2 && vol == 1){
      display.setCursor(3, 54);
      display.print("son");
    }
    if(lg == 1 && vol == 1){
      display.setCursor(3, 54);
      display.print("sound");
    }
    if(lg == 2 && vol == 0){
      display.setCursor(3, 54);
      display.drawLine(1, 58, 22, 58, WHITE);
      display.print("son");
    }
    if(lg == 1 && vol == 0){
      display.setCursor(3, 54);
      display.drawLine(1, 58, 33, 58, WHITE);
      display.print("sound");
    }


    if(val_menu > 2){
    display.drawRect(98, -1, 129, 14, WHITE);      
    display.drawRect(96, -1, 129, 16, WHITE);      
    }

    if(val_menu <= 2 && val_menu > 1){
    display.drawRect(-1, -1, 37, 14, WHITE);
    display.drawRect(-1, -1, 39, 16, WHITE);     
    }

    if(val_menu <= 1 && lg == 1){
    display.drawRect(-1, 49, 39, 65, WHITE);      
    display.drawRect(-1, 51, 37, 65, WHITE);      
    }

    if(val_menu <= 1 && lg == 2){
    display.drawRect(-1, 53, 26, 65, WHITE);      
    display.drawRect(-1, 51, 28, 65, WHITE);      
    }

    if(val_menu > 2 && state == 0){
    m1();   
    }

    if(val_menu <= 2 && val_menu > 1 && state == 0){
    mh();   
    }

    if(val_menu <= 1 && state == 0 ){
      vol = !vol; 
    }

    if(vol == 1){
      buzzer = 6; 
    }
    if(vol == 0){
      buzzer = 31; 
    }

  display.display(); 
 // 

 // partie graphe 
  state3 = digitalRead(boutton3); 

  Serial.print(eng); 
  Serial.print("  "); 
  Serial.println(hen1); 

  if(state3 == 0){

    if(eng == 1){
      hen1 = myRTC.hours; 
      mien1 = myRTC.minutes; 
      jen1 = myRTC.dayofmonth; 
      moien1 = myRTC.month; 
      anen1 = myRTC.year; 
      EEPROM.put(300000, hen1);
      EEPROM.put(300100, mien1);
      EEPROM.put(300200, jen1);
      EEPROM.put(300300, moien1);
      EEPROM.put(300400, anen1);
    }
    if(eng == 2){
      hen2 = myRTC.hours; 
      mien2 = myRTC.minutes; 
      jen2 = myRTC.dayofmonth; 
      moien2 = myRTC.month; 
      anen2 = myRTC.year; 
      EEPROM.put(300500, hen2);
      EEPROM.put(300600, mien2);
      EEPROM.put(300700, jen2);
      EEPROM.put(300800, moien2);
      EEPROM.put(300900, anen2);
    }
    if(eng == 3){
      hen3 = myRTC.hours; 
      mien3 = myRTC.minutes; 
      jen3 = myRTC.dayofmonth; 
      moien3 = myRTC.month; 
      anen3 = myRTC.year; 
      EEPROM.put(301000, hen3);
      EEPROM.put(301100, mien3);
      EEPROM.put(301200, jen3);
      EEPROM.put(301300, moien3);
      EEPROM.put(301400, anen3);
    }
    if(eng == 4){
      hen4 = myRTC.hours; 
      mien4 = myRTC.minutes; 
      jen4 = myRTC.dayofmonth; 
      moien4 = myRTC.month; 
      anen4 = myRTC.year; 
      EEPROM.put(301500, hen3);
      EEPROM.put(301600, mien3);
      EEPROM.put(301700, jen3);
      EEPROM.put(301800, moien3);
      EEPROM.put(301900, anen3);
    }

    record();  
  }

  grph(); 

    }
 //

}

// fonction introduction 
void intro(){

  for(int i=0; i<30; i+=5) {
    display.drawTriangle(
      display.width()/2  , display.height()/2-i,
      display.width()/2-i, display.height()/2+i,
      display.width()/2+i, display.height()/2+i, SSD1306_WHITE);
    display.display();

    display2.drawTriangle(
      display2.width()/2  , display.height()/2-i,
      display2.width()/2-i, display.height()/2+i,
      display2.width()/2+i, display.height()/2+i, SSD1306_WHITE);
    display2.display();

    delay(50);
  }

    delay(1500);

    display.clearDisplay();
    display2.clearDisplay();

    delay(10);

    display.setFont(&FreeSerifItalic12pt7b);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(10, 40);
    display.println("Cardio ECE");
    display.display();

    display2.setFont(&FreeSerifItalic12pt7b);
    display2.setTextColor(WHITE);
    display2.setTextSize(1);
    display2.setCursor(10, 40);
    display2.println("Cardio ECE");
    display2.display();

    delay(1500);

    display.setFont();
    display.display();

    display2.setFont();
    display2.display();
}

// fonction premier menu selection droit 
void m1(){

  delay(500);
 
  while(1){

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,2);

  if(lg == 1){
  display.println("Language");
  }
  if(lg == 2){
  display.println("Langue");
  }

  display.setCursor(20,15);

  if(lg == 1){
  display.println("Brightness");
  }
  if(lg == 2){
  display.println("Luminosite");
  }

  display.setCursor(20,28);
  display.println("Date");
  display.setCursor(20,41);
  display.println("BPM");
  display.setCursor(20,54);
  display.println("Credits");

  pot1_val = analogRead(pot1); 
  val_menu = map(pot1_val, 0, 1023, 0, 5);
  state = digitalRead(boutton); 

  display.setCursor(0,ym1);
  display.println(">");
  display.display();

  if(val_menu == 0){
    ym1=2;
  }

  if(val_menu == 1){
    ym1=15;
  }

  if(val_menu == 2){
    ym1=28;
  }

  if(val_menu == 3){
    ym1=41;
  }

  if(val_menu == 4){
    ym1=54;
  }

  if(val_menu == 0 && state == 0){
    mLa();
  }
    if(val_menu == 1 && state == 0){
    mLu();
  }
    if(val_menu == 2 && state == 0){
    mD();
  }
    if(val_menu >= 3 && val_menu < 4 && state == 0){
    mB();
  }
  if(val_menu >= 4 && state == 0){
    mc();
  }
  }
}

// fonction selection langue 
void mLa(){

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,20);
  display.println("English");
  display.setCursor(16,33);
  display.println("Francais");

  delay(500);
   

  while(1){

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,20);
  display.println("English");
  display.setCursor(16,33);
  display.println("Francais");

  pot1_val = analogRead(pot1); 
  val_menu = map(pot1_val, 0, 1023, 0, 4);
  state = digitalRead(boutton); 

  display.setCursor(0,ym1);
  display.println(">");
  display.display();

  if(val_menu <= 1){
    ym1=20;
  }

  if(val_menu > 1){
    ym1=33;
  }

  if(val_menu <= 1 && state == 0){
    delay(500);
    lg = 1;   
    loop(); 
  }

  if(val_menu > 1 && state == 0){
    delay(500);
    lg = 2; 
    loop();   
  }

  }

}

// fonction selection luminosité 
void mLu(){

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,20);

  if(lg == 1){
  display.println("Light mode");
  }
  if(lg == 2){
  display.println("Mode clair");
  }

  display.setCursor(16,33);

  if(lg == 1){
  display.println("Dark mode");
  }
  if(lg == 2){
  display.println("Mode sombre");
  }

  delay(500);
   

  while(1){

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,20);

  if(lg == 1){
  display.println("Light mode");
  }
  if(lg == 2){
  display.println("Mode clair");
  }

  display.setCursor(16,33);

  if(lg == 1){
  display.println("Dark mode");
  }
  if(lg == 2){
  display.println("Mode sombre");
  }

  pot1_val = analogRead(pot1); 
  val_menu = map(pot1_val, 0, 1023, 0, 4);
  state = digitalRead(boutton); 

  display.setCursor(0,ym1);
  display.println(">");
  display.display();

  if(val_menu <= 1){
    ym1=20;
  }

  if(val_menu > 1){
    ym1=33;
  }

  if(val_menu <= 1 && state == 0){
    delay(500);
     
    display.invertDisplay(true);
    display2.invertDisplay(true);
    loop(); 
  }

  if(val_menu > 1 && state == 0){
    delay(500);
     
    display.invertDisplay(false);
    display2.invertDisplay(false);
    loop();   
  }

  }

}

// fonction selection date 
void mD(){

  delay(500);
   
  pos = 0;

  while(1){

  myRTC.updateTime();
  display.clearDisplay();

  pot1_val = analogRead(pot1); 
  val_menu = map(pot1_val, 0, 1023, 0, 4);
  state = digitalRead(boutton);  

  display.setTextSize(2); 
  display.setCursor(5,28);
  display.print(jj);
  display.print("/");  
  display.print(mm);
  display.print("/");
  display.print(aa); 

  display.setTextSize(1); 
  display.setCursor(13,15); 

  if(lg == 1){
  display.println("D");
  }
  if(lg == 2){
  display.println("J");
  }
  display.setCursor(50,15); 

  display.println("M");

  display.setCursor(98,15); 

  if(lg == 1){
  display.println("Y");
  }
  if(lg == 2){
  display.println("A");
  }

  if(state == 0){
    pos++; 
    delay(500);
     
  }

  if(pos == 0){
    display.drawLine(5, 45, 26, 45, WHITE); 
    jj = map(pot1_val, 0, 1023, 1, 32);
  }

  if(pos == 1){
    display.drawLine(41, 45, 62, 45, WHITE); 
    mm = map(pot1_val, 0, 1023, 1, 13);
  }

  if(pos == 2){
    display.drawLine(77, 45, 122, 45, WHITE);
    aa = map(pot1_val, 0, 1023, 2000, 2051); 
  }

  if(pos == 3){
    myRTC.setDS1302Time(myRTC.seconds, myRTC.minutes, myRTC.hours, myRTC.dayofweek, jj, mm, aa);
    delay(500);
     
    loop();
  }

  display.display(); 

  }
}

// fonction selection bpm_min / bpm_max  
void mB(){

  delay(500);
   

  while(1){

  display.clearDisplay();

  pot1_val = analogRead(pot1); 
  val_menu = map(pot1_val, 0, 1023, 0, 4);
  state = digitalRead(boutton);  

  display.setTextSize(1); 
  display.setCursor(20,15); 

  if(lg == 1){
  display.println("Max BPM Threshold");
  }
  if(lg == 2){
  display.println("Seuil BPM Max");
  }

  display.setTextSize(2); 
  display.setCursor(45,30); 
  bpm_max = map(pot1_val, 0, 1023, 20, 220);
  display.println(bpm_max); 

  if(state == 0) {

    delay(500);
     

    while(1){

    display.clearDisplay();

    pot1_val = analogRead(pot1); 
    val_menu = map(pot1_val, 0, 1023, 0, 4);
    state = digitalRead(boutton);  

    display.setTextSize(1); 
    display.setCursor(25,15); 

    if(lg == 1){
    display.setCursor(20,15);
    display.println("Min BPM Threshold");
    }
    if(lg == 2){
    display.println("Seuil BPM Min");
    }

    display.setTextSize(2); 
    display.setCursor(45,30); 
    bpm_min = map(pot1_val, 0, 1023, 20, 220);
    display.println(bpm_min); 

    if(state == 0){
      delay(500);
       
      loop(); 

    }

    display.display();

    }

  }

  display.display();

  }
  
}

// fonction selection heure gauche  
void mh(){

  delay(500);
   

  while(1){
  myRTC.updateTime();
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,28);

  if(lg == 1){
  display.println("Time setting");
  }
  if(lg == 2){
  display.println("Reglage de l'heure");
  }

  pot1_val = analogRead(pot1); 
  val_menu = map(pot1_val, 0, 1023, 0, 4);
  state = digitalRead(boutton); 

  if(state == 0){

  delay(500);
   

  pos = 0;

  while(1){
  
  display.clearDisplay();

  pot1_val = analogRead(pot1); 
  val_menu = map(pot1_val, 0, 1023, 0, 4);
  state = digitalRead(boutton);  

  display.setTextSize(2); 
  display.setCursor(30,28);
  display.print(hh);
  display.setCursor(60,28);
  display.print("h");  
  display.setCursor(80,28);
  display.print(mnmn);


  if(state == 0){
    pos++; 
    delay(500);
     
  }

  if(pos == 0){
    display.drawLine(30, 45, 51, 45, WHITE); 
    hh = map(pot1_val, 0, 1023, 0, 24);
  }

  if(pos == 1){
    display.drawLine(80, 45, 101, 45, WHITE); 
    mnmn = map(pot1_val, 0, 1023, 0, 60);
  }

  if(pos == 2){
    myRTC.setDS1302Time(myRTC.seconds, mnmn , hh , myRTC.dayofweek, myRTC.dayofmonth, myRTC.month, myRTC.year);
    delay(500);
    loop();
  }

  display.display(); 

  }

  }

  }

}

// fonction affichage crédits 
void mc(){

  delay(500);
   

  while(1){

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,10);
  display.println("Come Cervantes");
  display.setCursor(10,23);
  display.println("Jean-Felix Bertrand");
  display.setCursor(10,36);
  display.println("Florian Bonelli");
  display.setCursor(10,49);
  display.println("Marco Ferrante");

  display.display();

  state = digitalRead(boutton); 

  if(state == 0){
    delay(500);
    loop();
    break; 
  }

  }
}

//fonction affichage écran 2 graphique
void grph(){

   display2.clearDisplay();

  pot2_val = analogRead(pot2);
  tai = map(pot2_val, 0, 1023, 0, 8); 
  state2 = digitalRead(boutton2); 
  state = digitalRead(boutton); 

  if(tai == 0){
    ech = 60; 
  }
  else if(tai == 1){
    ech = 30;   
  }
  else if(tai == 2){
    ech = 20;  
  }
  else if(tai == 3){
    ech = 10;   
  }
  else if(tai == 4){
    ech = 5;   
  }
  else if(tai == 5){
     ech = 1;  
  }
  else if(tai > 5){
    display2.drawRect(100, -1, 129, 12, WHITE);    
  }

  if(tai > 5 && state2 == 0){
    me(); 
  }

 display2.drawLine(1, 59, 126, 59, WHITE); // X 
 display2.drawLine(4, 1, 4, 62, WHITE); // Y 

 display2.drawLine(123, 56, 126, 59, WHITE); // fleche X 
  display2.drawLine(123, 62, 126, 59, WHITE); 

 display2.drawLine(1, 4, 4, 1, WHITE); // fleche Y 
  display2.drawLine(7, 4, 4, 1, WHITE); 

    display2.setTextSize(1); 
    display2.setCursor(105,-2);
    display2.print("...");

  display2.setTextSize(1);
  display2.setTextColor(WHITE);
  display2.setCursor(10,-1);
  display2.println("bpm");

  display2.setCursor(40,0);
  display2.print(ech);
  display2.println("s/10px");

  display2.setCursor(10,40);
  display2.println("- - - - - - - - - -"); // axe 60
  display2.setCursor(10,24);
  display2.println("- - - - - - - - - -"); // axe 100

      display2.drawLine(14, 57, 14, 61, WHITE); 
      display2.drawLine(24, 57, 24, 61, WHITE); 
      display2.drawLine(34, 57, 34, 61, WHITE); 
      display2.drawLine(44, 57, 44, 61, WHITE); 
      display2.drawLine(54, 57, 54, 61, WHITE); 
      display2.drawLine(64, 57, 64, 61, WHITE);       
      display2.drawLine(74, 57, 74, 61, WHITE); 
      display2.drawLine(84, 57, 84, 61, WHITE); 
      display2.drawLine(94, 57, 94, 61, WHITE); 
      display2.drawLine(104, 57, 104, 61, WHITE); 
      display2.drawLine(114, 57, 114, 61, WHITE); 

    hauteur = 58 - map(bpm, 0, 180, 0, 58); 
    tps2 = millis(); 

    if(tps - der2 >= (ech * 1000) && hi < 12 ){
      val_graphe[hi] = hauteur; 
      hi++; 
      der2 = millis(); 
      
    }

    if(tps - der2 >= (ech * 1000)){
      for(int i = 0; i < 12; i++){
        val_graphe[i] = val_graphe[i+1]; 
      }
      val_graphe[12] = hauteur; 
      der2 = millis(); 
      
    }

      display2.drawLine(4, val_graphe[0], 14, val_graphe[1], WHITE); 
      display2.drawLine(14, val_graphe[1], 24, val_graphe[2], WHITE); 
      display2.drawLine(24, val_graphe[2], 34, val_graphe[3], WHITE); 
      display2.drawLine(34, val_graphe[3], 44, val_graphe[4], WHITE); 
      display2.drawLine(44, val_graphe[4], 54, val_graphe[5], WHITE); 
      display2.drawLine(54, val_graphe[5], 64, val_graphe[6], WHITE); 
      display2.drawLine(64, val_graphe[6], 74, val_graphe[7], WHITE); 
      display2.drawLine(74, val_graphe[7], 84, val_graphe[8], WHITE); 
      display2.drawLine(84, val_graphe[8], 94, val_graphe[9], WHITE); 
      display2.drawLine(94, val_graphe[9], 104, val_graphe[10], WHITE); 
      display2.drawLine(104, val_graphe[10], 114, val_graphe[11], WHITE); 
      display2.drawLine(114, val_graphe[11], 124, val_graphe[12], WHITE); 


   display2.display();
}

// fonction menu enregistrements 
void me(){

 delay(500);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,30);

  if(lg == 2){
  display.println("Enregistrement :");
  }
  if(lg == 1){
  display.println("Recording :");
  }

  display.display(); 

  while(1){

  display2.clearDisplay();
  display2.setTextSize(1);
  display2.setTextColor(WHITE);
  display2.setCursor(20,2);

  if(lg == 2){
  display2.println("Enregistrement 1");
  }
  if(lg == 1){
  display2.println("Recording 1");
  }

  display2.setCursor(20,15);

  if(lg == 2){
  display2.println("Enregistrement 2");
  }
  if(lg == 1){
  display2.println("Recording 2");
  }

  display2.setCursor(20,28);

  if(lg == 2){
  display2.println("Enregistrement 3");
  }
  if(lg == 1){
  display2.println("Recording 3");
  }

  display2.setCursor(20,41);

  if(lg == 2){
  display2.println("Enregistrement 4");
  }
  if(lg == 1){
  display2.println("Recording 4");
  }

  pot2_val = analogRead(pot2); 
  val_menu2 = map(pot2_val, 0, 1023, 0, 5);
  state2 = digitalRead(boutton2); 

  display2.setCursor(0,ym1);
  display2.println(">");
  display2.display();

  if(val_menu2 == 0){
    ym1=2;
  }

  if(val_menu2 == 1){
    ym1=15;
  }

  if(val_menu2 == 2){
    ym1=28;
  }

  if(val_menu2 == 3){
    ym1=41;
  }

  if(val_menu2 == 0 && state2 == 0){
    mEn1();
  }
    if(val_menu2 == 1 && state2 == 0){
    mEn2();
  }
    if(val_menu2 == 2 && state2 == 0){
    mEn3();
  }
    if(val_menu2 >= 3 && val_menu2 < 4 && state2 == 0){
    mEn4();
  }
  }
}

// fonction affichage des enregistrements 
void mEn1(){

      hen1 = EEPROM.get(300000, hen1);
      mien1 = EEPROM.put(300100, mien1);
      jen1 = EEPROM.put(300200, jen1);
      moien1 = EEPROM.put(300300, moien1);
      anen1 = EEPROM.put(300400, anen1);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,30);

  for(int i = 0; i < 14; i++){
    val_grapheEn1[i] = EEPROM.get(20000+10*i, val_grapheEn1[i]);
  }

  if(lg == 2){
  display.println("Enregistrement :");
  }
  if(lg == 1){
  display.println("Recording :");
  }
  display.setCursor(20,40);
  display.print(hen1);
  display.print("h");
  display.print(mien1);
  display.print("  ");
  display.print(jen1);
  display.print("/");
  display.print(moien1);
  display.print("/");
  display.print(anen1);

  display.display(); 

  while (1) {
 state3 = digitalRead(boutton3); 

 if(state3 == 0){
  for(int i = 0; i  < 14; i++){
    val_grapheEn1[i] = 0; 
  }
   hen1 = 0;  
   mien1 = 0; 
   jen1 = 0;
   moien1 = 0; 
   anen1 = 0;
  sup();
  delay(500); 
  loop(); 
 }

 display2.clearDisplay();

 display2.drawLine(1, 59, 126, 59, WHITE); // X 
 display2.drawLine(4, 1, 4, 62, WHITE); // Y 

 display2.drawLine(123, 56, 126, 59, WHITE); // fleche X 
  display2.drawLine(123, 62, 126, 59, WHITE); 

  display2.drawLine(1, 4, 4, 1, WHITE); // fleche Y 
  display2.drawLine(7, 4, 4, 1, WHITE); 

  display2.setTextSize(1);
  display2.setTextColor(WHITE);
  display2.setCursor(10,-1);
  display2.println("bpm");

  display2.setCursor(10,40);
  display2.println("- - - - - - - - - -"); // axe 60
  display2.setCursor(10,24);
  display2.println("- - - - - - - - - -"); // axe 100

      display2.drawLine(14, 57, 14, 61, WHITE); 
      display2.drawLine(24, 57, 24, 61, WHITE); 
      display2.drawLine(34, 57, 34, 61, WHITE); 
      display2.drawLine(44, 57, 44, 61, WHITE); 
      display2.drawLine(54, 57, 54, 61, WHITE); 
      display2.drawLine(64, 57, 64, 61, WHITE);       
      display2.drawLine(74, 57, 74, 61, WHITE); 
      display2.drawLine(84, 57, 84, 61, WHITE); 
      display2.drawLine(94, 57, 94, 61, WHITE); 
      display2.drawLine(104, 57, 104, 61, WHITE); 
      display2.drawLine(114, 57, 114, 61, WHITE); 

      display2.drawLine(4, val_grapheEn1[0], 14, val_grapheEn1[1], WHITE); 
      display2.drawLine(14, val_grapheEn1[1], 24, val_grapheEn1[2], WHITE); 
      display2.drawLine(24, val_grapheEn1[2], 34, val_grapheEn1[3], WHITE); 
      display2.drawLine(34, val_grapheEn1[3], 44, val_grapheEn1[4], WHITE); 
      display2.drawLine(44, val_grapheEn1[4], 54, val_grapheEn1[5], WHITE); 
      display2.drawLine(54, val_grapheEn1[5], 64, val_grapheEn1[6], WHITE); 
      display2.drawLine(64, val_grapheEn1[6], 74, val_grapheEn1[7], WHITE); 
      display2.drawLine(74, val_grapheEn1[7], 84, val_grapheEn1[8], WHITE); 
      display2.drawLine(84, val_grapheEn1[8], 94, val_grapheEn1[9], WHITE); 
      display2.drawLine(94, val_grapheEn1[9], 104, val_grapheEn1[10], WHITE); 
      display2.drawLine(104, val_grapheEn1[10], 114, val_grapheEn1[11], WHITE); 
      display2.drawLine(114, val_grapheEn1[11], 124, val_grapheEn1[12], WHITE); 


   display2.display();

  delay(200); 

    state2 = digitalRead(boutton2); 
    if(state2 ==0){
      loop(); 
    }
 } 
}

void mEn2(){

      hen2 = EEPROM.get(300500, hen2);
      mien2 = EEPROM.put(300600, mien2);
      jen2 = EEPROM.put(300700, jen2);
      moien2 = EEPROM.put(300800, moien2);
      anen2 = EEPROM.put(300900, anen2);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,30);

  if(lg == 2){
  display.println("Enregistrement :");
  }
  if(lg == 1){
  display.println("Recording :");
  }
  display.setCursor(20,40);
  display.print(hen2);
  display.print("h");
  display.print(mien2);
  display.print("  ");
  display.print(jen2);
  display.print("/");
  display.print(moien2);
  display.print("/");
  display.print(anen2);

  display.display();

  for(int i = 0; i < 14; i++){
    val_grapheEn2[i] = EEPROM.get(16000+10*i, val_grapheEn2[i]);
  }

  while (1) {

  state3 = digitalRead(boutton3); 

  if(state3 == 0){
  for(int i = 0; i  < 14; i++){
    val_grapheEn2[i] = 0; 
  }
  hen2 = 0;  
   mien2 = 0; 
   jen2 = 0;
   moien2 = 0; 
   anen2 = 0;
   sup();
        delay(500); 
  loop(); 
 }

    delay(200); 

    state2 = digitalRead(boutton2); 
    if(state2 ==0){
      loop(); 
    }

 display2.clearDisplay();

 display2.drawLine(1, 59, 126, 59, WHITE); // X 
 display2.drawLine(4, 1, 4, 62, WHITE); // Y 

 display2.drawLine(123, 56, 126, 59, WHITE); // fleche X 
  display2.drawLine(123, 62, 126, 59, WHITE); 

 display2.drawLine(1, 4, 4, 1, WHITE); // fleche Y 
  display2.drawLine(7, 4, 4, 1, WHITE); 

  display2.setTextSize(1);
  display2.setTextColor(WHITE);
  display2.setCursor(10,-1);
  display2.println("bpm");

  display2.setCursor(10,40);
  display2.println("- - - - - - - - - -"); // axe 60
  display2.setCursor(10,24);
  display2.println("- - - - - - - - - -"); // axe 100

      display2.drawLine(14, 57, 14, 61, WHITE); 
      display2.drawLine(24, 57, 24, 61, WHITE); 
      display2.drawLine(34, 57, 34, 61, WHITE); 
      display2.drawLine(44, 57, 44, 61, WHITE); 
      display2.drawLine(54, 57, 54, 61, WHITE); 
      display2.drawLine(64, 57, 64, 61, WHITE);       
      display2.drawLine(74, 57, 74, 61, WHITE); 
      display2.drawLine(84, 57, 84, 61, WHITE); 
      display2.drawLine(94, 57, 94, 61, WHITE); 
      display2.drawLine(104, 57, 104, 61, WHITE); 
      display2.drawLine(114, 57, 114, 61, WHITE); 

      display2.drawLine(4, val_grapheEn2[0], 14, val_grapheEn2[1], WHITE); 
      display2.drawLine(14, val_grapheEn2[1], 24, val_grapheEn2[2], WHITE); 
      display2.drawLine(24, val_grapheEn2[2], 34, val_grapheEn2[3], WHITE); 
      display2.drawLine(34, val_grapheEn2[3], 44, val_grapheEn2[4], WHITE); 
      display2.drawLine(44, val_grapheEn2[4], 54, val_grapheEn2[5], WHITE); 
      display2.drawLine(54, val_grapheEn2[5], 64, val_grapheEn2[6], WHITE); 
      display2.drawLine(64, val_grapheEn2[6], 74, val_grapheEn2[7], WHITE); 
      display2.drawLine(74, val_grapheEn2[7], 84, val_grapheEn2[8], WHITE); 
      display2.drawLine(84, val_grapheEn2[8], 94, val_grapheEn2[9], WHITE); 
      display2.drawLine(94, val_grapheEn2[9], 104, val_grapheEn2[10], WHITE); 
      display2.drawLine(104, val_grapheEn2[10], 114, val_grapheEn2[11], WHITE); 
      display2.drawLine(114, val_grapheEn2[11], 124, val_grapheEn2[12], WHITE); 


   display2.display();

   delay(2000); 
 }
}

void mEn3(){

      hen3 = EEPROM.get(301100, hen3);
      mien3 = EEPROM.put(301200, mien3);
      jen3 = EEPROM.put(301300, jen3);
      moien3 = EEPROM.put(301400, moien3);
      anen3 = EEPROM.put(301500, anen3);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,30);

  if(lg == 2){
  display.println("Enregistrement :");
  }
  if(lg == 1){
  display.println("Recording :");
  }
  display.setCursor(20,40);
  display.print(hen3);
  display.print("h");
  display.print(mien3);
  display.print("  ");
  display.print(jen3);
  display.print("/");
  display.print(moien3);
  display.print("/");
  display.print(anen3);

  display.display();

    for(int i = 0; i < 14; i++){
    val_grapheEn3[i] = EEPROM.get(24000+10*i, val_grapheEn3[i]);
  }

  while (1) {
 state3 = digitalRead(boutton3); 

 if(state3 == 0){
  for(int i = 0; i < 13; i++){
    val_grapheEn3[i] = 0; 
  }
  hen3 = 0;  
   mien3 = 0; 
   jen3 = 0;
   moien3 = 0; 
   anen3 = 0;
   sup();
        delay(500); 
  loop(); 
 }
    delay(200); 

    state2 = digitalRead(boutton2); 
    if(state2 ==0){
      loop(); 
    }
    
 display2.clearDisplay();

 display2.drawLine(1, 59, 126, 59, WHITE); // X 
 display2.drawLine(4, 1, 4, 62, WHITE); // Y 

 display2.drawLine(123, 56, 126, 59, WHITE); // fleche X 
  display2.drawLine(123, 62, 126, 59, WHITE); 

 display2.drawLine(1, 4, 4, 1, WHITE); // fleche Y 
  display2.drawLine(7, 4, 4, 1, WHITE); 

  display2.setTextSize(1);
  display2.setTextColor(WHITE);
  display2.setCursor(10,-1);
  display2.println("bpm");

  display2.setCursor(10,40);
  display2.println("- - - - - - - - - -"); // axe 60
  display2.setCursor(10,24);
  display2.println("- - - - - - - - - -"); // axe 100

      display2.drawLine(14, 57, 14, 61, WHITE); 
      display2.drawLine(24, 57, 24, 61, WHITE); 
      display2.drawLine(34, 57, 34, 61, WHITE); 
      display2.drawLine(44, 57, 44, 61, WHITE); 
      display2.drawLine(54, 57, 54, 61, WHITE); 
      display2.drawLine(64, 57, 64, 61, WHITE);       
      display2.drawLine(74, 57, 74, 61, WHITE); 
      display2.drawLine(84, 57, 84, 61, WHITE); 
      display2.drawLine(94, 57, 94, 61, WHITE); 
      display2.drawLine(104, 57, 104, 61, WHITE); 
      display2.drawLine(114, 57, 114, 61, WHITE); 

      display2.drawLine(4, val_grapheEn3[0], 14, val_grapheEn3[1], WHITE); 
      display2.drawLine(14, val_grapheEn3[1], 24, val_grapheEn3[2], WHITE); 
      display2.drawLine(24, val_grapheEn3[2], 34, val_grapheEn3[3], WHITE); 
      display2.drawLine(34, val_grapheEn3[3], 44, val_grapheEn3[4], WHITE); 
      display2.drawLine(44, val_grapheEn3[4], 54, val_grapheEn3[5], WHITE); 
      display2.drawLine(54, val_grapheEn3[5], 64, val_grapheEn3[6], WHITE); 
      display2.drawLine(64, val_grapheEn3[6], 74, val_grapheEn3[7], WHITE); 
      display2.drawLine(74, val_grapheEn3[7], 84, val_grapheEn3[8], WHITE); 
      display2.drawLine(84, val_grapheEn3[8], 94, val_grapheEn3[9], WHITE); 
      display2.drawLine(94, val_grapheEn3[9], 104, val_grapheEn3[10], WHITE); 
      display2.drawLine(104, val_grapheEn3[10], 114, val_grapheEn3[11], WHITE); 
      display2.drawLine(114, val_grapheEn3[11], 124, val_grapheEn3[12], WHITE); 


   display2.display();

   delay(2000); 
 }
}

void mEn4(){

      hen4 = EEPROM.get(301500, hen4);
      mien4 = EEPROM.put(301600, mien4);
      jen4 = EEPROM.put(301700, jen4);
      moien4 = EEPROM.put(301800, moien4);
      anen4 = EEPROM.put(301900, anen4);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,30);

  if(lg == 2){
  display.println("Enregistrement :");
  }
  if(lg == 1){
  display.println("Recording :");
  }
  display.setCursor(20,40);
  display.print(hen4);
  display.print("h");
  display.print(mien4);
  display.print("  ");
  display.print(jen4);
  display.print("/");
  display.print(moien4);
  display.print("/");
  display.print(anen4);

  display.display(); 

  for(int i = 0; i < 14; i++){
    val_grapheEn4[i] = EEPROM.get(29000+10*i, val_grapheEn4[i]);
  }

  while(1){ 
 state3 = digitalRead(boutton3); 

 if(state3 == 0){
  for(int i = 0; i < 13; i++){
    val_grapheEn4[i] = 0; 
  }
   hen4 = 0;  
   mien4 = 0; 
   jen4 = 0;
   moien4 = 0; 
   anen4 = 0;
   sup();
  delay(500); 
  loop(); 
 }
    delay(200); 

    state2 = digitalRead(boutton2); 
    if(state2 ==0){
      loop(); 
    }
    
 display2.clearDisplay();

 display2.drawLine(1, 59, 126, 59, WHITE); // X 
 display2.drawLine(4, 1, 4, 62, WHITE); // Y 

 display2.drawLine(123, 56, 126, 59, WHITE); // fleche X 
  display2.drawLine(123, 62, 126, 59, WHITE); 

 display2.drawLine(1, 4, 4, 1, WHITE); // fleche Y 
  display2.drawLine(7, 4, 4, 1, WHITE); 

  display2.setTextSize(1);
  display2.setTextColor(WHITE);
  display2.setCursor(10,-1);
  display2.println("bpm");

  display2.setCursor(10,40);
  display2.println("- - - - - - - - - -"); // axe 60
  display2.setCursor(10,24);
  display2.println("- - - - - - - - - -"); // axe 100

      display2.drawLine(14, 57, 14, 61, WHITE); 
      display2.drawLine(24, 57, 24, 61, WHITE); 
      display2.drawLine(34, 57, 34, 61, WHITE); 
      display2.drawLine(44, 57, 44, 61, WHITE); 
      display2.drawLine(54, 57, 54, 61, WHITE); 
      display2.drawLine(64, 57, 64, 61, WHITE);       
      display2.drawLine(74, 57, 74, 61, WHITE); 
      display2.drawLine(84, 57, 84, 61, WHITE); 
      display2.drawLine(94, 57, 94, 61, WHITE); 
      display2.drawLine(104, 57, 104, 61, WHITE); 
      display2.drawLine(114, 57, 114, 61, WHITE); 

      display2.drawLine(4, val_grapheEn4[0], 14, val_grapheEn4[1], WHITE); 
      display2.drawLine(14, val_grapheEn4[1], 24, val_grapheEn4[2], WHITE); 
      display2.drawLine(24, val_grapheEn4[2], 34, val_grapheEn4[3], WHITE); 
      display2.drawLine(34, val_grapheEn4[3], 44, val_grapheEn4[4], WHITE); 
      display2.drawLine(44, val_grapheEn4[4], 54, val_grapheEn4[5], WHITE); 
      display2.drawLine(54, val_grapheEn4[5], 64, val_grapheEn4[6], WHITE); 
      display2.drawLine(64, val_grapheEn4[6], 74, val_grapheEn4[7], WHITE); 
      display2.drawLine(74, val_grapheEn4[7], 84, val_grapheEn4[8], WHITE); 
      display2.drawLine(84, val_grapheEn4[8], 94, val_grapheEn4[9], WHITE); 
      display2.drawLine(94, val_grapheEn4[9], 104, val_grapheEn4[10], WHITE); 
      display2.drawLine(104, val_grapheEn4[10], 114, val_grapheEn4[11], WHITE); 
      display2.drawLine(114, val_grapheEn4[11], 124, val_grapheEn4[12], WHITE); 


   display2.display();

   delay(2000); 
 }
}

// fonction enregistrement 
void record(){

  while (1) {

  for(int i = 0; i  < 13; i++){
    if(eng == 1){
          val_grapheEn1[i] = val_graphe[i];
          EEPROM.put(20000+10*i, val_grapheEn1[i]);
    }
    if(eng == 2){
          val_grapheEn2[i] = val_graphe[i];
          EEPROM.put(16000+10*i, val_grapheEn2[i]);
    }
    if(eng == 3){
          val_grapheEn3[i] = val_graphe[i];
          EEPROM.put(24000+10*i, val_grapheEn3[i]);
    }
    if(eng == 4){
          val_grapheEn4[i] = val_graphe[i];
          EEPROM.put(29000+10*i, val_grapheEn4[i]);
    }

  }

  eng++; 

  if(eng == 5){
    eng = 1; 
  }

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,20);

  if(eng == 4 || eng == 2 || eng == 3){
    numm = eng -1; 
  }
  if(eng == 1){
    numm = 4; 
  }

  if(lg == 2){
  display.print("Enregistre...");
  display.print(numm);

  }
  if(lg == 1){
  display.print("Recording ...");
  display.print(numm);

  }
  display.display(); 

 display2.clearDisplay(); 
 display2.drawLine(1, 59, 126, 59, WHITE); // X 
 display2.drawLine(4, 1, 4, 62, WHITE); // Y 

 display2.drawLine(123, 56, 126, 59, WHITE); // fleche X 
  display2.drawLine(123, 62, 126, 59, WHITE); 

 display2.drawLine(1, 4, 4, 1, WHITE); // fleche Y 
  display2.drawLine(7, 4, 4, 1, WHITE); 

  display2.setTextSize(1);
  display2.setTextColor(WHITE);
  display2.setCursor(10,-1);
  display2.println("bpm");

  display2.setCursor(10,40);
  display2.println("- - - - - - - - - -"); // axe 60
  display2.setCursor(10,24);
  display2.println("- - - - - - - - - -"); // axe 100

      display2.drawLine(14, 57, 14, 61, WHITE); 
      display2.drawLine(24, 57, 24, 61, WHITE); 
      display2.drawLine(34, 57, 34, 61, WHITE); 
      display2.drawLine(44, 57, 44, 61, WHITE); 
      display2.drawLine(54, 57, 54, 61, WHITE); 
      display2.drawLine(64, 57, 64, 61, WHITE);       
      display2.drawLine(74, 57, 74, 61, WHITE); 
      display2.drawLine(84, 57, 84, 61, WHITE); 
      display2.drawLine(94, 57, 94, 61, WHITE); 
      display2.drawLine(104, 57, 104, 61, WHITE); 
      display2.drawLine(114, 57, 114, 61, WHITE); 

      display2.drawLine(4, val_graphe[0], 14, val_graphe[1], WHITE); 
      display2.drawLine(14, val_graphe[1], 24, val_graphe[2], WHITE); 
      display2.drawLine(24, val_graphe[2], 34, val_graphe[3], WHITE); 
      display2.drawLine(34, val_graphe[3], 44, val_graphe[4], WHITE); 
      display2.drawLine(44, val_graphe[4], 54, val_graphe[5], WHITE); 
      display2.drawLine(54, val_graphe[5], 64, val_graphe[6], WHITE); 
      display2.drawLine(64, val_graphe[6], 74, val_graphe[7], WHITE); 
      display2.drawLine(74, val_graphe[7], 84, val_graphe[8], WHITE); 
      display2.drawLine(84, val_graphe[8], 94, val_graphe[9], WHITE); 
      display2.drawLine(94, val_graphe[9], 104, val_graphe[10], WHITE); 
      display2.drawLine(104, val_graphe[10], 114, val_graphe[11], WHITE); 
      display2.drawLine(114, val_graphe[11], 124, val_graphe[12], WHITE); 


   display2.display();

   delay(2000); 
   loop(); 

  }
}

// partie écran supprimé 
void sup(){
  display.clearDisplay();
  display2.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,30);

  if(lg == 2){
  display.println("Supprime :");
  }
  if(lg == 1){
  display.println("Delete :");
  }
  delay(1000);
  display.display();
  display2.display();
}

// 1855 lignes !! c'était épuisant...