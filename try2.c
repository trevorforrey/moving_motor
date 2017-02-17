#include <wiringPi.h>
#include <stdio.h>
#include <signal.h>
#include <softPwm.h>

//////// DEFINES //////////

#define ENABLE_BUTTON 4
#define DIRECTION_BUTTON 5
#define ENABLE_PIN 2
#define CONTROL_PIN_1 0
#define CONTROL_PIN_2 1


//////// VARIABLES //////////

// 0 = OFF, 1 = ON
volatile int motorEnabled = 0;

// 0 = ONE WAY, 1 = THE OTHER WAY
volatile int motorDirection = 0;

volatile unsigned long lastInterruptTime;
volatile unsigned long interruptTime;

///////// FUNCTIONS //////////

void turnOnOffMotor() {
  motorEnabled = !motorEnabled;
}

void switchMotorDirection() {
  motorDirection = !motorDirection;
}


///////// MAIN //////////

int main (void) {

  wiringPiSetup();

  // Declaring Pin Modes
  pinMode (ENABLE_BUTTON, INPUT);
  pinMode (DIRECTION_BUTTON, INPUT);
  pinMode (ENABLE_PIN, OUTPUT);
  pinMode (CONTROL_PIN_1, OUTPUT);
  pinMode (CONTROL_PIN_2, OUTPUT);

  digitalWrite(ENABLE_PIN, LOW);
  digitalWrite(CONTROL_PIN_1, LOW);
  digitalWrite(CONTROL_PIN_2, LOW);

  // Setting up turning on and off DC motor function as interrupt 
  wiringPiISR (ENABLE_BUTTON, INT_EDGE_FALLING, &turnOnOffMotor);

  // Setting up switching direction of DC motor function as interrupt
  wiringPiISR (DIRECTION_BUTTON, INT_EDGE_FALLING, &switchMotorDirection);

  // Set up ENABLE_PIN as a software pwm-able pin
  softPwmCreate(ENABLE_PIN,0,100);


  while (1) {
    
    if (motorEnabled == 0) {

      // turn off motor
      printf("OFF\n"); delay (1000);

      softPwmWrite(ENABLE_PIN,0);

    } else if (motorEnabled == 1) {

      // turn on motor
      printf("ON\n"); delay (1000);

      softPwmWrite(ENABLE_PIN, 60);

    }
    
    if (motorDirection == 0) {

      // turn direction A
      printf("A\n"); delay (1000);

      digitalWrite(CONTROL_PIN_1, HIGH);
      digitalWrite(CONTROL_PIN_2, LOW);

    } else if (motorDirection == 1) {

      // turn direction B
      printf("BBBBBBB\n"); delay (1000);

      digitalWrite(CONTROL_PIN_1, LOW);
      digitalWrite(CONTROL_PIN_2, HIGH);
    }
    
  }
}