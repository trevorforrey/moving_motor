#include <wiringPi.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include <signal.h>
#include <softPwm.h>


//////// DEFINES //////////

#define ON_BUTTON 21
#define CHANGE_LED_BUTTON 22
#define ON_LED 27
#define BLUE_LED 28
#define GREEN_LED 29


//////// VARIABLES //////////

// 0 = OFF, 1 = ON
volatile int LEDsEnabled = 0;

// 0 = ONE WAY, 1 = THE OTHER WAY
volatile int LEDDeterminator = 1;


///////// FUNCTIONS //////////

void turnOffLEDs() {
  printf("On / Off clicked");
  LEDsEnabled = !LEDsEnabled;
}

void changeLED() {
  printf("LED Changed");
  LEDDeterminator = !LEDDeterminator;  
}


///////// MAIN //////////

int main (void) {

  if(wiringPiSetup() == -1){
    printf("setup wiringPi failed !");
    return 1; 
  }

  // Declaring Pin Modes
  pinMode (ON_BUTTON, INPUT);
  pinMode (CHANGE_LED_BUTTON, INPUT);
  pinMode (ON_LED, OUTPUT);
  pinMode (BLUE_LED, OUTPUT);
  pinMode (GREEN_LED, OUTPUT);

  // Setting up turning on and off DC motor function as interrupt 
  wiringPiISR (ON_BUTTON, INT_EDGE_RISING, &turnOffLEDs);

  // Setting up switching direction of DC motor function as interrupt
  wiringPiISR (CHANGE_LED_BUTTON, INT_EDGE_RISING, &changeLED;

  while (1) {

    // Changing LED
    if (LEDDeterminator == 1) {
    
      digitalWrite(GREEN_LED, HIGH);
      printf("Green LED on\n"); delay(500);

    } else if (LEDDeterminator == 0) {
      
      digitalWrite(BLUE_LED, HIGH);
      printf("Blue LED on\n"); delay(500);
    }

    // Turning LEDs on/off
    if (LEDsEnabled == 1) {
      
      digitalWrite(ON_LED, HIGH);
      printf("LED ON\n"); delay(500);
    
    } else if (LEDsEnabled == 0) {
    
      digitalWrite(ON_LED, LOW);
      printf("OFFFFFFFFFF\n"); delay(500);
    
    }
  }
}