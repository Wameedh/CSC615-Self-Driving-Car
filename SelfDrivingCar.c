/**************************************************************
* Class: CSC-615-01 Spring 2021
* Group Name: Cesla Pirates
* Group Members:
*               Feras Alayoub (Manager), ID: 917942134, Github ID: ARM-Cortex-M4
*               Wameedh Mohammed Ali, ID: 920678405, Github ID: wameedh
*               Wilfredo Aceytuno Jolon, ID: 
*               Rasul Imanov, ID:
* Project: Final Group Project
*
* File: SelfDrivingCar.c
*
* Description: This is the main program for the final group project Self Driving Car.
*
**************************************************************/

#include "SelfDrivingCar.h"

// WiringPi pin# 29
int fd; //file descriptor to read, and write to the I2C int returned from
// wiringPiI2CSetup function call

int main()
{
    pthread_t left_ls_thread_id, right_ls_thread_id; // threads ids
    int error0, error1; // used to check if threads won't create
   
    
    printf("Starting Program\n");
    delay(5000);

    setup();  // setup the wiringPi using GPIO pin numbers & set the pins mode.
    
    // wiringPiSetup moved into setup() method 
    // if (wiringPiSetup() == -1)
    // {
    //     printf("WiringPi setup failed\n"); // WiringPi failed Check Here
    // }
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

    // creating thread that would be scanning for obstacles 
    error0 = pthread_create(&left_ls_thread_id, NULL, sensingTheLeftLine, NULL);
    // creating thread that would be sensing for the line 
    error1 = pthread_create(&right_ls_thread_id, NULL, sensingTheRightLine, NULL);

    if (error0 || error1) {
         printf("Error: unable to create thread/s \n");
         exit(-1);
      }

    // Program is on and sensing the line
    while (1){ 

        // Not sure if I need to add an else statment that would call Car_Forward() if the sensors are not on the line
        // Need to test this logic to see if it does wokr or not
        if(leftLineSensing == 1){
            // Need to be tested, check the condution might need to be changed to "leftLineSensing == 0"
            printf("left sensor On the  line... turn left!\n");
            Rotate_CarLeft();
           // the sensor on the left side of the line is on the line
           // Car must turn left until the sensor if off the line
        }
        if(rightLineSensing == 1){
            // Need to be tested, check the condution might need to be changed to "rightLineSensing == 0"
            printf("right sensor On the line... turn right!\n");
            Rotate_CarRight();
           // the sensor on the right side of the line is on the line
           // Car must turn right until the sensor if off the line
        }
    }
    
    pthread_cancel(left_ls_thread_id); // This should be at the end of the program
    pthread_cancel(right_ls_thread_id); // This should be at the end of the program

    // printf("Setting PWM\n");
    //Car_Forward();
    //delay(1000);
    //Car_Backward();
    //delay(1000);
    // Car_ShiftRight();
    // delay(1000);
    // Car_ShiftLeft();
    // delay(1000);
    // Rotate_CarRight();
    // delay(1000);
    // Rotate_CarLeft();
    // delay(1000);

    printf("End of program!\n");
    Motor_Stop();
    return 0;
}

void Car_Forward()
{

    // Bacl Right Motor
    PCA9685_SetPWM(0, 0, 1200);

    PCA9685_SetPWM(1, 4095, 0);

    PCA9685_SetPWM(2, 0, 4095);

    //Back Left Motor
    PCA9685_SetPWM(4, 0, 1200);

    PCA9685_SetPWM(5, 0, 4095);

    PCA9685_SetPWM(6, 4095, 0);

    //Front Right Motor
    PCA9685_SetPWM(8, 0, 1200);

    PCA9685_SetPWM(9, 4095, 0);

    PCA9685_SetPWM(10, 0, 4095);

    //Front Left Motor
    PCA9685_SetPWM(12, 0, 1200);

    PCA9685_SetPWM(13, 4095, 0);

    PCA9685_SetPWM(14, 0, 4095);
}

