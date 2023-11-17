# Plotter-ServoControl
Collection of Arduino sketches to control a RC-servo for pen up/down motion

Use an Arduino-Nano (or similar) to generate a PWM signal for a RC-Servo.

### PlotterServoControl_UpDown 
* Sets a servo position depending on input signal to predefined position 0 or 1.
* Intended use: use the grbl spindle-, flood- or mist- on/off signal to control a servo to lift or lower a pen or to control a gripper.


### PlotterServoControl_PWM 
* Translates a 1% - 100% PWM signal to a RC-Servo compatible signal.
* A 0% PWM signal (spindle off) sets a predefined position by a potentiometer.
* Intended use: use the grbl spindle PWM signal to control a servo to lift or lower a pen.
 
 
 I lift the pen with the help of a thin string (fishing line). In order to be able to adjust the height as finely as possible, the servo lever must be as short as possible. I use the servo axis to wind the line. To do this, I drilled through the side of the servo axle and threaded the cord through it.
