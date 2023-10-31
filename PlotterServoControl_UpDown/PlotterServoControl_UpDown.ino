/*
PlotterServoControl_UpDown.ino
From https://github.com/svenhb/Plotter-ServoControl

Sets a servo position depending on input signal to predefined position 0 or 1.
Intended use: use the grbl spindle-, flood- or mist- on/off signal to control a servo to lift or lower a pen.

Code adapted from https://docs.arduino.cc/learn/electronics/servo-motors

NOTE: The servo should be powered from a separate voltage source to avoid controller reset 
	  due to voltage dips caused by high servo currents!

My 1st implementation 2014 with ATtiny44: http://svenhb.bplaced.net/?Elektronik___Stiftheber
Similar commercial implementation: https://github.com/sparkfun/Servo_Trigger
*/

#include <Servo.h>

int potiPin0 = 0;  		// analog pin to connect potentiometer for position-selection 0
int potiPin1 = 1;  		// analog pin to connect potentiometer for position-selection 1
int potiValue;    		// variable to read the value from the analog pin

int selectPin = 2;     	// input position-selection signal
int servoPin = 9;     	// output servo signal

Servo myServo;			// create servo object to control a servo

void setup() {
	pinMode(selectPin, INPUT_PULLUP);	// input position-selection signal
	pinMode(LED_BUILTIN, OUTPUT);		// output position-selection status LED
	myServo.attach(servoPin); 			// init servo
}

void loop() {
	int select = digitalRead(selectPin);	// get position-selection
	digitalWrite(LED_BUILTIN, select);   	// show position-selection status
	if (select == HIGH)
		potiValue = analogRead(potiPin1);		// reads the potiValue of the potentiometer 1 (potiValue between 0 and 1023)
	else
		potiValue = analogRead(potiPin0);		// reads the potiValue of the potentiometer 0 (potiValue between 0 and 1023)
			
	potiValue = map(potiValue, 0, 1023, 0, 180);	// scale it to use it with the servo (potiValue between 0 and 180)
	myServo.write(potiValue);						// sets the servo position according to the scaled potiValue
	delay(20);									// waits for the servo to get there
}