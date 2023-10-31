/*
PlotterServoControl_PWM.ino
From https://github.com/svenhb/Plotter-ServoControl

Translates a 1% - 100% PWM signal to a RC-Servo compatible signal.
A 0% PWM signal (spindle off) sets a predefined position by a potentiometer.
Intended use: use the grbl spindle PWM signal to control a servo to lift or lower a pen.

Code adapted from https://forum.arduino.cc/t/how-do-i-read-pwm-signals-from-rx-more-efficiently/697623/18

NOTE: The servo should be powered from a separate voltage source to avoid controller reset 
	  due to voltage dips caused by high servo currents!
*/

#include <Servo.h>

void isrPinChange();	// interrupt service routine

int potiPin0 = 0;  		// analog pin to connect potentiometer for position-selection 0
int potiValue;    		// variable to read the value from the analog pin
int pwmPin = 2;     	// input PWM signal from grbl-controller

int servoPin = 9;     	// output servo signal
int missingISR;			// detect missing interrupt because of PWM = 0% or 100%

uint32_t	pwmStart; 	
uint32_t	pwmWidth; 
uint32_t	pwmMax; 
uint8_t     pwmDegrees;

// there is a jitter, when counting PWM width and period, try to smooth the values
const int averageCount = 20; 
int averageIndexWidth = 0;
int averageIndexMax = 0;
uint32_t averageBufferWidth[averageCount]; 
uint32_t averageBufferMax[averageCount]; 
uint32_t averageWidth; 
uint32_t averageMax; 

Servo myServo;			// create servo object to control a servo

void setup() {
	pinMode(pwmPin, INPUT_PULLUP);
	pinMode(LED_BUILTIN, OUTPUT);		// output PWM pin-level
	myServo.attach(servoPin); 
	attachInterrupt( digitalPinToInterrupt( pwmPin ), &isrPinChange, CHANGE );                
}

void loop() {
	if (missingISR > 2)			// no interrupt because of PWM = 0% or 100% ?
	{
		if ( digitalRead(pwmPin) == HIGH )
		{	pwmDegrees = 180; }
		else
		{	potiValue = analogRead(potiPin0);		// reads the potiValue of the potentiometer 0 (potiValue between 0 and 1023)
			pwmDegrees = map(potiValue, 0, 1023, 0, 180);	// scale it to use it with the servo (potiValue between 0 and 180)
		}
	}
	else
	{
		averageWidth = 0;
		averageMax = 0;
		for (int i = 0; i < averageCount; i++)
		{ 	averageWidth += averageBufferWidth[i];
			averageMax += averageBufferMax[i];		
		}
		averageWidth =  averageWidth / averageCount;	// calculate average pulse-width
		averageMax = averageMax / averageCount;			// calculate average pulse-duration
		pwmDegrees = (uint8_t)map( averageWidth, 0, averageMax, 0, 180 );        
	}

	myServo.write(pwmDegrees);	// sets the servo position according to the pwm signal
	
	missingISR++;				// counter must be cleared in ISR
	delay(20);					// waits for the servo to get there
}

void isrPinChange( void )
{
	missingISR=0;
    uint32_t timeNow = micros();
	int pwmLevel = digitalRead(pwmPin);		// get pwm level
	digitalWrite(LED_BUILTIN, pwmLevel);   	// show pwm level
        
    if( pwmLevel == HIGH )
    {
		pwmMax = timeNow - pwmStart;		// pulse-duration usually 1024 µs = ca. 1 kHz
        pwmStart = timeNow;
		if (pwmMax < 10000 )
		{	averageBufferMax[averageIndexMax++] = pwmMax;
			if (averageIndexMax >= averageCount)
				averageIndexMax = 0;
		}
    }
    else
    {
        pwmWidth = timeNow - pwmStart;           
		if (pwmWidth <= pwmMax )
		{	averageBufferWidth[averageIndexWidth++] = pwmWidth;
			if (averageIndexWidth >= averageCount)
				averageIndexWidth = 0;
		}
    }
}