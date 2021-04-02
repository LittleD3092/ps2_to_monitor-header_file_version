#include <arduino.h>
#include <PS2X_lib.h>

class ps2_to_motor
{
public:
	void init_ps2(int, int, int, int, bool, bool);
	void ps2_to_monitor();
	
private:
	void ps2Input(*bool, *bool, *bool, *bool);
	PS2X ps2x;
};