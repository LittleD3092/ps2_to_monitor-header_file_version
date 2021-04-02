#include <arduino.h>
#include <PS2X_lib.h>
#include "ps2_to_2_wheel_car.h"

void ps2_to_motor::init_ps2(int dataPort, int commandPort, int attPort; int clockPort, bool supportAnalogJoystick, bool supportVibration)
{
	int error = 0;
	byte type = 0;
	
	//test ps2 console is connected or not
  	do
  	{  
    	error = ps2_to_motor::ps2x.config_gamepad(clockPort, commandPort, attPort, dataPort, supportAnalogJoystick, supportVibration);
    	if(error == 0)            Serial.println("Controller found");
    	else if(error == 1)       Serial.println("ERROR: No Controller found");
    	else if(error == 2)       Serial.println("ERROR: Controller not accepting command");  
    	else if(error == 3)       Serial.println("ERROR: Controller refusing to enter Pressures Mode, may not support it");
	}while(error != 0);

  	//determine controller type
  	type = ps2_to_motor::ps2x.readType();
  	switch(type)
  	{
  	  	case 0:   Serial.println("Unknown controller type");      break;
  	  	case 1:   Serial.println("DualShock controller found");   break;
    	case 2:   Serial.println("GuitarHero controller found");    break;
  	}

}


void ps2_to_motor::ps2_to_monitor()
{
	bool front, back, right, left;

	ps2_to_monitor::ps2Input(&front, &back, &right, &left);


	int wheelRightSpeed = 200;
	int wheelLeftSpeed  = 200;
  	if( front && !back && !right && !left)			//foward
  	{
  		Serial.print("right motor speed = ");	Serial.println(wheelRightSpeed * 0.8);
  		Serial.print("left  motor speed = ");	Serial.println(wheelLeftSpeed  * 0.8);
	}
	if(!front &&  back && !right && !left)			//backward
  	{
  		Serial.print("right motor speed = ");	Serial.println(wheelRightSpeed * (-0.8));
  		Serial.print("left  motor speed = ");	Serial.println(wheelLeftSpeed  * (-0.8));
	}
	if(!front && !back &&  right && !left)			//turn right
  	{
  		Serial.print("right motor speed = ");	Serial.println(wheelRightSpeed * (-0.5));
  		Serial.print("left  motor speed = ");	Serial.println(wheelLeftSpeed  * 0.5);
	}
	if(!front && !back && !right &&  left)			//turn left
  	{
  		Serial.print("right motor speed = ");	Serial.println(wheelRightSpeed * 0.5);
  		Serial.print("left  motor speed = ");	Serial.println(wheelLeftSpeed  * (-0.5));
	}
	if( front && !back &&  right && !left)			//front right
  	{
  		Serial.print("right motor speed = ");	Serial.println(wheelRightSpeed * 0.6);
  		Serial.print("left  motor speed = ");	Serial.println(wheelLeftSpeed  * 1);
	}
	if( front && !back && !right &&  left)			//front left
  	{
  		Serial.print("right motor speed = ");	Serial.println(wheelRightSpeed * 1);
  		Serial.print("left  motor speed = ");	Serial.println(wheelLeftSpeed  * 0.6);
	}
	if(!front &&  back &&  right && !left)			//back right
  	{
  		Serial.print("right motor speed = ");	Serial.println(wheelRightSpeed * (-0.6));
  		Serial.print("left  motor speed = ");	Serial.println(wheelLeftSpeed  * (-1));
	}
	if(!front &&  back && !right &&  left)			//back left
  	{
  		Serial.print("right motor speed = ");	Serial.println(wheelRightSpeed * (-1));
  		Serial.print("left  motor speed = ");	Serial.println(wheelLeftSpeed  * (-0.6));
	}
	if(!front && !back && !right && !left)			//stop
  	{
  		Serial.println("right motor speed = 0");
  		Serial.println("left  motor speed = 0");
	}

	Serial.println("");
}


void ps2_to_motor::ps2Input(*bool front, *bool back, *bool right, *bool left)
{
	int ps2_left_analog_Y = 255 - ps2_to_motor::ps2x.Analog(PSS_LY);
  	int ps2_right_analog_X = ps2_to_motor::ps2x.Analog(PSS_RX);
  	Serial.print("ps2 left y = ");				Serial.println(ps2_left_analog_Y);
  	Serial.print("ps2 right x = ");				Serial.println(ps2_right_analog_X);

  	front = (ps2_left_analog_Y  > 256/2 + deadArea/2);
  	back  = (ps2_left_analog_Y  < 256/2 - deadArea/2);
  	right = (ps2_right_analog_X > 256/2 + deadArea/2);
  	left  = (ps2_right_analog_X < 256/2 - deadArea/2);
}