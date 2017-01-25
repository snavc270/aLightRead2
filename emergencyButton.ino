#include <Adafruit_Thermal.h>
#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
int outputPin = 13; 
int buttonState = 1;
int previousButtonState = 1;
const int buttonPin = 7;
int randomNum;
boolean firstPressed = false;
int charInt = 0;
int percentage = 100; 
int storyInt = 0; 

long time = 0; 
long debounce = 200; 
long dur_on = 0; 

//String story[30] = {"A Light Read...", "   ", "You", "want", "to", "be", "a", "master, ", "he", "said.", "Well",  "you","are", "not", "a", "master. ", "That", "took", "me", "down", "a", "peg.", "Seems", "I", "still", "have", "a", "lot", "to", "learn"};
//String story2[30] = {"She", "likes", "it", "She", "is", "like", "me", "Therefore", "I", "might", "like", "it", "She", "is", "like", "me", "She", "likes", "the", "things", "I", "like", "She", "likes", "this", "So", "I", "might", "like", "it"}; 
//String story5[12] = {"A Light Read...", "    ", "Under", "all", "this", "dirt", "the", "floor", "is", "really", "very", "clean"}; 
//String story4[49] = {"A Light Read...", "     ", "Color", "these", "fish", "Cut", "them", "out", "Punch", "a", "hole", "in", "the", "top", "of", "each", "fish", "Put", "a", "ribbon", "through", "all", "the", "holes",
//                    "Tie", "these", "fish", "together", "Now", "read", "what", "is", "written", "on", "these", "fish", "Jesus", "is", "a", "friend", "Jesus", "gathers", "friends", "I", "am", "a", "friend", "of", "Jesus"}; 
//String story3[30] = {"A Light Read...","    ",  "Into", "how", "small", "a", "place", "the", "word", "judgement", "can", "be", "compressed: ", "it", "must", "fit", "inside", "the", "brain", "of", "a", "ladybug", "as", "she", 
//                  "before", "my", "eyes", "makes", "a", "decision"}; 

String story[10] = {"a light read", "CYCC","www.alightread.wordpress.com", "So", "what", "am", "I", "now", "sliced", "bread?"}; 
String story2[16] = {"a light read", "CYCC","www.alightread.wordpress.com", "next", "time",  "I", "go", "to", "the", "grocery", "store,", "remind", "me", "to", "buy", "eggs."}; 
String story3[13] = {"a light read", "CYCC","www.alightread.wordpress.com","people", "are", "losing", "their", "lives", "because", "of", "taking", "dangerous", "selfies"}; 

void setup() {
  pinMode(7, OUTPUT); digitalWrite(7, LOW);
  // put your setup code here, to run once:
  Serial.begin(19200); 
  mySerial.begin(19200);
  printer.begin();

  // Charset selection alters a few chars in ASCII 0x23-0x7E range.
  printer.setCharset(CHARSET_NORWAY);
  // Code page selects alt symbols for 'upper' ASCII 0x80-0xFF.
  // There's a TON of these, best to check datasheet!
  printer.setCodePage(CODEPAGE_KATAKANA);

  

  printer.feed(2);
  printer.setDefault(); // Restore printer to defaults

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(outputPin, OUTPUT);
  randomSeed(analogRead(0));

}

void loop() {
//  Serial.println(buttonState); 
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW){
    digitalWrite(outputPin, HIGH);
  }else{
    digitalWrite(outputPin, LOW);
  }
  if(charInt <= 3){
    printer.justify('C'); 
  }else{
    printer.justify('R'); 
  }

  if(charInt == 0){
    printer.setSize('L');  
  }else{
    printer.setSize('S'); 
  }
  
  printer.upsideDownOn(); 
  switch(storyInt){
    case 0:
      if(charInt <= 3){
        percentage = 100; 
      }else{
        percentage = map(charInt, 0, 9, 75, 2); 
      }
        if (buttonState != previousButtonState) { 
          if (buttonState == 1) {
            int randomNum = random(0, 100);
            
           if (randomNum < percentage) {
                  printer.println(story[charInt]);  
                  Serial.println(story[charInt]);         
              if (charInt < 9) {
                charInt ++;
              }
            } else {
              mySerial.println(".");
              Serial.println("."); 
            }
         }
        } 
        if(charInt >= 10){
            storyInt = 1;
            charInt = 0;  
       }
      break; 

      case 1:
        if(charInt <=3){
          percentage = 100; 
        }else{
          percentage = map(charInt, 0, 15, 75, 5); 
        }
        if (buttonState != previousButtonState) {
          if (buttonState == 1) {
            int randomNum = random(0, 100);
           
            if (randomNum < percentage) {
                printer.print(story2[charInt]); 
                Serial.println(story2[charInt]); 
              if (charInt < 14) {
                charInt ++;
              }
            } else {
                mySerial.println(".");
                Serial.println("."); 
            }
         }
      }
      if(charInt >= 14){
            storyInt = 2; 
            charInt = 0; 
      }
      break; 
      

      case 2: 
        if(charInt <= 3){
          percentage = 100; 
        }else {
          percentage = map(charInt, 0, 12, 90, 4); 
        }
        if (buttonState != previousButtonState) {
          if (buttonState == 0) {
            int randomNum = random(0, 100);
           
            if (randomNum < percentage) {
                printer.print(story3[charInt]); 
                Serial.println(story3[charInt]); 
              if (charInt < 11) {
                charInt ++;
              }
            } else {
              mySerial.println(".");
              Serial.println("."); 
            }
         }
      }
      if(charInt >= 12){
            storyInt = 0; 
            charInt = 0; 
      }
      break; 
   
      default: 
        printer.println("master "); 
        break; 
  }

  if(dur_on > 10){
    charInt = 0; 
    storyInt = int(random(0,2)); 
  }

  if(buttonState == 1 && previousButtonState == 0 && millis()-time > debounce){
          time = millis(); 
   }

   if(buttonState == 1 && (millis()-time >debounce)){
          dur_on = (millis()-time)/ 1000; 
          
   }
   
  previousButtonState = buttonState;


}
