# Plotter-ServoControl
Collection of Arduino sketches to control a RC-servo for pen up/down motion

### PlotterServoControl_UpDown 
* Sets a servo position depending on input signal to predefined position 0 or 1.
* Intended use: use the grbl spindle-, flood- or mist- on/off signal to control a servo to lift or lower a pen.


### PlotterServoControl_PWM 
* Translates a 1% - 100% PWM signal to a RC-Servo compatible signal.
* A 0% PWM signal (spindle off) sets a predefined position by a potentiometer.
* Intended use: use the grbl spindle PWM signal to control a servo to lift or lower a pen.