void Car_ShiftRight()
{
    // Bacl Right Motor
    PCA9685_SetPWM(0, 0, 1200);

    PCA9685_SetPWM(1, 4095, 0);

    PCA9685_SetPWM(2, 0, 4095);

    //Back Left Motor
    PCA9685_SetPWM(4, 0, 1200);

    PCA9685_SetPWM(5, 4095, 0);

    PCA9685_SetPWM(6, 0, 4095);

    //Front Right Motor
    PCA9685_SetPWM(8, 0, 1200);

    PCA9685_SetPWM(9, 0, 4095);

    PCA9685_SetPWM(10, 4095, 0);

    //Front Left Motor
    PCA9685_SetPWM(12, 0, 1200);

    PCA9685_SetPWM(13, 4095, 0);

    PCA9685_SetPWM(14, 0, 4095);
}

void Car_ShiftLeft()
{

    // Bacl Right Motor
    PCA9685_SetPWM(0, 0, 1200);

    PCA9685_SetPWM(1, 0, 4095);

    PCA9685_SetPWM(2, 4095, 0);

    //Back Left Motor
    PCA9685_SetPWM(4, 0, 1200);

    PCA9685_SetPWM(5, 0, 4095);

    PCA9685_SetPWM(6, 4095, 0);

    //Front Right Motor
    PCA9685_SetPWM(8, 0, 1200);

    PCA9685_SetPWM(9, 4095, 0);

    PCA9685_SetPWM(10, 0, 4095);

    //Front Left Motor
    PCA9685_SetPWM(12, 0, 1200);

    PCA9685_SetPWM(13, 0, 4095);

    PCA9685_SetPWM(14, 4095, 0);
}

void Rotate_CarLeft()
{

    // Back Right Motor
    PCA9685_SetPWM(0, 0, 1200);

    PCA9685_SetPWM(1, 4095, 0);

    PCA9685_SetPWM(2, 0, 4095);

    //Back Left Motor
    PCA9685_SetPWM(4, 0, 1200);

    PCA9685_SetPWM(5, 4095, 0);

    PCA9685_SetPWM(6, 0, 4095);

    //Front Right Motor
    PCA9685_SetPWM(8, 0, 1200);

    PCA9685_SetPWM(9, 4095, 0);

    PCA9685_SetPWM(10, 0, 4095);

    //Front Left Motor
    PCA9685_SetPWM(12, 0, 1200);

    PCA9685_SetPWM(13, 0, 4095);

    PCA9685_SetPWM(14, 4095, 0);
}

void Rotate_CarRight()
{

    // Back Right Motor
    PCA9685_SetPWM(0, 0, 1200);

    PCA9685_SetPWM(1, 0, 4095);

    PCA9685_SetPWM(2, 4095, 0);

    //Back Left Motor
    PCA9685_SetPWM(4, 0, 1200);

    PCA9685_SetPWM(5, 0, 4095);

    PCA9685_SetPWM(6, 4095, 0);

    //Front Right Motor
    PCA9685_SetPWM(8, 0, 1200);

    PCA9685_SetPWM(9, 0, 4095);

    PCA9685_SetPWM(10, 4095, 0);

    //Front Left Motor
    PCA9685_SetPWM(12, 0, 1200);

    PCA9685_SetPWM(13, 4095, 0);

    PCA9685_SetPWM(14, 0, 4095);
}

void Car_Backward()
{
    // Bacl Right Motor
    PCA9685_SetPWM(0, 0, 1200);

    PCA9685_SetPWM(1, 0, 4095);

    PCA9685_SetPWM(2, 4095, 0);

    //Back Left Motor
    PCA9685_SetPWM(4, 0, 1200);

    PCA9685_SetPWM(5, 4095, 0);

    PCA9685_SetPWM(6, 0, 4095);

    //Front Right Motor
    PCA9685_SetPWM(8, 0, 1200);

    PCA9685_SetPWM(9, 0, 4095);

    PCA9685_SetPWM(10, 4095, 0);

    //Front Left Motor
    PCA9685_SetPWM(12, 0, 1200);

    PCA9685_SetPWM(13, 0, 4095);

    PCA9685_SetPWM(14, 4095, 0);
}

