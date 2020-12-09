#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 5
#define RST_PIN 9
#define RELAY 3 //connect the relay to number 3 pin
#define BUZZER 2 // connect the buzzer to 2 pin
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000

//LED Light
const int pwm = 10 ; 




//LCD
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 8, en = 7, d4 = 6, d5 = 4, d6 = 1, d7 = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);




MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


void setup() 
{
  lcd.begin(17, 2);
  //Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  digitalWrite(RELAY, HIGH);

  //Serial.println("Put your card to the reader for scanning ...");
  //Serial.println();


  //LCD
    // set up the LCD's number of columns and rows:
  
  // Print a message to the LCD.
 //LED light
 pinMode(pwm,OUTPUT) ;  //Set pin 2 as output
  

}
void loop() 
{
   
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  //Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
 // Serial.println();
  //Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "1A 66 FD 84") // enter your own card number after copying it from serial monitor
  {
    //Serial.println("Authorized access");
 lcd.print("Access Success:)");
    //Serial.println();
    delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);


     analogWrite(pwm,2500) ;     //setting pwm to 25 
     delay(50) ;      //delay of 50 ms
    lcd.clear();
  }
 
 else   {
  
    //Serial.println(" Access denied");
 lcd.print("Access Denied :(");
  
 

    tone(BUZZER, 300);
    delay(DENIED_DELAY);
    noTone(BUZZER);
    lcd.clear();
  }

//LCD
// Turn off the blinking cursor:
  //lcd.noBlink();
  //delay(100);
  // Turn on the blinking cursor:
  //lcd.blink();
  //delay(3000);

  
}
