//Open Serial Monitor and change the Baud Rate to 115200 baud, to match the code.
// it expects the sd card to contain these three mp3 files
// but doesn't care whats in them
//
// sd:/mp3/0001.mp3
// sd:/mp3/0002.mp3
// sd:/mp3/0003.mp3
// sd:/mp3/0004.mp3
// sd:/mp3/0005.mp3
// sd:/mp3/0006.mp3
// sd:/mp3/0007.mp3
// sd:/mp3/0008.mp3
// sd:/mp3/0009.mp3
// sd:/mp3/0010.mp3
// sd:/mp3/0011.mp3 //big button for servant mode

//********************SOUND************************
const int buttonPin2 = 2;     // the number of the pushbutton pin
const int buttonPin3 = 3;     // the number of the pushbutton pin
const int buttonPin4 = 4;     // the number of the pushbutton pin
const int buttonPin5 = 8;     // the number of the pushbutton pin
const int buttonPin6 = 9;     // the number of the pushbutton pin
const int buttonPin7 = 12;    // the number of the pushbutton pin
const int buttonPin8 = A1;    // the number of the pushbutton pin
const int buttonPin9 = A2;    // the number of the pushbutton pin
const int buttonPin10 = A3;   // the number of the pushbutton pin
const int buttonPin11 = A4;   // the number of the pushbutton pin
const int buttonPin12 = A5;   // the number of the pushbutton pin

const int ledPin = 13;        // the number of the LED pin
int buttonState2 = 0;         // variable for reading the pushbutton status
int buttonState3 = 0;         // variable for reading the pushbutton status
int buttonState4 = 0;         // variable for reading the pushbutton status
int buttonState5 = 0;         // variable for reading the pushbutton status
int buttonState6 = 0;         // variable for reading the pushbutton status
int buttonState7 = 0;         // variable for reading the pushbutton status
int buttonState8 = 0;         // variable for reading the pushbutton status
int buttonState9 = 0;         // variable for reading the pushbutton status
int buttonState10 = 0;        // variable for reading the pushbutton status
int buttonState11 = 0;        // variable for reading the pushbutton status
int buttonState12 = 0;        // variable for reading the pushbutton status

int redLEDState = 0;          // red LED state for the Servant mode area
int blueLEDState = 0;         // blue LED state for the Servant mode area

int servantTime = 2200;       // time for the servant mode clip to play and turn off the LED

//NOTES: LED power must come from the 3.3V on the UNO and 
//must connect to the common anode (long) on the LED

//LIBRARIES===================================================
#include <SoftwareSerial.h>
#include <DFMiniMp3.h>
#include "SoftwareSerial.h"
#include "DFMiniMp3.h"
//for the LEDs
#include "OneButton.h"


//DEFINE===============================================
//********************LED************************
//Button pin number to turn off and on the Blue and Red LED
#define buttonLEDPin  A0 //analog pin A0
#define LEDPower 7 //pin to give all the LEDs Power instead of 3.3V
//Blue LED
#define blueLED 5//add pin number here must be PWM
//Red LED
#define redLED 6//add pin number here must be PWM

//VARIABLES============================================
//********************LED************************
//Button Variables for press control with on or off
//integer to hold current state
//1 for blue and 2 for red
int state = 1;
//integer to hold the last state
int old = 0;


//********************LED************************
//attach button to the OneButton Library Analog Pin A1
OneButton buttonLED(buttonLEDPin, true);

// implement a notification class,
// its member methods will get called 
//
class Mp3Notify
{
public:
  static void OnError(uint16_t errorCode)
  {
    // see DfMp3_Error for code meaning
    Serial.println();
    Serial.print("Com Error ");
    Serial.println(errorCode);
  }

  static void OnPlayFinished(uint16_t globalTrack)
  {
    Serial.println();
    Serial.print("Play finished for #");
    Serial.println(globalTrack);   
  }

  static void OnCardOnline(uint16_t code)
  {
    Serial.println();
    Serial.print("Card online ");
    Serial.println(code);     
  }

