//Author: Ryan Bowers
//Edited by Billy Straub
//Sketch for flying a blimp based on XBee radio control using an Arudino MEGA

//Libraries to include
#include <XBee.h>
#include <Servo.h>

//Pin definitions
#define E1_pin 10  //PWM
#define M1_pin 9
#define E2_pin 8  //PWM
#define M2_pin 7
#define servo_pin 6  //PWM
#define XBeeSerial Serial1

//---------EDIT AS NEEDED---------
//#define killTime 1000 //time in ms without xBee contact before forcing motor shutdown
#define numMotors 3 //number of onboard motors (both regular and servo)
//--------------------------------

//Motor objects
//mdMotorController motor1 = mdMotorController(E1_pin,M1_pin);
//mdMotorController motor2 = mdMotorController(E2_pin,M2_pin);
Servo servo1;

//-------ADD/CHANGE AS NEEDED-------

//XBee object
XBee xbee = XBee(&XBeeSerial);

//Other system variables
//unsigned long killTimer;
String message;
int motors[numMotors];



void setup() {
  Serial.begin(9600);

  //pin setup
  servo1.attach(servo_pin); //!
  //motor initialization
  pinMode(M1_pin, OUTPUT);            //States that "M1" is an output given by the Arduino device
  pinMode(M2_pin, OUTPUT);            //States that "M2" is an output given by the Arduino device
  //motor1.init();
  //motor2.init();
  
  //Serial.println("Starting XBee");

  //start XBee communication
  XBeeSerial.begin(9600);

}



void loop() {
  if (xbee.available()) {
    //reset kill timer
    //killTimer = millis();
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
    
    //motor1.setSpeed(motors[0]);
    //motor2.setSpeed(motors[1]);
    //servo1.write(motors[2]);

    analogWrite(E1_pin, abs(motors[0]));  //abs() is the function corresponding with absolute value
    if (motors[0]>0){
      digitalWrite(M1_pin, true);  //"HIGH" is equivalent to "true" or "1", which supplies power to pin, turning the motors backwards
    }
    else {
      digitalWrite(M1_pin, false);  //"LOW" is equivalent to "false" or "0", which doesn't supply power, turning the motors forwards
    }
    
    analogWrite(E2_pin, abs(motors[1]));
    if (motors[1]>0){
      digitalWrite(M2_pin, true);
    }
    else {
      digitalWrite(M2_pin, false); 
    }

    servo1.write(motors[2]);
    
  //}
     
  /*  
    //---------ADD/CHANGE AS NEEDED---------
  
  else if (millis() - killTimer > killTime) {
    //Lost XBee connection for too long - kill propulsion system
    analogWrite(E1_pin, 0);
    analogWrite(E2_pin, 0);
    //-------ADD EXTRA MOTORS HERE TOO-------
    //You can also reset servo values on connection loss if you want:
    //servo1.write(90); //90 is middle value, choose whatever makes sense for a reset.
  }
*/
  //Debugging
  Serial.print(motors[0]);
  Serial.print(',');
  Serial.print(motors[1]);
  Serial.print(',');
  Serial.println(motors[2]);
  
  //Update motor values
  //motor1.run();
  //motor2.run();
  //-----ADD AS NEEDED FOR MOTOR CONTROLLERS-----

  delay(10);

  }
}
