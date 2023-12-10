#include <avr/interrupt.h>
#include <avr/sleep.h>

/*
 * File: OrnamentCode.ino
 * Lukas Severinghaus, PrincipIoT LLC
 * Dec 10, 2023
 * Rev 1
 * Software for the PrincipIoT PCB Christmas Tree Ornament.  
*/

#define TIMER_PERIOD 60*60*1000
volatile bool timer_enabled = false;
volatile long timer_end = 0;

ISR(PCINT0_vect){
  if((PINB >> 2) & 1){
    // Timer not enabled
    timer_enabled = false;
  }else{
    // Timer enabled
    timer_enabled = true;
    timer_end = millis() + TIMER_PERIOD;
  }
}

void setup() {
  DDRB = 0b00011000; // Set 4,3 to out, 2 to input
  PORTB |= 0b00000100; // Pullup on pin 2

  // Disable ADC and set pin change interrupt
  ADCSRA = 0;
  GIMSK = 0b00100000; 
  PCMSK = 0b00000100;  
  if(!((PINB >> 2) & 1)){
    timer_enabled = true;
    timer_end = millis() + TIMER_PERIOD;
  }
}


#define MAX 1000
int red_index = (int) MAX/3;
int red_direction = 1;
int green_index = 0;
int green_direction = 1;

void loop() { 
  increment_green();
  increment_red();
  if(timer_enabled && millis() > timer_end){
    timer_enabled = false;
    go_to_sleep();
  }
}

void go_to_sleep(){
  digitalWrite(3, 0);
  digitalWrite(4, 0);
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_cpu(); 
  return;
  
  MCUCR |= 00110000; // Set SE bit and set mode to power down
  sleep_cpu(); // Execute sleep command
  MCUCR ^= 00100000; // Clear SE bit, after exiting sleep
}

void increment_green(){
  if(green_index == MAX){
    green_direction = -1;
  }else if(green_index == 0){
    green_direction = 1;
  }
  PORTB |= 1<<3;
  delayMicroseconds(green_index);
  PORTB &= ~(1<<3);
  delayMicroseconds(MAX-green_index);
  green_index += green_direction;  
}

void increment_red(){
  if(red_index == MAX){
    red_direction = -1;
  }else if(red_index == 0){
    red_direction = 1;
  }
  PORTB |= 1<<4;
  delayMicroseconds(red_index);
  PORTB &= ~(1<<4);
  delayMicroseconds(MAX-red_index);
  red_index += red_direction;
}