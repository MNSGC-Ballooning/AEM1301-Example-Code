//Author: Ryan Bowers
//Sketch to drive a control board, process values, and transmit desired actions to blimp via XBee

//Libraries to include
#include <XBee.h>

//Pin definitions
#define pot1_pin A0
#define pot2_pin A4
#define slidepot_pin A2
#define button_pin 8
//XBee serial connection
#define XBeeSerial Serial1

//XBee object
XBee xbee = XBee(&XBeeSerial);

//Input device values
int pot1, pot2, slidepot;
bool button;
//Requested motor values
int motor1, motor2, servo1;
//String to transmit to blimp
String message;

void setup() {
  //Serial.begin(115200);
  
  //pin setup
  pinMode(pot1_pin,INPUT);
  pinMode(pot2_pin,INPUT);
  pinMode(slidepot_pin,INPUT);
  pinMode(button_pin,INPUT_PULLUP);

  //start XBee communication
  XBeeSerial.begin(9600);

}

void loop() {
  //read input devices
  pot1 = analogRead(pot1_pin);
  pot2 = analogRead(pot2_pin);
  slidepot = analogRead(slidepot_pin);
  button = digitalRead(button_pin);
  //-------ADD/CHANGE AS NEEDED-------

  //convert to desired motor values - 0-255 for regular motors, 0-180 for servo
  //-------IMPORTANT-------
  //This is where the majority of your control board implementation happens.
  //You need to choose how to assign potentiometer and button values to motors - 
  //eg. coupling multiple motors to a single pot,
  //mapping forward/reverse to full pot range,
  //adding an on/off switch, etc.
  //Here's where your team has the most design flexibility - use it.

  //My example is a bare minimum - 1 pot/motor or servo, with a reverse push-button
  motor1 = pot1/1023.0*255;
  motor2 = pot2/1023.0*255;
  servo1 = slidepot/1023.0*180;
  if (!button) {
    motor1 = -motor1;
    motor2 = -motor2;
  }

  //Once all motor values are assigned, combine them into a single string of numbers
  //separated by commas, and transmit to the blimp.
  //ORDER MATTERS - MAKE SURE YOUR BLIMP CODE ASSIGNS THE RIGHT VALUES TO THE RIGHT MOTORS
  message = String(motor1) + ',' + String(motor2) + ',' + String(servo1);
  xbee.println(message);
  //Serial.println(message);

  //Transmit ~10 times per second.
  //You can adjust if needed, but is updating more frequently really going to make these things
  //any more controllable?
  delay(100);
}
