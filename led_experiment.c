#include <wiringPi.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include <signal.h>
#include <softPwm.h>


//////// DEFINES //////////

#define ON_BUTTON 4
#define CHANGE_LED_BUTTON 5
#define ON_LED 0
#define BLUE_LED 2
#define GREEN_LED 3


//////// VARIABLES //////////

// 0 = OFF, 1 = ON
volatile int LEDsEnabled = 0;

// 0 = ONE WAY, 1 = THE OTHER WAY
volatile int LEDDeterminator = 1;


///////// FUNCTIONS //////////

void turnOffLEDs() {  
  LEDsEnabled = !LEDsEnabled;
  printf("On / Off clicked");
}

void changeLED() {
  LEDDeterminator = !LEDDeterminator;  
  printf("LED Changed");
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

  digitalWrite (ON_LED, LOW);
  digitalWrite (BLUE_LED, LOW);
  digitalWrite (GREEN_LED, LOW);

  // Setting up turning on and off DC motor function as interrupt 
  wiringPiISR (ON_BUTTON, INT_EDGE_FALLING, &turnOffLEDs);

  // Setting up switching direction of DC motor function as interrupt
  wiringPiISR (CHANGE_LED_BUTTON, INT_EDGE_FALLING, &changeLED);

  while (1) {

    // Changing LED
    if (LEDDeterminator == 1) {
    
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(BLUE_LED, LOW);

    } else if (LEDDeterminator == 0) {
      
      digitalWrite(BLUE_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
    }

    // Turning LEDs on/off
    if (LEDsEnabled == 1) {
      
      digitalWrite(ON_LED, HIGH);
    
    } else if (LEDsEnabled == 0) {
    
      digitalWrite(ON_LED, LOW);
    }
  }
}