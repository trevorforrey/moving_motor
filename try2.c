#include <wiringPi.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

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
  //interruptTime = millis();
  //if (interruptTime - lastInterruptTime < 100) {
    motorEnabled = !motorEnabled;
  //}
  //lastInterruptTime = interruptTime;
  //printf("enable finish\n");
}

void switchMotorDirection() {
  //interruptTime = millis();
  //if (interruptTime - lastInterruptTime < 100) {
    motorDirection = !motorDirection;
  //}
  //lastInterruptTime = interruptTime; 
  //printf("direction finish\n");
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


  //while (1) {

    //printf("OFF\n");
    //digitalWrite(ENABLE_PIN, LOW);
    //digitalWrite(CONTROL_PIN_1, HIGH);
    //digitalWrite(CONTROL_PIN_2, LOW);
    //delay(1000);

    
    //printf("STILL OFF\n");
    //digitalWrite(ENABLE_PIN, LOW);
    //digitalWrite(CONTROL_PIN_1, LOW);
    //digitalWrite(CONTROL_PIN_2, HIGH);
    //delay(1000);

    //printf("ON\n");
    //digitalWrite(ENABLE_PIN, HIGH);
    //digitalWrite(CONTROL_PIN_1, HIGH);
    //digitalWrite(CONTROL_PIN_2, LOW);
    //delay(1000);
    

    //digitalWrite(ENABLE_PIN, LOW);
    //delay(1000);
    
    //printf("STILL ON\n");
    //digitalWrite(ENABLE_PIN, HIGH);
    //digitalWrite(CONTROL_PIN_1, LOW);
    //digitalWrite(CONTROL_PIN_2, HIGH);
    //delay(1000);
  
  //}


  while (1) {
    
    if (motorEnabled == 0) {
      // turn off motor
      printf("OFF\n"); delay (1000);
      digitalWrite(ENABLE_PIN, LOW);
    } else if (motorEnabled == 1) {
      // turn on motor
      printf("ON\n"); delay (1000);
      digitalWrite(ENABLE_PIN, HIGH);
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