void Motor_Stop()
{
    PCA9685_SetPWM(0, 0, 0);

    PCA9685_SetPWM(4, 0, 0);

    PCA9685_SetPWM(8, 0, 0);

    PCA9685_SetPWM(12, 0, 0);
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
    writeI2C(LED0_ON_L + 4 * channel, on & 0xFF);
    writeI2C(LED0_ON_H + 4 * channel, on >> 8);
    writeI2C(LED0_OFF_L + 4 * channel, off & 0xFF);
    writeI2C(LED0_OFF_H + 4 * channel, off >> 8);
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
    freq *= 0.9; // Correct for overshoot in the frequency setting (see issue #11).
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
    writeI2C(MODE1, oldmode | 0x80); //  This sets the MODE1 register to turn on auto increment.
}

void runTheMotor(int i, int speed)
{
    if (speed > 100)
    { // max speed is 100
        speed = 100;
    }
    PCA9685_SetPWM(PWMA, 0, speed * (4096 / 100) - 1); //This sets the Duty cycle of the PWM to get the RMS voltage
    if (i == 1)
    {
        PCA9685_SetPWM(AIN1, 0, 4095); // basically saying i want this to be a PWM of duty cycle 100% so always on
        PCA9685_SetPWM(AIN2, 0, 0);    // setting the polarity forward
    }
    else
    {
        PCA9685_SetPWM(AIN1, 0, 0); //setting the polarity of motor in reverse
        PCA9685_SetPWM(AIN2, 0, 4095);
    }
}

void writeI2C(char reg, char value)
{
    if (wiringPiI2CWriteReg8(fd, reg, value) != 0)
    {
        // Test to check for failure
        //printf("wiringPiI2CWriteReg8() has failed!\n");
    }
    //made a wrapper function to to check for issues regarding writes
    //this should return an acknowledge bit the the destination was written to
}

char readI2C(char reg)
{
    return wiringPiI2CReadReg8(fd, reg);
    //Read the reg from the chosen I2C address file
    //did not know how to check this for error.
}


void setup() {
        // wiringPiSetupGpio();  // Initializes wiringPi using the Broadcom GPIO pin numbers
        if(wiringPiSetupGpio() == -1) { 
            printf("WiringPi setup failed\n"); // WiringPi failed Check Here
            exit(0);
        }
        pinMode(LEFT_LINE_SENSOR_PIN, INPUT);
        pinMode(RIGHT_LINE_SENSOR_PIN, INPUT);
        
        //TRIG pin must start LOW
        digitalWrite(LEFT_LINE_SENSOR_PIN, LOW);
        digitalWrite(RIGHT_LINE_SENSOR_PIN, LOW);
        delay(30); // If we don't pause after setting it to low, sometimes the sensor doesn't work right. Source - online search!
}
 
/**********************************************/
/* Start of Left and right line sensors setup */
/**********************************************/
void *sensingTheLeftLine() {
    // keep reading the line sensor difital pin
    while (1) {
        if(digitalRead(LEFT_LINE_SENSOR_PIN) == HIGH)
        {
            // if high, means the sensor is reading the black line
            leftLineSensing = 1;

        }
        if(digitalRead(LEFT_LINE_SENSOR_PIN) == LOW)
        {
            // if low, means the sensor is can not reading the black line or off the line
            leftLineSensing = 0;
        }
    }
}


void *sensingTheRightLine() {
    // keep reading the line sensor difital pin
    while (1) {
        if(digitalRead(RIGHT_LINE_SENSOR_PIN) == HIGH)
        {
            // if high, means the sensor is reading the black line
            rightLineSensing = 1;

        }
        if(digitalRead(RIGHT_LINE_SENSOR_PIN) == LOW)
        {
            // if low, means the sensor is can not reading the black line or off the line
            rightLineSensing = 0;
        }
    }
/********************************************/
/* End of Left and right line sensors setup */
/********************************************/

}