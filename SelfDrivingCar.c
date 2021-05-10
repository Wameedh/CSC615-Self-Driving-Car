/**************************************************************
* Class: CSC-615 Spring 2021
* Name: Feras Alayoub
* Student ID: 917942134
* Github ID: ARM-Cortex-M4
* Project: Assignment 3 - Start Your Motor
*
* File: assignment3.c
*
* Description: This is the main program for assignment3 Start Your
* Motor.
*
**************************************************************/

#include "assignment3.h"






// WiringPi pin# 29
int fd; //file descriptor to read, and write to the I2C int returned from
// wiringPiI2CSetup function call

int main() {
    
    printf("Starting Program\n");
    delay(5000);

  if(wiringPiSetup() == -1) { 
        printf("WiringPi setup failed\n"); // WiringPi failed Check Here
    }


    
    Motor_Stop();
    
     
    //Get the fd
    fd = wiringPiI2CSetup(0x40); //this was the I2C address of the
    //wave share board
    
    
    // write 0 to the fd
    //This step is more a PCA9685 initilization step for the registers
    //channels and modes
    writeI2C(MODE1, 0x00);
    // set the freq
    //This step sets the frequency at which the PWM wave repeats at
    //500 Hz or .002 Seconds
    PCA9685_SetPWMFreq(500);


    printf("Setting PWM\n");
    //Car_Forward();
    //delay(1000);
    //Car_Backward();
    //delay(1000);
    Car_ShiftRight();
    delay(1000);
    Car_ShiftLeft();
    delay(1000);
    Rotate_CarRight();
    delay(1000);
    Rotate_CarLeft();
    delay(1000);



    
    

    printf("End of program!\n");
    Motor_Stop();
    return 0;
}



void Car_Forward() {
    
    // Bacl Right Motor  
    PCA9685_SetPWM(0,0,1200);
      
    PCA9685_SetPWM(1,4095,0);
      
    PCA9685_SetPWM(2,0,4095);
    
    //Back Left Motor
    PCA9685_SetPWM(4,0,1200);
      
    PCA9685_SetPWM(5,0,4095);
      
    PCA9685_SetPWM(6,4095,0);
    
    //Front Right Motor
    PCA9685_SetPWM(8,0,1200);
      
    PCA9685_SetPWM(9,4095,0);
      
    PCA9685_SetPWM(10,0,4095);
    
    //Front Left Motor
    PCA9685_SetPWM(12,0,1200);
      
    PCA9685_SetPWM(13,4095,0);
      
    PCA9685_SetPWM(14,0,4095);
      
    
    
    }
    
    void Car_ShiftRight() {
    // Bacl Right Motor  
    PCA9685_SetPWM(0,0,1200);
      
    PCA9685_SetPWM(1,4095,0);
      
    PCA9685_SetPWM(2,0,4095);
    
    //Back Left Motor
    PCA9685_SetPWM(4,0,1200);
      
    PCA9685_SetPWM(5,4095,0);
      
    PCA9685_SetPWM(6,0,4095);
    
    //Front Right Motor
    PCA9685_SetPWM(8,0,1200);
      
    PCA9685_SetPWM(9,0,4095);
      
    PCA9685_SetPWM(10,4095,0);
    
    //Front Left Motor
    PCA9685_SetPWM(12,0,1200);
      
    PCA9685_SetPWM(13,4095,0);
      
    PCA9685_SetPWM(14,0,4095);
      
    
     
    
    }


    void Car_ShiftLeft() {
        
    // Bacl Right Motor  
    PCA9685_SetPWM(0,0,1200);
      
    PCA9685_SetPWM(1,0,4095);
      
    PCA9685_SetPWM(2,4095,0);
    
    //Back Left Motor
    PCA9685_SetPWM(4,0,1200);
      
    PCA9685_SetPWM(5,0,4095);
      
    PCA9685_SetPWM(6,4095,0);

    //Front Right Motor
    PCA9685_SetPWM(8,0,1200);
      
    PCA9685_SetPWM(9,4095,0);
      
    PCA9685_SetPWM(10,0,4095);
    
    //Front Left Motor
    PCA9685_SetPWM(12,0,1200);
      
    PCA9685_SetPWM(13,0,4095);
      
    PCA9685_SetPWM(14,4095,0);
      
    
     
    
    }
        
    
    void Rotate_CarLeft() {

    // Back Right Motor  
    PCA9685_SetPWM(0,0,1200);
      
    PCA9685_SetPWM(1,4095,0);
      
    PCA9685_SetPWM(2,0,4095);
    
    //Back Left Motor
    PCA9685_SetPWM(4,0,1200);
      
    PCA9685_SetPWM(5,4095,0);
      
    PCA9685_SetPWM(6,0,4095);
    
    //Front Right Motor
    PCA9685_SetPWM(8,0,1200);
      
    PCA9685_SetPWM(9,4095,0);
      
    PCA9685_SetPWM(10,0,4095);
    
    //Front Left Motor
    PCA9685_SetPWM(12,0,1200);
      
    PCA9685_SetPWM(13,0,4095);
      
    PCA9685_SetPWM(14,4095,0);
      
    
    
    }
    
    
    void Rotate_CarRight() {
        
    // Back Right Motor  
    PCA9685_SetPWM(0,0,1200);
      
    PCA9685_SetPWM(1,0,4095);
      
    PCA9685_SetPWM(2,4095,0);
    
    //Back Left Motor
    PCA9685_SetPWM(4,0,1200);
      
    PCA9685_SetPWM(5,0,4095);
      
    PCA9685_SetPWM(6,4095,0);
    
    //Front Right Motor
    PCA9685_SetPWM(8,0,1200);
      
    PCA9685_SetPWM(9,0,4095);
      
    PCA9685_SetPWM(10,4095,0);
    
    //Front Left Motor
    PCA9685_SetPWM(12,0,1200);
      
    PCA9685_SetPWM(13,4095,0);
      
    PCA9685_SetPWM(14,0,4095);
      
    
    
    }
    
    void Car_Backward() {
    // Bacl Right Motor  
    PCA9685_SetPWM(0,0,1200);
      
    PCA9685_SetPWM(1,0,4095);
      
    PCA9685_SetPWM(2,4095,0);
    
    //Back Left Motor
    PCA9685_SetPWM(4,0,1200);
      
    PCA9685_SetPWM(5,4095,0);
      
    PCA9685_SetPWM(6,0,4095);
    
    //Front Right Motor
    PCA9685_SetPWM(8,0,1200);
      
    PCA9685_SetPWM(9,0,4095);
      
    PCA9685_SetPWM(10,4095,0);
    
    //Front Left Motor
    PCA9685_SetPWM(12,0,1200);
      
    PCA9685_SetPWM(13,0,4095);
      
    PCA9685_SetPWM(14,4095,0);
      
         
    
    }

