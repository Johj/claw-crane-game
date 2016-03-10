#include <AFMotor.h>
#include <Servo.h>

// Keypad constants
#define PIN_KEYPAD A1

// Stepper constants
#define PIN_MOTORZ 2
#define STEPS_PER_REVOLUTION 200
#define SPEED 150
#define STEPS 150
#define STEP_TYPE DOUBLE // 2x the torque

// Servo constants
#define PIN_SERVO 10
#define MIN_PULSE 640
#define MAX_PULSE 2400
#define ANGLE_I 50
#define ANGLE_F 175

// IR Sensor Constants
#define PIN_SENSOR A4

// Allocate
AF_Stepper motorZ(STEPS_PER_REVOLUTION, PIN_MOTORZ);
Servo hitec;

// Functions
void setup() {
  motorZ.setSpeed(SPEED);
  hitec.attach(PIN_SERVO, MIN_PULSE, MAX_PULSE);
  hitec.write(ANGLE_I);
    
  // Serial.begin(9600);
}

void loop() {
  for(int col = 0; col < 3 ; ++col){
    int voltage = analogRead(col + PIN_KEYPAD);
    /*if(voltage > 125) {
      Serial.print("Col = ");
      Serial.print(col);
      Serial.print(" Voltage = ");
      Serial.print(voltage);
      Serial.print(" Row = ");
      Serial.print(row);
      Serial.println();
    }*/
    // If button is pressed and not the same as the previously pressed button.
    if(voltage > 125) {
        if(col == 0) { // 1
          // Serial.println("Move DOWN");
          while(analogRead(PIN_SENSOR) > 290) {
             // Serial.println(analogRead(PIN_SENSOR));
             motorZ.step(STEPS, BACKWARD, STEP_TYPE);
          }
          
          // hook
          hitec.write(ANGLE_F);
          delay(1000);

          // Serial.println("Move UP");
          while(analogRead(PIN_SENSOR) < 600){
             motorZ.step(STEPS, FORWARD, STEP_TYPE);
          }
        }
        else if(col == 1) { // 2
          // Serial.println("Move UP");
          motorZ.step(STEPS, FORWARD, STEP_TYPE);
        }
        else if(col == 2) { // 3
          // Serial.println("Move HOOK");
          if(hitec.read() == ANGLE_F){
            hitec.write(ANGLE_I);
          }
          else{
            hitec.write(ANGLE_F);
          }
          delay(1000);
        }
       break;
      }
      else {
        motorZ.release();
      }
    }
  delay(50);
}
