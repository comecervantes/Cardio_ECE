#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define largeurDeLimage           20          // Largeur de l'image à afficher, en pixels
#define hauteurDeLimage           20          // Hauteur de l'image à afficher, en pixels

const int pot1 = A3; 
int pot1_val; 
int val_menu;
int boutton = 2; 
int ym1; 
int state = 0; 
int lg; 

int afh; 
int jj = 12; 
int mm = 10; 
int aa = 2022; 
int hh; 
int mnmn; 
int de; 

int pos;

int smax; 
int smin; 

const unsigned char coeur [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0e, 0x00, 0x1f, 0x9f, 0x80, 0x1f, 
	0x9f, 0x80, 0x3f, 0xff, 0xc0, 0x3f, 0xff, 0xc0, 0x3f, 0xff, 0xc0, 0x3f, 0xff, 0xc0, 0x1f, 0xff, 
	0x80, 0x07, 0xfe, 0x00, 0x07, 0xfe, 0x00, 0x03, 0xfc, 0x00, 0x00, 0xf8, 0x00, 0x00, 0xf0, 0x00, 
	0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const int epd_bitmap_allArray_LEN = 1;
const unsigned char* epd_bitmap_allArray[1] = {coeur};


void setup() {

  afh = 24; 
  lg = 2; 

  de = 0; 

  hh = 12; 
  mnmn = 0; 

  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
  for(;;);  } 

    Serial.begin(115200);

  display.setTextColor(WHITE);
  display.clearDisplay(); 

}

void loop() {

  while(1){

  de = de + 30; 
  
  pot1_val = analogRead(pot1); 
  val_menu = map(pot1_val, 0, 1023, 0, 4);
  state = digitalRead(boutton); 
  Serial.println(state);

  delay(30); 

    display.clearDisplay(); 

    display.setTextSize(2); 
    display.setCursor(30,28);
    display.print("100");

    display.setTextSize(1); 
    display.setCursor(68,36);
    display.print("bpm");

    display.drawBitmap(83 , 25 , coeur, largeurDeLimage,  hauteurDeLimage, WHITE);

    display.setTextSize(1); 
    display.setCursor(0,1);
    display.print("12:00");

    display.setTextSize(1); 
    display.setCursor(105,-2);
    display.print("...");

    display.drawRect(-1, -1, 35, 12, WHITE);

    display.drawRect(100, -1, 129, 12, WHITE);

    if(val_menu > 1){
    display.drawRect(98, -1, 129, 14, WHITE);      
    display.drawRect(96, -1, 129, 16, WHITE);      
    }

    if(val_menu <= 1){
    display.drawRect(-1, -1, 37, 14, WHITE);
    display.drawRect(-1, -1, 39, 16, WHITE);     
    }

    if(val_menu > 1 && state == 0){
    m1();   
    }

    if(val_menu <= 1 && state == 0){
    mh();   
    }

  display.display(); 

  }  

}

void m1(){

  delay(500);
  de = de + 500; 

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

  pot1_val = analogRead(pot1); 
  val_menu = map(pot1_val, 0, 1023, 0, 4);
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

  if(val_menu == 0 && state == 0){
    mLa();
  }
    if(val_menu == 1 && state == 0){
    mLu();
  }
    if(val_menu == 2 && state == 0){
    mD();
  }
    if(val_menu >= 3 && state == 0){
    mB();
  }
  }
}

void mLa(){

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,20);
  display.println("English");
  display.setCursor(20,33);
  display.println("Francais");

  delay(500);
  de = de + 500; 

  while(1){

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,20);
  display.println("English");
  display.setCursor(20,33);
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
    de = de + 500; 
    lg = 1;   
    loop(); 
  }

  if(val_menu > 1 && state == 0){
    delay(500);
    de = de + 500; 
    lg = 2; 
    loop();   
  }

  }

}

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

  display.setCursor(20,33);

  if(lg == 1){
  display.println("Dark mode");
  }
  if(lg == 2){
  display.println("Mode sombre");
  }

  delay(500);
  de = de + 500; 

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

  display.setCursor(20,33);

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
    de = de + 500; 
    display.invertDisplay(true);
    loop(); 
  }

  if(val_menu > 1 && state == 0){
    delay(500);
    de = de + 500; 
    display.invertDisplay(false);
    loop();   
  }

  }

}

void mD(){

  delay(500);
  de = de + 500; 

  pos = 0;

  while(1){
  
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
    de = de + 500; 
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
    aa = map(pot1_val, 0, 1023, 2000, 2101); 
  }

  if(pos == 3){
    delay(500);
    de = de + 500; 
    loop();
  }

  display.display(); 

  }
}

void mB(){

  delay(500);
  de = de + 500; 

  while(1){

  display.clearDisplay();

  pot1_val = analogRead(pot1); 
  val_menu = map(pot1_val, 0, 1023, 0, 4);
  state = digitalRead(boutton);  

  display.setTextSize(1); 
  display.setCursor(25,15); 

  if(lg == 1){
  display.println("Max BPM Threshold");
  }
  if(lg == 2){
  display.println("Seuil BPM Max");
  }

  display.setTextSize(2); 
  display.setCursor(45,30); 
  smax = map(pot1_val, 0, 1023, 20, 220);
  display.println(smax); 

  if(state == 0) {

    delay(500);
    de = de + 500; 

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
    smin = map(pot1_val, 0, 1023, 20, 220);
    display.println(smin); 

    if(state == 0){
      delay(500);
      de = de + 500; 
      loop(); 

    }

    display.display();

    }

  }

  display.display();

  }
  
}

void mh(){

  delay(500);
  de = de + 500; 

  while(1){

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,15);
  display.println("12h");
  display.setCursor(20,28);
  display.println("24H");
  display.setCursor(20,41);

  if(lg == 1){
  display.println("Time setting");
  }
  if(lg == 2){
  display.println("Reglage de l'heure");
  }

  pot1_val = analogRead(pot1); 
  val_menu = map(pot1_val, 0, 1023, 0, 4);
  state = digitalRead(boutton); 

  display.setCursor(0,ym1);
  display.println(">");
  display.display();

  if(val_menu <= 1){
    ym1=15;
  }

  if(val_menu > 1 && val_menu <= 2){
    ym1=28;
  }

  if(val_menu > 2){
    ym1=41;
  }

  if(val_menu <= 1 && state == 0){
    afh = 12; 
    delay(500);
    de = de + 500; 
    loop(); 
  }

  if(val_menu > 1 && val_menu <= 2 && state == 0){
    afh = 24; 
    delay(500);
    de = de + 500; 
    loop();   
  }

  if(val_menu > 2 && state == 0){

  delay(500);
  de = de + 500; 

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
    de = de + 500; 
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
    delay(500);
    de = de + 500; 
    loop();
  }

  display.display(); 

  }

  }

  }

}