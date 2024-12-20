#include "definitions.h"


enum states
{
	INIT,
	IDLE,
	FLIP,
	BALANCE,
	ERROR
};


int state_machine()
{
	enum states state = INIT;

	switch (state) 
	{
		case INIT:
			init_motor();
			init_imus()
			init_display();
			break;

		case IDLE:
			break;

		case FLIP:
			break;

		case BALANCE:
			break;

		case ERROR:
			break;
	}

	return KUBE_ERROR;
}
