// ----------------- KEYPAD PIN TANIMLAMALARI ------------------------------


#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h> 

LiquidCrystal_I2C lcdekranim(0x27,16,2);

int lm35Pin = A0;

int okunan_deger = 0;
float sicaklik_gerilim = 0;
float sicaklik = 0;

//---------------------------------
int basamak = 0;
const byte satir = 4;
const byte sutun = 4;
String girilen_sifre="";    
String sifre = "1234"; 

int yesil_led =22;   
int kirmizi_led =23; 


char tus_takimi[satir][sutun]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

byte satirpin[satir] = {13,12,11,10}; 
byte sutunpin[sutun]= {9,8,7,6}; 

Keypad tus_takimim= Keypad(makeKeymap(tus_takimi), satirpin, sutunpin, satir, sutun);


// ------------------------HAREKET SENSOR PIN TANIMLAMALARI ------------------------

int pirPin = 3;               
int lamba =53;
int hareket;                     

//-----------------------------------------------

//-------------------------ALEV SENSOR PIN TANIMLAMALARI -----------------------

int alevsensor =48;
int buzzer =49;

int alevdeger;
//-------------------------------------------------------


void setup() 
{
  
  lcdekranim.begin();                     
  lcdekranim.backlight();
  lcdekranim.setCursor(0,0);
  lcdekranim.print("Enter Password");

  pinMode(yesil_led,OUTPUT);
  pinMode(kirmizi_led,OUTPUT);
  pinMode(buzzer,OUTPUT);  
  pinMode(lamba,OUTPUT);  
  pinMode(buzzer,OUTPUT);
        
  pinMode(pirPin, INPUT);         
  pinMode(alevsensor,INPUT);
  
  digitalWrite(yesil_led,LOW);
  digitalWrite(kirmizi_led,LOW);
  digitalWrite(buzzer,LOW);     
              
  
  Serial.begin(9600);
  
}
 
void loop()
{

  
 sicaklik_sensor();
 sifre_giris();
 hareket_sensor();
 alevFonk();

 
}


// --------------- SICAKLIK SENSORUNUN FONKSİYON TANIMLAMASI ---------

 int sicaklik_sensor(){

  okunan_deger = analogRead(lm35Pin);
  sicaklik_gerilim = (okunan_deger / 1023.0)*5000;  
  sicaklik = sicaklik_gerilim /10.0; 

  

  if(sicaklik > 30){
    lcd_ekran_yuksek();
 
  }  
  else if (sicaklik <20){
    lcd_ekran_dusuk();
  }
  
  else{    
    lcd_ekran_normal();
    
  }
 }

 




//------------------LCD EKRAN YUKSEK SICAKLIK FONKSİYON TANIMLAMASI -----------------

int lcd_ekran_yuksek(){

 lcdekranim.clear();
 lcdekranim.setCursor(0,0);
 lcdekranim.print("SICAKLIK YUKSEK");
 lcdekranim.setCursor(1,4);
 lcdekranim.print("    ");
 lcdekranim.print(sicaklik);
 
 Serial.println("Sicaklik yuksek");
 delay(150);
 
  }





//------------------LCD EKRAN DUSUK SICAKLIK FONKSİYON TANIMLAMASI -----------------

int lcd_ekran_dusuk(){

  
 
 lcdekranim.clear();
 lcdekranim.setCursor(0,0);
 lcdekranim.print("SICAKLIK DUSTU");
 Serial.println("Sicaklik dusuk");
 delay(150);
 
  }


//------------------LCD EKRAN NORMAL SICAKLIK FONKSİYON TANIMLAMASI -----------------

int lcd_ekran_normal(){

 lcdekranim.clear();
 lcdekranim.setCursor(0,0);
 lcdekranim.print("   SICAKLIK");
 lcdekranim.setCursor(1,4);
 lcdekranim.print("    ");
 lcdekranim.print(sicaklik);
 Serial.println(sicaklik);

 delay(150);
 
  }


// -------------------------------------------------------------



int sifre_giris(){
    
  
char tus = tus_takimim.getKey();  // keypadden gelen değer
  if (tus != NO_KEY) {                            

     if(basamak <4){
      Serial.print("-----Basilan Tus : "); 
     Serial.println(tus); }   
     
     
       girilen_sifre =girilen_sifre + tus;
     basamak++;                          
     
   
  }



  if(tus=='#'){
      
      if((girilen_sifre.substring(0,basamak-1)) == sifre) {
        
     Serial.println("\n-------Correct Password");

        //yesil_led_yak(); 
       digitalWrite(yesil_led,HIGH);
       delay(400);
       digitalWrite(yesil_led,LOW);

       for(int i=0; i<16; i++)
       {
        //lcd.setCursor(i,1);
        //lcd.print(" ");
       }
        girilen_sifre = "";
        basamak = 0;
       }
     
      else if (( girilen_sifre.substring(0,basamak-1) != sifre))  {
       //lcd.setCursor(0,1);
       //lcd.print("Wrong Password");
      Serial.println("\n-------Wrong Password");

       // kirmizi_led_yak(); 
       digitalWrite(kirmizi_led,HIGH);
       delay(400);
       digitalWrite(kirmizi_led,LOW);
       
       for(int i=0; i<16; i++)
       {
        //lcd.setCursor(i,1);
        //lcd.print(" ");
       }
        girilen_sifre = "";
        basamak = 0;
        
      }
    }
  }
//}  
 //---------------------------------------------------------------------



// -------------------HAREKET SENSORU FONKSIYONU----------------------
int hareket_sensor(){
  hareket = digitalRead(pirPin); 
  Serial.print("Harket : " );
  Serial.println(hareket);
  delay(100);  
  
  if(hareket == HIGH){            

      Serial.println("Hareket Algilandi...");
      digitalWrite(lamba,HIGH);
      delay(300);
      //digitalWrite(yesil_led,LOW);
      


  }
  else{                         
    digitalWrite(lamba,LOW);
  }
}


//------------------------------------------------ ALEV FONKSİYONU---------------------------------------------------
int alevFonk(){
  alevdeger= digitalRead(alevsensor);

  Serial.print("AlevDeger : ");
  Serial.println(alevdeger);
  Serial.println();
  

  if(alevdeger==0){
    digitalWrite(buzzer,HIGH);
    delay(100);
    
  }

  else {
    digitalWrite(buzzer,LOW);
    }
  }













