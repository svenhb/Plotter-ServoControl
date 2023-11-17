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

 
 ### Servo setup 
 I lift the pen with the help of a thin string (fishing line). In order to be able to adjust the height as finely as possible, the servo lever must be as short as possible. I use the servo axis to wind the line. To do this, I drilled through the side of the servo axle and threaded the cord through it.
<img src="https://github.com/svenhb/Plotter-ServoControl/assets/19973251/956ff810-169d-4861-9860-30374cf65fa1" width="800">

<img src="https://github.com/svenhb/Plotter-ServoControl/assets/19973251/475b52da-94f5-41c7-9f77-7d5a26e08cbe" width="800">


<img src="https://github.com/svenhb/Plotter-ServoControl/assets/19973251/4a094eb8-f4f2-4545-ac00-705f1729a4b1" height="800">


<img src="https://github.com/svenhb/Plotter-ServoControl/assets/19973251/7633d544-4a24-43d5-84ef-82146ebd8c6a" height="800">
