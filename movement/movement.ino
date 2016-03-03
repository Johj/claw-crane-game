#include <AFMotor.h>

// Keypad constants
#define PIN_KEYPAD A1
#define ROWS 3
#define COLS 3

// Stepper constants
#define PIN_MOTORX 2
#define PIN_MOTORY 1
#define STEPS_PER_REVOLUTION 200
#define SPEED 80
#define STEPS 80
#define STEP_TYPE DOUBLE

// Allocate
AF_Stepper motorX(STEPS_PER_REVOLUTION, PIN_MOTORX);
AF_Stepper motorY(STEPS_PER_REVOLUTION, PIN_MOTORY);

// Functions
int getRow(int v) {
  if(v < 125)
    return -1;
  else if(v < 325) //325 usb 410 batt
    return 0;
  else if(v < 510) //510 usb 620 batt
    return 1;
  else
    return 2;
}

void setup() {
  motorX.setSpeed(SPEED);
  motorY.setSpeed(SPEED);
  
  Serial.begin(9600);
}

void loop() {
  for(int col = 0; col < 3 ; ++col){
    int voltage = analogRead(col + PIN_KEYPAD);
    int row = getRow(voltage);
   /* 
    if(voltage > 125) {
      Serial.print("Col = ");
      Serial.print(col);
      Serial.print(" Voltage = ");
      Serial.print(voltage);
      Serial.print(" Row = ");
      Serial.print(row);
      Serial.println();
    }*/
    // If button is pressed and not the same as the previously pressed button.
    if(row != -1) {
      if(row == 0) { // first row - 123
        if(col == 0) { // 1 - left
           //Serial.println("Move LEFT");
           motorX.step(STEPS, BACKWARD, STEP_TYPE);
        }
        else if(col == 1) { // 2 - up
          //Serial.println("Move UP");
          motorY.step(STEPS, BACKWARD, STEP_TYPE);
        }
        else if(col == 2) { // 3 - right
          //Serial.println("Move RIGHT");
          motorX.step(STEPS, FORWARD, STEP_TYPE);
        }
      }
      else if(row == 1) { // second row - 456
        if(col == 1) { // 5 - down
          //Serial.println("Move DOWN");
          motorY.step(STEPS, FORWARD, STEP_TYPE);
        }
      }
      break;
    }
    // Release torque to prevent overheating.
    else {
      motorX.release();
      motorY.release();
    }
  }
  delay(50);
}
