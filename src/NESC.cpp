/**************************************************************************/
/*!
    @file     NESC.cpp
    @author   Mario Avenoso (M-tech Creations)
	@author   Robin Avenoso (RAvenoso0721 (at) gmail.com)
	
	Based on the work of http://poorstudenthobbyist.blogspot.com/2013/07/how-controller-works.html
	
    @license  MIT (see license.txt)

    Library for using a standered NES or SNES contoller with a arduino

    @section  HISTORY

    v0.1.0 - First release
*/
/**************************************************************************/

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "NESC.h"



/*========================================================================*/
/*                            CONSTRUCTORS                                */
/*========================================================================*/

/**************************************************************************/
/*!
    Constructor
*/
/**************************************************************************/
NESC::NESC(void)
{
	//is_started = false;
}


/*========================================================================*/
/*                           PUBLIC FUNCTIONS                             */
/*========================================================================*/

/**************************************************************************/


/**************************************************************************/
/*!
     @brief  Initializes the library with the pins to be used on the Arduino
				and starts the library
*/
/**************************************************************************/
void NESC::begin(int latch1,int clk1,int data1)
  {
    latch = latch1;
    clk = clk1;
    data = data1;
    pinMode(latch,OUTPUT);
    pinMode(clk,OUTPUT);
    pinMode(data,INPUT);

    digitalWrite(latch,LOW);
    digitalWrite(clk,LOW);
    //is_started = true;
  }

  
/**************************************************************************/
/*!
     @brief  Query's the controller state and stores it
*/
/**************************************************************************/
void NESC::update()
{
	button_state = readController();
}

/**************************************************************************/
/*!
     @brief  Checks to see if the given button or one of a group of buttons
	 has been pressed using a button mask.
     
     @returns boolean: true if there is a pressed button, false if not 
*/
/**************************************************************************/
boolean NESC::pressed(BUFFER mask)
{
	return button_state & mask;
}

/**************************************************************************/
/*!
     @brief  Checks to see if the given button or one of a group of buttons
	 is not pressed using a button mask.
     
     @returns boolean: true if the button(s) are not pressed, false if they are 
*/
/**************************************************************************/
boolean NESC::released(BUFFER mask)
{
	return (~button_state) & mask; 
}

/**************************************************************************/
/*!
     @brief  Checks to see if the controller is in the exact state you are
	 looking for using the button masks
     
     @returns boolean: true if the state matches the mask, false if not 
*/
/**************************************************************************/
boolean NESC::exclusivePressed(BUFFER pressed, BUFFER released)
{
	BUFFER temp = button_state ^ released;
	BUFFER mask = pressed | released;
	temp = temp & mask;
	return temp == mask;
}

/**************************************************************************/
/*!
     @brief  Checks for Button press
     
     @returns boolean: true if button is pressed, false if not 
*/
/**************************************************************************/
boolean NESC::upButton()
{
	return pressed(UP_BUTTON);
}

/**************************************************************************/
/*!
     @brief  Checks for Button press
     
     @returns boolean: true if button is pressed, false if not 
*/
/**************************************************************************/
boolean NESC::downButton()
{
	return pressed(DOWN_BUTTON);
}

/**************************************************************************/
/*!
     @brief  Checks for Button press
     
     @returns boolean: true if button is pressed, false if not 
*/
/**************************************************************************/
boolean NESC::leftButton()
{
	return pressed(LEFT_BUTTON);
}

/**************************************************************************/
/*!
     @brief  Checks for Button press
     
     @returns boolean: true if button is pressed, false if not 
*/
/**************************************************************************/
boolean NESC::rightButton()
{
	return pressed(RIGHT_BUTTON);
}

/**************************************************************************/
/*!
     @brief  Checks for Button press
     
     @returns boolean: true if button is pressed, false if not 
*/
/**************************************************************************/
boolean NESC::startButton()
{
	return pressed(START_BUTTON);
}

/**************************************************************************/
/*!
     @brief  Checks for Button press
     
     @returns boolean: true if button is pressed, false if not 
*/
/**************************************************************************/
boolean NESC::selectButton()
{
	return pressed(SEL_BUTTON);
}

/**************************************************************************/
/*!
     @brief  Checks for Button press
     
     @returns boolean: true if button is pressed, false if not 
*/
/**************************************************************************/
boolean NESC::aButton()
{
	return pressed(A_BUTTON);
}

/**************************************************************************/
/*!
     @brief  Checks for Button press
     
     @returns boolean: true if button is pressed, false if not 
*/
/**************************************************************************/
boolean NESC::bButton()
{
	return pressed(B_BUTTON);
}
#if defined SNES_CONNTROLLER
/**************************************************************************/
/*!
     @brief  Checks for Button press
     
     @returns boolean: true if button is pressed, false if not 
*/
/**************************************************************************/
  bool NESC::xButton()
  {
	  return pressed(X_BUTTON);
  }
  
/**************************************************************************/
/*!
     @brief  Checks for Button press
     
     @returns boolean: true if button is pressed, false if not 
*/
/**************************************************************************/
  bool NESC::yButton()
  {
	  return pressed(Y_BUTTON);
  }
#endif

/*========================================================================*/
/*                           PRIVATE FUNCTIONS                             */
/*========================================================================*/

/**************************************************************************/

/**************************************************************************/
/*!
     @brief  Gets the current status of the controller buttons
*/
/**************************************************************************/
BUFFER NESC::readController()
  {
    BUFFER nes_buttons = 0;
    digitalWrite(latch, HIGH);
    delayMicroseconds(12);
    digitalWrite(latch, LOW);
    // The Latch has now been sent, so send clock signal and read the button states
    for(int x=0;x<sizeof(BUFFER) * 8;x++){
      digitalWrite(clk,LOW);
      delayMicroseconds(4);
      nes_buttons = nes_buttons << 1; // Shift the bits of nes_buttons to the left
      nes_buttons = nes_buttons + digitalRead(data)^1; // Add the new pin state, either a 1 or 0
      digitalWrite(clk,HIGH); // Next button state is output to the data line
      delayMicroseconds(4);
    }
    digitalWrite(clk,LOW);
    return nes_buttons;
  }