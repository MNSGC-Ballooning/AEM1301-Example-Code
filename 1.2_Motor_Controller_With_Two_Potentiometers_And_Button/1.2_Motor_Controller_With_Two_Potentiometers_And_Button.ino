//Author: Billy Straub

/*
  For the H-Bridge Motor Controller:
    VD is powered by microcontroller and VS is powered by an external battery to power the attached motors/propellers.
    Both the external battery and the microcontroller use the same GND port.
    E1,E2: Motor Enable Pin.（PWM Control, so must be connected to a PWM port）
    M1,M2: Motor Signal Pin. Eg: M1 = 0,the motor rotates in forward direction. M1 = 1,the motor rotates in back direction. (Attached to digital port)
*/

#define E1 9                   //Defines the term "E1" as pin 9 (H-Bridge Motor Controller Enable Pins must be attached to PWM ports)
#define M1 10                  //Defines the term "M1" as pin 10
#define E2 11                  //Defines the term "E2" as pin 11 (H-Bridge Motor Controller Enable Pins must be attached to PWM ports)
#define M2 12                  //Defines the term "M2" as pin 12
#define Potentiometer_1Pin A0  //Defines the term "Potentiometer_1Pin" as pin A0
#define Potentiometer_2Pin A1  //Defines the term "Potentiometer_2Pin" as pin A1
#define pushButtonPin 2        //Defines the term "pushButtonPin" as pin 2

int Potentiometer_1Value;      //Creates an integer data type for "Potentiometer_1Value"
int Potentiometer_2Value;      //Creates an integer data type for "Potentiometer_2Value"
bool buttonState;              //Creates a boolean data type for "buttonState" (Boolean data types can only be true or false)
bool hBridgeForward = false;   //Defines "hBridgeForward" as false in the boolean data type
bool hBridgeBackward = true;   //Defines "hBridgeBackward" as true in the boolean data type



void setup() {

  pinMode(M1, OUTPUT);            //States that "M1" is an output given by the Arduino device
  pinMode(M2, OUTPUT);            //States that "M2" is an output given by the Arduino device
  pinMode(pushButtonPin, INPUT);  //States that "pushButtonPin" is an input into the Arduino device

}



void loop() {

  Potentiometer_1Value = analogRead(Potentiometer_1Pin);              //The "Potentiometer_1Value" integer will equal what the "Potentiometer_1Pin" reads  (Note: potentiometers are attached to analog pins, hence "analogRead")
  Potentiometer_2Value = analogRead(Potentiometer_2Pin);              //The "Potentiometer_2Value" integer will equal what the "Potentiometer_2Pin" reads
  Potentiometer_1Value = map(Potentiometer_1Value, 0, 1023, 0, 255);  //The "Potentiometer_1Value" originally reads from 0 to 1023 (b/c analog device), but the map function allows to the bounds to be changed to 0 to 255 (to PWM values)
  Potentiometer_2Value = map(Potentiometer_2Value, 0, 1023, 0, 255);  //The "Potentiometer_2Value" originally reads from 0 to 1023 (b/c analog device), but the map function allows to the bounds to be changed to 0 to 255 (to PWM values)
  analogWrite(E1, Potentiometer_1Value);                              //The H-Bridge Motor Controller's first Enable Pin will be able to go between 0 and 255 based on the "Potentiometer_1Value"
  analogWrite(E2, Potentiometer_2Value);                              //The H-Bridge Motor Controller's second Enable Pin will be able to go between 0 and 255 based on the "Potentiometer_2Value"
  
  buttonState = digitalRead(pushButtonPin);                           //The "buttonState" boolean data type will equal what the "pushButtonPin" reads  (Note: buttons are attached to digital pins, hence "digitalRead")
  if (buttonState == HIGH) {                                          //Conditional statement declaring that if the "buttonState" is "HIGH" (a.k.a. pressed down), then the following code will be run
    digitalWrite(M1, hBridgeBackward);                                //The H-Bridge Motor Controller's first Signal Pin will be set to "hBridgeBackward", which is defined as "true" above  (Allows the H-Bridge motors to run backwards when the button is held down)
    digitalWrite(M2, hBridgeBackward);                                //The H-Bridge Motor Controller's second Signal Pin will be set to "hBridgeBackward", which is defined as "true" above  (Allows the H-Bridge motors to run backwards when the button is held down)
  } 
  else {                                                              //Conditional statement declaring that if the first condition is not met (if the "buttonState" is not "HIGH", or in this case "LOW") then the following code will be run
    digitalWrite(M1, hBridgeForward);                                 //The H-Bridge Motor Controller's first Signal Pin will be set to "hBridgeForward", which is defined as "false" above  (Allows the H-Bridge motors to run forwards when the button is not held down)
    digitalWrite(M2, hBridgeForward);                                 //The H-Bridge Motor Controller's second Signal Pin will be set to "hBridgeForward", which is defined as "false" above  (Allows the H-Bridge motors to run forwards when the button is not held down)
  }

}
