#include "definitions.h"




int state_machine()
{
	enum states state = INIT;

	while (1)
	{
		switch (state) 
		{
			case INIT:
				//init_motor();
				//init_imus()
				//init_display();
				state = ERROR;
				break;

			case IDLE:
				break;

			case FLIP:
				break;

			case BALANCE:
				break;

			case ERROR:
				return KUBE_ERROR;
				break;
		}
	}

	return KUBE_ERROR;
}

int main()
{
	state_machine();
}
