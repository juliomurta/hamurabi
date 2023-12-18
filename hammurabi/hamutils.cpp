#include <time.h>
#include <stdlib.h>
#include "hamutils.h"

int generate_random(int min, int max)
{
	srand(time(NULL));
	return rand() % ((max + 1) - min) + min;
}