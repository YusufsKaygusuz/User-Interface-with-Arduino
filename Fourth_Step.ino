#include <LCD5110_Graph.h>
LCD5110 lcd(8,9,10,11,12);

extern uint8_t SmallFont[];
extern uint8_t MediumNumbers [];
extern uint8_t TinyFont [];

extern uint8_t bpilC[];
extern uint8_t empty[]; // Pil değerini gösteren simgenin içi boş (pil bitme seviyesinde) şeklini tanıtıyoruz.
extern uint8_t yirmi[]; // Pil değerini gösteren simgenin içi 1/5 dolu şeklini tanıtıyoruz.
extern uint8_t kirk[]; // Pil değerini gösteren simgenin içi 2/5 dolu şeklini tanıtıyoruz.
extern uint8_t altmis[]; // Pil değerini gösteren simgenin içi 3/5 dolu şeklini tanıtıyoruz.
extern uint8_t seksen[]; // Pil değerini gösteren simgenin içi 4/5 dolu şeklini tanıtıyoruz.
extern uint8_t full[];
extern uint8_t unlem[];

float Vpower = 5;
float R1 = 200000;
float R2 = 100000;

boolean ArkaIsik = false;
int contrast=65;

int page =0;
int menuitem=1;
int sayac = 1;

volatile boolean up = false;
volatile boolean down = false;
volatile boolean middle = false;
volatile boolean geri = false;

int asagibuton = 0;
int yukaributon = 0;
int secmebuton = 0;
int geributon =0;

int lastasagibuton = 0;
int lastyukaributon = 0;
int lastsecmebuton = 0;
int lastgeributon= 0;

const int buzzer=2;