  static void OnUsbOnline(uint16_t code)
  {
    Serial.println();
    Serial.print("USB Disk online ");
    Serial.println(code);     
  }

  static void OnCardInserted(uint16_t code)
  {
    Serial.println();
    Serial.print("Card inserted ");
    Serial.println(code); 
  }

  static void OnUsbInserted(uint16_t code)
  {
    Serial.println();
    Serial.print("USB Disk inserted ");
    Serial.println(code); 
  }

  static void OnCardRemoved(uint16_t code)
  {
    Serial.println();
    Serial.print("Card removed ");
    Serial.println(code);  
  }

  static void OnUsbRemoved(uint16_t code)
  {
    Serial.println();
    Serial.print("USB Disk removed ");
    Serial.println(code);  
  }
};
// instance a DFMiniMp3 object, 
// defined with the above notification class and the hardware serial class
//
//DFMiniMp3<HardwareSerial, Mp3Notify> mp3(Serial1);

// Some arduino boards only have one hardware serial port, so a software serial port is needed instead.
// comment out the above definition and uncomment these lines
SoftwareSerial secondarySerial(10, 11); // RX, TX
DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(secondarySerial);

void setup() 
{

    //**********************LED***********************
  //setup the button for the LEDs as input
  //pinMode(button, INPUT);
  //setup the red and blue LEDS as output
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(LEDPower, OUTPUT);
  //make sure the LEDS are off
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(LEDPower, LOW);
  //links to button click events
  //single click function
  buttonLED.attachClick(singleclick);
  //long press function
  buttonLED.attachLongPressStop(longclick);

  
  //**********************SOUND***********************
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
  pinMode(buttonPin7, INPUT_PULLUP);
  pinMode(buttonPin8, INPUT_PULLUP);
  pinMode(buttonPin9, INPUT_PULLUP);
  pinMode(buttonPin10, INPUT_PULLUP);
  pinMode(buttonPin11, INPUT_PULLUP);
  pinMode(buttonPin12, INPUT_PULLUP);
  
  Serial.begin(9600);

  Serial.println("initializing...");
  
  mp3.begin();

   //set volume
  uint16_t volume = mp3.getVolume();
  Serial.print("volume ");
  Serial.println(volume);
  mp3.setVolume(30);


  //SERVANT MODE FOR STARTUP
  delay(100);
  //turn on the red LED
  digitalWrite(redLED, HIGH);
  digitalWrite(LEDPower, HIGH);
  mp3.playMp3FolderTrack(11);  // sd:/mp3/00011.mp3
  delay(servantTime);
  //turn off the red LED
  digitalWrite(LEDPower, LOW);
  digitalWrite(redLED, LOW);

 //delay(5000);
}


void loop() {

   //********************LED************************
  //check the status of the led button
  //short press to change LED color 
  //long press to turn off the LED
  buttonLED.tick();
  //short pause between checking the state of the LED button
  delay(10);

  //********************SOUND************************
  //read the pushbutton value into a variable
  int sensorVal = digitalRead(2);
  //print out the value of the pushbutton
  Serial.println(sensorVal);
  
  // read the state of the pushbutton value:
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);
  buttonState6 = digitalRead(buttonPin6);
  buttonState7 = digitalRead(buttonPin7);
  buttonState8 = digitalRead(buttonPin8);
  buttonState9 = digitalRead(buttonPin9);
  buttonState10 = digitalRead(buttonPin10);
  buttonState11 = digitalRead(buttonPin11);
  buttonState12 = digitalRead(buttonPin12);

  //read the state of the LEDs
  redLEDState = digitalRead(redLED);
  blueLEDState = digitalRead(blueLED);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState2 == LOW) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    // play track 1:
    Serial.println("track 1"); 
  mp3.playMp3FolderTrack(1);  // sd:/mp3/0001.mp3
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

