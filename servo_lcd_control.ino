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

}

void loop() { //This code runs continuously after startup

// Declare the datatype being read first = in this case 'integer', stored as 16-bit integer
// Assign the analog voltage readout from pin A0 to variable name 'value'
  int value = analogRead(A0);

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


