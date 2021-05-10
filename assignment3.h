/**************************************************************
* Class: CSC-615 
* Name: Feras Alayoub
* Student ID: 917942134
* Github ID: ARM-Cortex-M4
* Project: Assignment 3 - Start your motors
*
* File: assignment3.h
*
* Description: This file is the header file for assigment3.c
**************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <math.h>
#include <stdint.h>

#define HIGH    1
#define LOW     0

#define MODE1   0x00

//GPIO config
#define PWMA       0 //These are the channels 
#define AIN1       1
#define AIN2       2

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
