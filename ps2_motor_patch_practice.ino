#include "ps2_to_2_wheel_car.h"

#define dataPort 8                      //port 1: data
#define commandPort 9                   //port 2: command
                                        //port 3: shock motor power

//goundPort GND                         //port 4: ground
//Vcc(3.3V) Vin                         //port 5: 3.3V power
#define attPort 10                      //port 6: attribute select

#define clockPort 11                    //port 7: clock
                                        //port 8: NULL
                                        //port 9: ACK response

//feature setting
#define supportAnalogJoystick true      //does it support anolog joystick?
#define supportVibration true           //does it support vibration?

ps2_to_motor car;

void setup()
{
  	Serial.begin(9600);
    Serial.println();
    Serial.println("start");
  	car.init_ps2(dataPort, commandPort, attPort, clockPort, supportAnalogJoystick, supportVibration);
}

void loop()
{
  	car.ps2_to_monitor();
  	delay(500);
}
