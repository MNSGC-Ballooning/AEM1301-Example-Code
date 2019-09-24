//Author: Ryan Bowers
//Sketch for flying a blimp based on XBee radio control

//Libraries to include
#include <XBee.h>
#include <mdMotorController.h>
#include <Servo.h>

//Pin definitions
#define E1_pin 12
#define M1_pin 11
#define E2_pin 3
#define M2_pin 2
#define servo_pin 7
//XBee serial connection
#define XBeeSerial Serial1

//---------EDIT AS NEEDED---------
#define killTime 1000 //time in ms without xBee contact before forcing motor shutdown
#define numMotors 3 //number of onboard motors (both regular and servo)
//--------------------------------

//Motor objects
mdMotorController motor1 = mdMotorController(E1_pin,M1_pin);
mdMotorController motor2 = mdMotorController(E2_pin,M2_pin);
Servo servo1;
//-------ADD/CHANGE AS NEEDED-------

//XBee object
XBee xbee = XBee(&XBeeSerial);

//Other system variables
unsigned long killTimer;
String message;
int motors[numMotors];

void setup() {
  //Serial.begin(115200);

  //pin setup
  pinMode(servo_pin,OUTPUT);
  servo1.attach(servo_pin);
  //motor initialization
  motor1.init();
  motor2.init();
  
  //Serial.println("Starting XBee");

  //start XBee communication
  XBeeSerial.begin(9600);

}

void loop() {
  if (xbee.available()) {
    //reset kill timer
    killTimer = millis();
    //read XBee message
    message = xbee.readStringUntil('\n');
    //Serial.println(message);

    //message is set of comma-separated numbers - 
    //parse into array of ints by order received
    int lastSplit = -1;
    int split = message.indexOf(',');
    byte i = 0;
    while (split != -1 && i<numMotors) {
      motors[i] = (message.substring(lastSplit+1,split)).toInt();
      lastSplit = split;
      split = message.indexOf(',',lastSplit+1);
      i++;
    }
    if (i < numMotors) {
      motors[i] = (message.substring(lastSplit+1,message.length())).toInt();
    }
    //By this point, all motor values should be in the motors array.
    //Assign these values to the correct motor objects.
    //MAKE SURE YOUR GROUND AND BLIMP CODE AGREE ON MOTOR VALUE ORDERS
    motor1.setSpeed(motors[0]);
    motor2.setSpeed(motors[1]);
    servo1.write(motors[2]);
    //---------ADD/CHANGE AS NEEDED---------
  }
  else if (millis() - killTimer > killTime) {
    //Lost XBee connection for too long - kill propulsion system
    motor1.setSpeed(0);
    motor2.setSpeed(0);
    //-------ADD EXTRA MOTORS HERE TOO-------
    //You can also reset servo values on connection loss if you want:
    //servo1.write(90); //90 is middle value, choose whatever makes sense for a reset.
  }

  //Debugging
  //Serial.print(motors[0]);
  //Serial.print(',');
  //Serial.print(motors[1]);
  //Serial.print(',');
  //Serial.println(motors[2]);
  
  //Update motor values
  motor1.run();
  motor2.run();
  //-----ADD AS NEEDED FOR MOTOR CONTROLLERS-----
}
