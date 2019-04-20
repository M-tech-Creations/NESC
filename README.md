#NESC Library #

Arduino library for interfacing with an NES or SNES controller.

## About this Library ##
This is Used for getting button states from with a NES or SNES contoller.


First create a NESC object and in the setup loop call the begin function passing it the arduino pins
that will be used for Latch, Clock and Data.

When checking for button presses first call the update function on the NESC object. After calling update
the current status of the controller buttons are stored and can then be checked using a few different functions.

There are function calls each button (aButton, startButton etc.) or you can use the pressed function. To use pressed,
you pass it the Button or combination of buttons you are checking to have been pressed using the set constants.
If you want to check if the A Button is pressed you pass A_BUTTON to pressed and it will return true or false for if
its pressed. To check if there are more than one button preeses and dont care which, you can pass A_BUTTON | B_BUTTON.
By using the logical or you are able to check is either A or B is presses in this instance.


 On the NES Controller, Pin 1 is Ground, 2 is Clock, 3 is Latch, 4 is Data out and 5 is +5v
   ____
  / 0 1|  
  | 5 2|  
  | 6 3|  
  | 7 4|  
  ------  

This is still a work in progress and as of this point the SNES parts of this library have not been fully developed 

Written by Mario Avenoso of mtechcreations.com
and Robin Avenso (https://github.com/LittlePinkRobin)
MIT license, check license.txt for more information


