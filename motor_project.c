#include <wiringPi.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include <signal.h>
#include <softPwm.h>


//////// DEFINES //////////

#define CONTROL_PIN_1 25
#define CONTROL_PIN_2 24
#define ON_OFF_CONTROL_PIN 23
#define DIRECTION_SWITCH_PIN 22
#define ON_OFF_BUTTON_PIN 21



//////// VARIABLES //////////

// 0 = OFF, 1 = ON
volatile int motorEnabled = 0;

// 0 = ONE WAY, 1 = THE OTHER WAY
volatile int motorDirection = 1;


///////// FUNCTIONS //////////

void turnOnOffMotor() {
  printf("On / Off clicked");
  motorEnabled = !motorEnabled;
}

void switchMotorDirection() {
  printf("Direction Changed");
  motorDirection = !motorDirection;  
}

//void intHandler(int sig) {
//  exit(0);
//}


///////// MAIN //////////

int main (void) {

  wiringPiSetup();

  // Declaring Pin Modes
  pinMode (DIRECTION_SWITCH_PIN, INPUT);
  pinMode (ON_OFF_BUTTON_PIN, INPUT);
  pinMode (CONTROL_PIN_1, OUTPUT);
  pinMode (CONTROL_PIN_2, OUTPUT);
  pinMode (ON_OFF_CONTROL_PIN, OUTPUT);

  // Set up ON_OFF_CONTROL_PIN as a software pwm-able pin
  softPwmCreate(ON_OFF_CONTROL_PIN,0,100);


  // Setting up turning on and off DC motor function as interrupt 
  wiringPiISR (ON_OFF_BUTTON_PIN, INT_EDGE_RISING, &turnOnOffMotor);

  // Setting up switching direction of DC motor function as interrupt
  wiringPiISR (DIRECTION_SWITCH_PIN, INT_EDGE_RISING, &switchMotorDirection);

  // Setting up a singal handler (for CNTRL-C'ing the program)
  //signal(SIGINT, intHandler);

  while (1) {

    // Changing direction
    if (motorDirection == 1) {
    
      // Change control pins on h-bridge to turn motor "wise"
      digitalWrite(CONTROL_PIN_1, HIGH);
      digitalWrite(CONTROL_PIN_2, LOW);
      printf("Motor turning in direction A\n"); delay(500);

    } else if (motorDirection == 0) {
      
      // Change control pins on h-bridge to turn motor "wise"
      digitalWrite(CONTROL_PIN_1, LOW);
      digitalWrite(CONTROL_PIN_2, HIGH);
      printf("Motor turning in direction B\n"); delay(500);
    }

    // Turning motor on & off
    if (motorEnabled == 1) {
      
      // turn on motor w/ ON_OFF_CONTROL_PIN
      softPwmWrite(ON_OFF_CONTROL_PIN,100);
      //digitalWrite(ON_OFF_CONTROL_PIN, HIGH);
      printf("Motor should be running\n"); delay(500);
    
    } else if (motorEnabled == 0) {
    
      // turn off motor w/ ON_OFF_CONTROL_PIN
      softPwmWrite(ON_OFF_CONTROL_PIN,0);
      //digitalWrite(ON_OFF_CONTROL_PIN, LOW);
      printf("Motor should be off\n"); delay(500);
    
    }
  }
}