/**************************************************************
* Class: CSC-615-01 Spring 2021
* Group Name: Cesla Pirates
* Group Members:
*               Feras Alayoub (Manager), ID: 917942134, Github ID: ARM-Cortex-M4
*               Wameedh Mohammed Ali, ID: 920678405, Github ID: wameedh
*               Rasul Imanov, ID: 920668590, Github ID: rimanov
*               Wilfredo Aceytuno Jolon - Droped off from class!
* Project: Final Group Project
*
* File: SelfDrivingCar.h
*
* Description: This file is the header file for SelfDrivingCar.c
**************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <math.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>


#define HIGH    1
#define LOW     0

#define MODE1   0x00

//GPIO config
#define PWMA       0 //These are the channels 
#define AIN1       1
#define AIN2       2

//GPIO config
// Pin number declarations. We're using the Broadcom chip pin numbers.
// out pin of the IR Obstacle Sensor
#define LEFT_LINE_SENSOR_PIN               28           // Physical pin 38
#define RIGHT_LINE_SENSOR_PIN              29           // Physical pin 40
#define ECHO							   27      		//Physical pin 36
#define TRIG							   25			//Physical pin 37
#define IR_OBSTACLE						   24 			//physical pin 35				   

// Speed of sound at sea level
const double speedOfSoundMetersPerSecond = 340.29;
//Time for echo location sensor
static volatile long startTime;
static volatile long travelTime;
static volatile int maneuver = 1;
//IR obstacle
// 1 if there is no obstacle on the way.
static volatile int obstacleOn = 1;


// 1 if there is no obstacle on the way.
static volatile int leftLineSensing = 1; 
// 1 if the senser is on the line.
static volatile int rightLineSensing = 1;

#define LED0_ON_L           0x06
#define LED0_ON_H           0x07
#define LED0_OFF_L          0x08
#define LED0_OFF_H          0x09
// I obtained these from the PCA9685 library as these where the preset
//register values that controlled the High or Low values to make the PWM.
 

#define PRESCALE    0xFE
//This was used in the frequency PCA9685


//function declarations used in this assignment
void Car_Forward();
void Car_Backward();
void Rotate_CarRight();
void Rotate_CarLeft();
void Car_ShiftRight();
void Car_ShiftLeft();
void Motor_Stop();
void PCA9685_SetPWM(char channel, int on, int off);
void PCA9685_SetPWMFreq(int freq);
void runTheMotor(int i, int speed);
void writeI2C(char reg, char value);
char readI2C(char reg);

//Use these for the echo sound location sensor.
void *recordPulse();
bool isObstacleClose();



void *sensingTheLeftLine(); // function that will be running on the left line senser thread.
void *sensingTheRightLine(); // function that will be running on the right line senser thread.
void setup();  // function that will be called at the beginning of the program to initialize the WiringPi & its pins.


void *scanForObstacles();
void maneuverObstacle();
void *trigger();
