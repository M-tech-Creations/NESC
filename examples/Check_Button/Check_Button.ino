#define NES_CONTROLLER //This is used to tell the Library which controller you are using
                       //If you do not define a contoller, the NES controller is used by default
// The define statment needs to come before the Library inculde to setup the library for the controller
#include <NESC.h>

/*
 * Example code for checking Buttons with the NESC Libary 4/20/18
 */




NESC controller1; //Create the NESC object to be used in the rest of the program

void setup()
{
  Serial.begin(9600);
  
  int Latch = 6; //Define the pins used for Latch, Clock and Data
  int Clock = 7;
  int Data  = 8;

  controller1.begin(Latch,Clock,Data); //Start the Controller
}

void loop()
{
  controller1.update(); //Update the state of the controller
  Serial.println(controller1.pressed(START_BUTTON | SEL_BUTTON)); // Output a 1 if either Start 
                                                                  // or Select is pressed

  delay(10); //Give a slight delay beween reading the controller
}