void setup() {
  pinMode(6, INPUT);
  pinMode(5, INPUT);
  pinMode(4, INPUT);
  pinMode(3, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(1 , OUTPUT);
   
  lcd.InitLCD();
}

void loop(){
  drawMenu();

   asagibuton = digitalRead(5);
   secmebuton =digitalRead(4); 
   yukaributon =digitalRead(6);
   geributon = digitalRead(3);

   CheckIfasagibutonIsPressed();
   CheckIfyukaributonIsPressed();
   CheckIfsecmebutonIsPressed();
   CheckIfgeributonIsPressed();

    if(up && page == 0)
   {
    up = false;

    lcd.clrScr();
    lcd.setFont(SmallFont);
    lcd.print("<<Blaockade>>",6,12);
    lcd.drawRect(0,26,83,40);
    for(int i=2; i<=80; i++)
    {
      lcd.drawRect(0,26,i,40);
      lcd.update();
      delay(7);
    }
    lcd.update();
    page =1;
   }
   else if(down && page == 0)
   {
    down = false;
    
    lcd.clrScr();
    lcd.setFont(SmallFont);
    lcd.print("<<Blaockade>>",6,12);
    lcd.drawRect(0,26,83,40);
    for(size_t i=2; i<=80; i++)
    {
      lcd.drawRect(0,26,i,40);
      lcd.update();
      delay(7);
    }
    lcd.update();
    page =1;
   }
   else if(middle && page == 0)
   {
    middle = false;
    
    lcd.clrScr();
    lcd.setFont(SmallFont);
    lcd.print("<<Blaockade>>",6,12);
    lcd.drawRect(0,26,83,40);
    for(size_t i=2; i<=80; i++)
    {
      lcd.drawRect(0,26,i,40);
      lcd.update();
      delay(7);
    }
    lcd.update();
    page =1;
   }
   else if(geri && page == 0)
   {
    geri =false;
    
    lcd.clrScr();
    lcd.setFont(SmallFont);
    lcd.print("<<Blaockade>>",6,12);
    lcd.drawRect(0,26,83,40);
    for(size_t i=2; i<=80; i++)
    {
      lcd.drawRect(0,26,i,40);
      lcd.update();
      delay(7);
    }
    lcd.update();
    page =1;
   }

   if( up && page ==1 )
   {
    up = false; 
    menuitem--;

    if(menuitem == 0)
    {
      menuitem = 3;
    }
   }
   else if (up && page == 2) {
    up = false;
    contrast++;
    SetContrast();
   }
   else if (up && page == 3){
    up = false;
    sayac--;

   if (sayac == 0) {
    sayac =2;
   }
   }

   if (down && page == 1){
    down = false;
    menuitem++;
    if (menuitem == 4){
      menuitem =1;
    }
   }
   else if (down && page == 2){
    down =false;
    contrast--;
    SetContrast();
   }
   else if (down && page == 3){
   down = false; 
   sayac++;
   if( sayac == 3) {
    sayac=1;
   }
   }

   if(geri){
    geri = false;

    if(page==3){
      page =1 ;
    }
   }

   if(middle){
    middle =false;
    
    if (page == 1 && menuitem ==2)
    {
      if(ArkaIsik)
      {
        ArkaIsik= false;
        turnArkaIsikOff();
      }
    else {
      ArkaIsik = true;
      turnArkaIsikOn();
    }
   }
   
   if(page ==1 && menuitem==3)
   {
    page = 3;
   }
   else if (page == 1 && menuitem ==1)
   {
    page =2;
   }
   else if (page == 2){
    page = 1;
   }
   else if (page == 3 && sayac ==1){
    page = 4;  
   }
   else if (page == 3 && sayac == 2){
    page = 5;
   }
   else if(page == 4){
    page =3;
   }
   else if(page == 5) {
    page =3;
   }
} 

}
void CheckIfasagibutonIsPressed(){
  if(asagibuton != lastasagibuton)
  {
    if(asagibuton == 0) {
      down = true; 
    }
    delay(50);    
  }
  lastasagibuton = asagibuton;
}

void CheckIfyukaributonIsPressed(){
  if (yukaributon != lastyukaributon)
  {
    if(yukaributon == 0){
      up = true;
    }
    delay(50);
  }
  lastyukaributon = yukaributon;
}

void CheckIfsecmebutonIsPressed (){
  if (secmebuton != lastsecmebuton)
  {
    if(secmebuton ==0){
      middle = true;
    }
    delay(50);
    }
    lastsecmebuton = secmebuton; 
}

void CheckIfgeributonIsPressed() {
  if (lastgeributon != geributon)
  {
    if(geributon == 0){
      geri = true;  
    }
    delay(50);
  }
  lastgeributon = geributon;
}

void drawMenu () {

  if(page==0){
    lcd.clrScr();
    lcd.setFont(SmallFont);
    lcd.print("<<Blockade>>",6,12);
    lcd.setFont(TinyFont);
    lcd.print("Press any button!",12,28);
    lcd.update();
  }

  else if(page==1){
  lcd.clrScr();
  lcd.setFont(SmallFont);
  lcd.print("Main Menu",14,0);
  lcd.drawLine(8,8,76,8);
  lcd.print("Contr Value",2,13);
  
  lcd.print("Backlight: ",2,24);
  if(ArkaIsik != 0) {
    lcd.print("On",60,24); 
  }
  else{
    lcd.print("Off",60,24);
  }
  lcd.print("Battary Type",2,36);

  if(menuitem == 1) 
  {
    lcd.drawRoundRect(0,11,82,21);
  }

  if(menuitem == 2) {
    lcd.drawRoundRect(0,21,82,32);
  }

  if(menuitem == 3) {
    lcd.drawRoundRect(0,34,82,46);
  }
   lcd.update();
  }

  else if(page == 2) {
      lcd.clrScr();
      lcd.setFont(SmallFont);
      lcd.print("Contrast",16,0);
      lcd.print("Value:", 22 ,9);
      lcd.setFont(MediumNumbers);
      lcd.printNumI(contrast,30,24);
      lcd.update();
  }

  else if (page == 3){
  lcd.clrScr();
  lcd.setFont(SmallFont);
  lcd.print("Battary",18,0);
  lcd.print("Type",27,10);
  lcd.drawLine(6,19,76,19);
  lcd.print(">1.5V Battary",2,23);
  lcd.print(">9V Battary",2,34);

   if(sayac == 1) {
    lcd.drawRoundRect(0,21,83,32);
   }
   if (sayac == 2) {
    lcd.drawRoundRect(0,32,83,42);
   }
   lcd.update(); 
  }
  
  else if( page == 4) {

 float V = (analogRead(0) * Vpower) /1024.0;
 float V2 = V / (R2 / (R1 + R2)); 

  if (V2 <0.9){ 
lcd.clrScr(); //Ekranı temizliyoruz.
lcd.drawBitmap(0,0,empty,84,48);
lcd.setFont(MediumNumbers);
lcd.printNumF(V2,2,35,15);
}
if (V2 >0.9 && V2 <1.0){ 
lcd.clrScr(); 
lcd.drawBitmap(0,0,yirmi,84,48);
lcd.setFont(MediumNumbers);
lcd.printNumF(V2,2,35,15); 
}
if (V2 >1.0 && V2 <1.1){ 
lcd.clrScr(); 
lcd.drawBitmap(0,0,kirk,84,48);
lcd.setFont(MediumNumbers);
lcd.printNumF(V2,2,35,15); 
}
if (V2 >1.1 && V2 <1.2){ 
lcd.clrScr(); 
lcd.drawBitmap(0,0,altmis,84,48);
lcd.setFont(MediumNumbers);
lcd.printNumF(V2,2,35,15); 
}
if (V2 >1.2 && V2 <1.4){ 
lcd.clrScr(); 
lcd.drawBitmap(0,0,seksen,84,48);
lcd.setFont(MediumNumbers);
lcd.printNumF(V2,2,35,15);
}
if (V2 >1.4 && V2<1.6){ 
lcd.clrScr(); 
lcd.drawBitmap(0,0,full,84,48);
lcd.setFont(MediumNumbers);
lcd.printNumF(V2,2,35,15); 
}
if(V2>1.6){
  lcd.clrScr();
  lcd.setFont(SmallFont);
  lcd.drawBitmap(0,0,unlem,45,48);
  lcd.print("HIGH",46,12);
  lcd.print("VOLTAGE",38, 22);
  lcd.update();
  digitalWrite(buzzer, HIGH);
}
else{
  digitalWrite(buzzer, LOW);
}
lcd.setFont(TinyFont);
lcd.print("By",56,36);
lcd.print("Yusuf S.",46,42);
lcd.update();
}
  else if (page == 5) {
   float V = (analogRead(0) * Vpower) /1024.0;
   float V2 = V / (R2 / (R1 + R2));   
  
if (V2 <1.0){ 
lcd.clrScr(); //Ekranı temizliyoruz.
lcd.drawBitmap(0,0,empty,84,48);
lcd.setFont(MediumNumbers);
lcd.printNumF(V2,2,35,15);
}
if (V2 >1.0 && V2 < 1.8){ 
lcd.clrScr(); 
lcd.drawBitmap(0,0,yirmi,84,48);
lcd.setFont(MediumNumbers);
lcd.printNumF(V2,2,35,15);
}
if (V2 > 1.8 && V2<3.6) { 
lcd.clrScr(); 
lcd.drawBitmap(0,0,kirk,84,48);
lcd.setFont(MediumNumbers);
lcd.printNumF(V2,2,35,15); 
}
if (V2 >3.6 && V2 < 5.4){ 
lcd.clrScr(); 
lcd.drawBitmap(0,0,altmis,84,48);
lcd.setFont(MediumNumbers);
lcd.printNumF(V2,2,35,15); 
}
if (V2 >5.4 && V2 < 7.2){ 
lcd.clrScr(); 
lcd.drawBitmap(0,0,seksen,84,48);
lcd.setFont(MediumNumbers);
lcd.printNumF(V2,2,35,15);
}
if (V2 >7.2){ 
lcd.clrScr(); 
lcd.drawBitmap(0,0,full,84,48);
lcd.setFont(MediumNumbers);
lcd.printNumF(V2,2,35,15); 
}

lcd.setFont(TinyFont);
lcd.print("Created By:",37,36);
lcd.print("Yusuf S.Kay.",36,42);
lcd.update();
}
  }

  void turnArkaIsikOn() {
    digitalWrite(1,HIGH);
  }
  
  void turnArkaIsikOff() {
    digitalWrite(1,LOW);
  }

  void SetContrast() {
    lcd.setContrast(contrast);
    lcd.update();
  }
