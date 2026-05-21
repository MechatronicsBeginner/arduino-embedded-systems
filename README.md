# Multi-Actuator Control via Arduino with LCD readout

Potentiometer-controlled servo motor and DC motor with LCD displaying output from Servomotor angle and potentiometer reading. 

### Background 

Sophomore Mechatronics Engineering student at MTSU with six years of professional automotive diagnostics experience. This project is part of a self-directed embedded systems portfolio targeting robotics and autonomous systems internships.



## Components Used

- Arduino Uno R3
- Servo Motor
- 2 potentiometers (10k ohm each)
- 16x2 LCD display
- jumper wires(male-to-male)
- breadboard
- L293D H-bridge motor driver
- DC motor

## Concepts Used

- ADC analog input reading
- PWM servo control
- Non-blocking timing with millis() function
- Open loop control and its limitations
- Dual output display management
- ADC quantization and resolution limitations
- H-bridge motor control
- Bidirectional DC motor speed control
- Dead zone implementation
- Multi-actuator control from single sensor output

## Suggested Improvements

- Use position feedback from servomotor for output display and serial monitor printout for more accurate debugging purposes.

- Use sensor-verification of initial servo position at startup rather than a basic time-delay

- use position feedback from DC motor to verify correct operation of motor and correct output

- Use a larger LCD to display all the outputs desired with their actual positions for better diagnostics in real time
## How to Run this: 

1. Wire components per pin assignments in sketch comments

 *Note: Fritzing wiring diagram to be added*

2. Upload servo_lcd_control.ino via Arduino IDE
3. Adjust contrast potentiometer until LCD display is readable 	at desired level


## Feedback/Improvements Needed

During testing, I noticed on initial uploads to the Arduino the code did not initialize correctly. Had to upload twice to have correctly functioning code. Need to investigate further whether this is an Arduino IDE problem or a USB cable issue. It is worth noting that the readout for the servo position is only showing the input command due to a lack of a feedback wire on this particular servo motor. A better solution would be to include a separate sensor to verify the actual position of the servo motor to account for any variance or fault condition. This is far more useful for debugging than simply reflecting the input command back as output. Also of importance, the potentiometers used for this demo have poor resolution near their end limits, and so there is not perfectly fine-tuned control over the output. A higher resolution potentiometer with tighter tolerances would be appropriate in a critical application. 

After adding the DC motor, I noticed that the HD44780 LCD supports custom character definitions which could allow more compact display formatting to fit additional data on screen.


