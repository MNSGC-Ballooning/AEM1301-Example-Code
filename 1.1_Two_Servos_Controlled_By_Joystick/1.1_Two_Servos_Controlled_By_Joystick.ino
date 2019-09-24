//Author: Billy Straub

/*
Note: The Adafruit Thumbstick works by having two potentiometers inside of it. One potentiometer is in the X direction, and the other is in the Y direction.
        Since the thumbstick resides in the middle of the pad, the defualt potentiometer values are half of the max X value and half of the max Y value.
*/

#include <Servo.h>           //Servo library allows for servo use


#define Servo_1Pin 9         //Defines the term "Servo_1Pin" as pin 9 (Servo pins must be attached to PWM ports)
#define Servo_2Pin 10        //Defines the term "Servo_2Pin" as pin 10 (Servo pins must be attached to PWM ports)
#define ThumbstickXPin A0    //Defines the term "ThumbstickXPin" as pin A0
#define ThumbstickYPin A1    //Defines the term "ThumbstickYPin" as pin A1

Servo Servo_1;               //Defines "Servo_1" as a servo object
Servo Servo_2;               //Defines "Servo_2" as a servo object

int ThumbstickXValue;        //Creates an integer data type for "ThumbstickXValue"
int ThumbstickYValue;        //Creates an integer data type for "ThumbstickYValue"



void setup() {

  Servo_1.attach(Servo_1Pin);  //Attaches Servo_1 to whatever pin "Servo_1Pin" is defined as
  Servo_2.attach(Servo_2Pin);  //Attaches Servo_2 to whatever pin "Servo_2Pin" is defined as

}



void loop() {

  ThumbstickXValue = analogRead(ThumbstickXPin);              //The "ThumbstickXValue" integer will equal what the "ThumbstickXPin" reads
  ThumbstickXValue = map(ThumbstickXValue, 0, 1023, 0, 180);  //The "ThumbstickXValue" originally reads from 0 to 1023 (b/c analog device), but the map function allows to the bounds to be changed to 0 to 180
  Servo_1.write(ThumbstickXValue);                            //The servo will move between 0 and 180 degrees based on the "ThumbstickXValue"

  ThumbstickYValue = analogRead(ThumbstickYPin);              //The "ThumbstickYValue" integer will equal what the "ThumbstickYPin" reads
  ThumbstickYValue = map(ThumbstickYValue, 0, 1023, 0, 180);  //The "ThumbstickYValue" originally reads from 0 to 1023 (b/c analog device), but the map function allows to the bounds to be changed to 0 to 180
  Servo_2.write(ThumbstickYValue);                            //The servo will move between 0 and 180 degrees based on the "ThumbstickYValue"

}
