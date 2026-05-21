// Pull servo library into program
#include <Servo.h> 

//Pull LCD library into program
#include <LiquidCrystal.h>

// Assign pinout for LCD display
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Create the servo motor as a global object, has to be before the setup portion
Servo servo1;

// establish servo timer
unsigned long lastservoupdate = 0;

// establish print timer
unsigned long lastprintupdate = 0;

//establish dc motor timer
unsigned long lastmotorupdate = 0;

void setup() {// This code runs one time at startup and never again

  // Initializes the usb serial data connection @ 9600 bits per second
  Serial.begin(9600);

  //Initialize LCD display with correct sizing identifier
  lcd.begin(16, 2);

  // Establish Pin 9 as the PWM for the servo motor control
  servo1.attach(9);

  // Send command to servo motor to start at 0
  servo1.write(0);

  // Allow for a 1 second delay for the servo to reach its starting position
  delay(1000);

  // establish pin modes for dc motor control
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

}

void loop() { //This code runs continuously after startup

// Declare the datatype being read first = in this case 'integer', stored as 16-bit integer
// Assign the analog voltage readout from pin A0 to variable name 'value'
  int value = analogRead(A0);

  //Overarching Conditional for DC motor command every 150ms
  if (millis() - lastmotorupdate >=150 ) {

    //Set reverse zone conditions
    if (value < 489)  {

    //Set Motor Output pins to opposite signals 
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);

    //define speed value from raw analog output
    int speed = map(value,489,0,0,255);
    analogWrite(11, speed);

    //update motor control timer
    lastmotorupdate = millis();
    }

    //set deadband zone with no speed
    else if (value>=489 && value<=534) {

      // set motor output pins to low
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);

       // set speed value to zero
      int speed = value-value;
      analogWrite(11, speed);

      //update motor control timer
      lastmotorupdate = millis();
    }

    //set forward speed zone 
    else {

      //set motor output pins to opposite reverse
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);

      //Set forward speed
      int speed = map(value,534,1023,0,255);

      //Apply PWM output
      analogWrite(11, speed);

      //update motor control timer
    lastmotorupdate = millis();
    }
  }

  //Correlate analogreadout from A0 to angle using map() function
  int inputangle = map(value,0,1023,0,180);
  

// establish conditional for servo command every 100ms
if (millis() - lastservoupdate >= 20 ) {

  //Send command to servo motor
  servo1.write(inputangle);

  //establish updated servo update timer
  lastservoupdate = millis();
}

// establish 500ms interval for serial printout
if (millis() - lastprintupdate >= 500) {

  // Print Commanded Servo Angle and analog readout to Monitor for debugging
  Serial.print("Analog Readout: ");
  Serial.print(value);
  Serial.print(" | Commanded Angle: ");
  Serial.println(inputangle);

  // Command to relay info on LCD screen

  //Clear the LCD each loop
  lcd.clear();

  //Set cursor position BEFORE writing to LCD
  lcd.setCursor(0,0); //Top row cursor set
  lcd.print("Level: ");
  lcd.print(value);

 //Set cursor position BEFORE writing to LCD
  lcd.setCursor(0,1); //Bottom Row cursor set
  lcd.print("Servo Angle: ");
  lcd.print(inputangle);

  // establish new print timer update
  lastprintupdate = millis();
}
}


