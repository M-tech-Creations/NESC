/**************************************************************************/
/*!
    @file     NESC.h
    @author   Mario Avenoso (M-tech Creations)
    @author   Robin Avenoso (RAvenoso0721 (at) gmail.com)
	
	Based on the work of http://poorstudenthobbyist.blogspot.com/2013/07/how-controller-works.html
	
	@section LICENSE

    The MIT License (MIT)

	Copyright (c) 2019 Mario Avenoso (M-tech Creations) and Robin Avenoso

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.

*/
/**************************************************************************/

#ifndef _NESC_h_
#define _NESC_h_

#if defined NES_CONTROLLER
	#define A_BUTTON  B10000000
	#define B_BUTTON  B01000000
	#define SEL_BUTTON  B00100000
	#define START_BUTTON  B00010000
	#define UP_BUTTON  B00001000
	#define DOWN_BUTTON  B00000100
	#define LEFT_BUTTON  B00000010
	#define RIGHT_BUTTON  B00000001
	#define BUFFER  uint8_t
#elif defined SNES_CONTROLLER
	#define A_BUTTON  0x8000 
	#define B_BUTTON  0x4000
	//#define X_BUTTON 
	//#define Y_BUTTON 
	#define SEL_BUTTON  0x2000
	#define START_BUTTON  0x1000
	#define UP_BUTTON  0x800
	#define DOWN_BUTTON  0x400
	#define LEFT_BUTTON  0x200
	#define RIGHT_BUTTON  0x100
	//Buttons need to be completed here
	#define BUFFER  uint16_t
#else
	#define A_BUTTON  B10000000
	#define B_BUTTON  B01000000
	#define SEL_BUTTON  B00100000
	#define START_BUTTON  B00010000
	#define UP_BUTTON  B00001000
	#define DOWN_BUTTON  B00000100
	#define LEFT_BUTTON  B00000010
	#define RIGHT_BUTTON  B00000001
	#define BUFFER  uint8_t
#endif

class NESC{
	public:
	NESC(void);
	
	void begin(int,int,int);
	void update(void);
	boolean pressed(BUFFER);
	boolean released(BUFFER);
	boolean exclusivePressed(BUFFER,BUFFER);
	
	boolean upButton(void);
	boolean downButton(void);
	boolean leftButton(void);
	boolean rightButton(void);
	boolean startButton(void);
	boolean selectButton(void);
	boolean aButton(void);
	boolean bButton(void);
	#if defined SNES_CONNTROLLER
	  bool xButton(void);
	  bool yButton(void);
	#endif
	
	private:
	int latch,clk,data;
	boolean is_started;
	BUFFER button_state = 0;

	BUFFER readController(void);
};

#endif