void Motor_Stop()
{
 PCA9685_SetPWM(0,0,0);
 
 PCA9685_SetPWM(4,0,0);
 
 PCA9685_SetPWM(8,0,0);
 
 PCA9685_SetPWM(12,0,0);
}

//The PCA Function below were copied below, However, I used I2C calls in
//them

/**
 * Set the PWM output.
 *
 * @param channel: 16 output channels.  //(0 ~ 15)
 * @param on: 12-bit register will hold avalue for the ON time.  //(0 ~ 4095)
 * @param off: 12-bit register will hold the value for the OFF time.  //(0 ~ 4095)
 *
 * @For more information, please see page 15 - page 19 of the datasheet.
 * Example:
 * PCA9685_SetPWM(0, 0, 4095);
 */
void PCA9685_SetPWM(char channel, int on, int off)
{
    writeI2C(LED0_ON_L + 4*channel, on & 0xFF);
    writeI2C(LED0_ON_H + 4*channel, on >> 8);
    writeI2C(LED0_OFF_L + 4*channel, off & 0xFF);
    writeI2C(LED0_OFF_H + 4*channel, off >> 8);
    //This essentially builds a PWM out of setting registers high and low
    //for specific intervals the bit pushing for this is somewhat complicated
    //but
}


/**
 * Some of the code and logic in the Below function was sourced from
 * https://www.waveshare.com/wiki/File:Motor_Driver_HAT_Code.7z
 * Set the frequency (PWM_PRESCALE) and restart.
 * 
 * For the PCA9685, Each channel output has its own 12-bit 
 * resolution (4096 steps) fixed frequency individual PWM 
 * controller that operates at a programmable frequency 
 * from a typical of 40 Hz to 1000 Hz with a duty cycle 
 * that is adjustable from 0 % to 100 % 
 * 
 * @param freq: Output frequency.  //40 ~ 1000
 *
 * Example:
 * PCA9685_SetPWMFreq(50);
 */
void PCA9685_SetPWMFreq(int freq) // this function sets the frequency of the PWM signal
{
    freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
    double prescaleval = 25000000.0;
    prescaleval /= 4096.0;
    prescaleval /= freq;
    prescaleval -= 1;
    

    char prescale = floor(prescaleval + 0.5);
    

    char oldmode = readI2C(MODE1);
    char newmode = (oldmode & 0x7F) | 0x10; // sleep
    writeI2C(MODE1, newmode);
    writeI2C(PRESCALE, prescale);
    writeI2C(MODE1, oldmode);
    delay(5);
    writeI2C(MODE1, oldmode | 0x80);  //  This sets the MODE1 register to turn on auto increment.
}


void runTheMotor(int i, int speed)
{
    if(speed > 100) { // max speed is 100
        speed = 100;
    }
        PCA9685_SetPWM(PWMA, 0, speed * (4096 / 100) - 1); //This sets the Duty cycle of the PWM to get the RMS voltage
        if(i == 1) {
            PCA9685_SetPWM(AIN1,0, 4095); // basically saying i want this to be a PWM of duty cycle 100% so always on
            PCA9685_SetPWM(AIN2,0, 0); // setting the polarity forward
        } else {
            PCA9685_SetPWM(AIN1,0, 0); //setting the polarity of motor in reverse
            PCA9685_SetPWM(AIN2,0, 4095);
        }
}

void writeI2C(char reg, char value){
    if(wiringPiI2CWriteReg8(fd, reg, value) != 0){
            // Test to check for failure
            //printf("wiringPiI2CWriteReg8() has failed!\n");
        }
        //made a wrapper function to to check for issues regarding writes
        //this should return an acknowledge bit the the destination was written to
}

char readI2C(char reg){
    return  wiringPiI2CReadReg8(fd, reg);
    //Read the reg from the chosen I2C address file
    //did not know how to check this for error.
}

