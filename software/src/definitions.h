#ifndef DEFINITIONS_H
#define DEFINITIONS_H


//#include "../sam-stuff/sam.h"
#include "../sam-core/sam.h"

/* return values of functions*/

#define KUBE_SUCCESS 1
#define KUBE_ERROR -1


enum states
{
	INIT,
	IDLE,
	FLIP,
	BALANCE,
	ERROR
};






#endif
