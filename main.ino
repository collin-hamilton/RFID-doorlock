//RFID DoorLock
//
//
// created by collin hamilton

// include the library code:
#include <LiquidCrystal.h>
#include <Keypad.h>
#include "pitches.h"
#include <SPI.h>
#include <MFRC522.h>
#include <Stepper.h> 
#define SS_PIN 53
#define RST_PIN 5
//Create RFID instance
MFRC522 mfrc522(SS_PIN, RST_PIN);
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(41, 39, 49, 47, 45, 43);
const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 15;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {37, 35, 33, 31}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {29, 27, 25, 23}; //connect to the column pinouts of the keypad
String pin = "1234";
//initialize an instance of class NewKeypad
Keypad myKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
int buzzer = 2;
String num1;
int melody_correct[] = {
  NOTE_C5,NOTE_F5,NOTE_A5};
int melody_incorrect[] = {
  NOTE_F5,NOTE_C5};
int duration = 500;  // 500 miliseconds
//RGB Variables
int redPin= 6;
int greenPin = 4;
int bluePin = 3;
bool check = false;
void setup() {
  //Set up Stepper
  myStepper.setSpeed(rolePerMinute);
  // set up RGB LED
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzer,OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("    Welcome!");
  delay(3000);
}




void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}


void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Please enter Pin");
  lcd.setCursor(0, 1);
  char key = myKeypad.getKey();
  unsigned char i;
  if (key != NO_KEY && (key=='1'||key=='2'||key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0'))// check which key is pressed by checking its integer value
    {
      if (num1.length() < 4){
        num1 = num1 + key; // storing the value of key pressed in num1
        lcd.setCursor(6, 1); 
        lcd.print(num1); // printing the first number entered
      }
    }
   if (num1.length() == 4){
     if (num1 == pin) {
      num1 = "";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  Pin Accepted");
      setColor(0, 255, 0);
      for (int thisNote = 0; thisNote < 3; thisNote++) {
      // pin8 output the voice, every scale is 0.5 sencond
      tone(2, melody_correct[thisNote],duration);
      delay(200);
    }
      delay(2000);
      setColor(0, 0, 0);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  Scan RFID Tag");
      while (check == false){
      //Start RFID Scan
        SPI.begin();      // Initiate  SPI bus
        mfrc522.PCD_Init();   // Initiate MFRC522
      // Look for new cards
          if ( ! mfrc522.PICC_IsNewCardPresent()) 
          {
            continue;
          }
          // Select one of the cards
          if ( ! mfrc522.PICC_ReadCardSerial()) 
          {
           continue;
          }
          String content= "";
          byte letter;
          for (byte i = 0; i < mfrc522.uid.size; i++) 
          {
             content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
             content.concat(String(mfrc522.uid.uidByte[i], HEX));
          }
          content.toUpperCase();
          if (content.substring(1) == "6A 17 9A 3A") //change here the UID of the card/cards that you want to give access
          {
            check = true;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(" RFID Accepted");
            setColor(0, 255, 0);
            for (int thisNote = 0; thisNote < 3; thisNote++) {
            // pin8 output the voice, every scale is 0.5 sencond
            tone(2, melody_correct[thisNote],duration);
            delay(200);
          }
          delay(2000);
          //Begin Stepper Motor Operation
          lcd.clear();
          lcd.setCursor(0, 0);
          setColor(0, 0, 0);
          lcd.print("...Unlocking...");
          myStepper.step(stepsPerRevolution);
          lcd.clear();
          while (1==1){
            ;
          }}
         
         else   {
            lcd.clear();
            lcd.setCursor(0, 0);
            setColor(255, 0, 0);
            lcd.print(" Incorrect RFID");
            for (int thisNote = 0; thisNote < 2; thisNote++) {
          // pin8 output the voice, every scale is 0.5 sencond
          tone(2, melody_incorrect[thisNote], duration);
          delay(3000);
          setColor(0, 0, 0);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("  Scan RFID Tag");
                }
                
      }
      }}
    else {
      num1 = "";
      lcd.clear();
      lcd.setCursor(0, 0);
      setColor(255, 0, 0);
      lcd.print("Incorrect Pin");
      for (int thisNote = 0; thisNote < 2; thisNote++) {
    // pin8 output the voice, every scale is 0.5 sencond
    tone(2, melody_incorrect[thisNote], duration);
    delay(300);
  }
    delay(2000);
    setColor(0, 0, 0);
      }
  }

}