// check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState3 == LOW) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    // play track 2:
    Serial.println("track 2"); 
  mp3.playMp3FolderTrack(2);  // sd:/mp3/0002.mp3
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState4 == LOW) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    // play track 3:
    Serial.println("track 3"); 
  mp3.playMp3FolderTrack(3);  // sd:/mp3/0003.mp3
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState5 == LOW) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    // play track 4:
    Serial.println("track 4"); 
  mp3.playMp3FolderTrack(4);  // sd:/mp3/0004.mp3
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState6 == LOW) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    // play track 5:
    Serial.println("track 5"); 
  mp3.playMp3FolderTrack(5);  // sd:/mp3/0005.mp3
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState7 == LOW) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    // play track 6:
    Serial.println("track 6"); 
  mp3.playMp3FolderTrack(6);  // sd:/mp3/0006.mp3
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState8 == LOW) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    // play track 7:
    Serial.println("track 7"); 
  mp3.playMp3FolderTrack(7);  // sd:/mp3/0007.mp3
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState9 == LOW) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    // play track 8:
    Serial.println("track 8"); 
  mp3.playMp3FolderTrack(8);  // sd:/mp3/0008.mp3
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState10 == LOW) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    // play track 9:
    Serial.println("track 9"); 
  mp3.playMp3FolderTrack(9);  // sd:/mp3/0009.mp3
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState11 == LOW) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    // play track 10:
    Serial.println("track 10"); 
  mp3.playMp3FolderTrack(10);  // sd:/mp3/0010.mp3
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }


  // SERVANT MODE 
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState12 == LOW) 
  {
    // FOR THE DIFFERENT LED SENARIOS---------
    //if both of the LEDs are turned off
    if (blueLEDState == LOW && redLEDState == LOW)
    {
      //turn on the red LED
      digitalWrite(redLED, HIGH);
      digitalWrite(LEDPower, HIGH);
      // turn LED on:
      digitalWrite(ledPin, HIGH);
      // play track 11:
      Serial.println("track 11"); 
      mp3.playMp3FolderTrack(11);  // sd:/mp3/0011.mp3
      
      delay(servantTime);
      //turn off the red LED
      digitalWrite(LEDPower, LOW);
      digitalWrite(redLED, LOW);
    }

    //if the Red LED is on
    if (redLEDState == HIGH)
    {
        // turn LED on:
      digitalWrite(ledPin, HIGH);
      // play track 11:
      Serial.println("track 11"); 
      mp3.playMp3FolderTrack(11);  // sd:/mp3/0011.mp3
    }

    //if the blue LED is on
    if (blueLEDState == HIGH)
    {
      //turn off the blue LED
      digitalWrite(LEDPower, LOW);
      digitalWrite(blueLED, LOW);
      digitalWrite(redLED, HIGH);
      digitalWrite(LEDPower, HIGH);
      // turn LED on:
      digitalWrite(ledPin, HIGH);
      // play track 11:
      Serial.println("track 11"); 
      mp3.playMp3FolderTrack(11);  // sd:/mp3/0011.mp3

      //turn back on the blue LED
      delay(servantTime);
      digitalWrite(LEDPower, LOW);
      digitalWrite(redLED, LOW);
      digitalWrite(blueLED, HIGH);
      digitalWrite(LEDPower, HIGH);
    }
    
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
  
}


//HELPER FUNCTIONS=======================================
//********************LED************************
//to change the LEDS color from blue to red or vice versus
void singleclick()
{
  //if state is 1 then the blue LED turns on
  if(state == 1)
  {
    //turn on the LED power
    digitalWrite(LEDPower, HIGH);
    //turn off the red LED just in case
    digitalWrite(redLED, LOW);
    //turn on the blue LED
    digitalWrite(blueLED, HIGH);
    //update the blue LED as the previous state
    old = state + 1;
  }

  //if state is 2 then turn on the red LED
  if(state == 2)
  {
    //turn off the blue LED just in case
    digitalWrite(blueLED, LOW);
    //turn on the red LED
    digitalWrite(redLED, HIGH);
    //update the red LED as the previous state
    old = state - 1;
  }

  state = old;
}

//turn off the LED with long click
void longclick()
{
  //turn off both of the LEDS
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);

  //cut off the LED power
  digitalWrite(LEDPower, LOW);
}
