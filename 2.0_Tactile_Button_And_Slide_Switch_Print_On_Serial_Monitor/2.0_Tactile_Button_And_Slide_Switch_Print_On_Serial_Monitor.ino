//Author: Billy Straub

/*
Note: +5v or +3.3v should be run into the button/switch and the exit side should have a 10k ohm resistor run to ground (GND)
        Between the resistor and the button/switch, a wire should be run to the designated digital port of the button/switch
*/

#define pushButtonPin 2        //Defines the term "pushButtonPin" as pin 2
#define slideSwitchLeftPin 3   //Defines the term "slideSwitchLeft" as pin 3
#define slideSwitchRightPin 4  //Defines the term "slideSwitchRight" as pin 4

bool buttonState;              //Creates a boolean data type for "buttonState" (Boolean data types can only be true or false)
bool slideSwitchLeftState;     //Creates a boolean data type for "slideSwitchLeftState"
bool slideSwitchRightState;    //Creates a boolean data type for "slideSwitchRightState"



void setup() {

  Serial.begin(9600);                //Starts the serial monitor at a baud rate of 9600

  pinMode(pushButtonPin, INPUT);     //States that "pushButtonPin" is an input into the Arduino device
  pinMode(slideSwitchLeftPin, INPUT);   //States that "slideSwitchLeft" is an input into the Arduino device
  pinMode(slideSwitchRightPin, INPUT);  //States that "slideSwitchRight" is an input into the Arduino device

}



void loop() {

  buttonState = digitalRead(pushButtonPin);                  //The "buttonState" boolean data type will equal what the "pushButtonPin" reads
  slideSwitchLeftState = digitalRead(slideSwitchLeftPin);    //The "slideSwitchLeftState" boolean data type will equal what the "slideSwitchLeftPin" reads
  slideSwitchRightState = digitalRead(slideSwitchRightPin);  //The "slideSwitchRightState" boolean data type will equal what the "slideSwitchRightPin" reads

  Serial.print("Button State: ");                            //Prints phrase in quotation marks on serial monitor
  Serial.println(buttonState);                               //Prints "buttonState" and ends the line

  Serial.print("The Slide Switch is ");                      //Prints phrase in quotation marks on serial monitor
  if (slideSwitchLeftState == HIGH) {                        //Conditional statement declaring that if the "slideSwitchLeftState" is "HIGH" (a.k.a. slide is to the left), then the following code will be run
    Serial.println("LEFT");                                  //Prints phrase in quotation marks on serial monitor and ends the line
  }
  else if (slideSwitchRightState == HIGH) {                  //Conditional statement declaring that if the first conditional statement was false and if the "slideSwitchRightState" is "HIGH" (a.k.a. slide is to the right), then the following code will be run
    Serial.println("RIGHT");                                 //Prints phrase in quotation marks on serial monitor and ends the line
  }

  Serial.println("=========================");               //Prints phrase in quotation marks on serial monitor

  delay(1000);                                               //Waits 1000 milliseconds (1 second) before running the code again (Allows for the values to print on the serial monitor every second)

}
