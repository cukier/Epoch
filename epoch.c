/*
 * epoch.c
 *
 *  Created on: 08/06/2012
 *      Author: cuki
 */

//#include <stdio.h>
//#include <stdlib.h>
#include "epoch.h"

int main(int argc, char **argv) {

	fromEpoch(atof(argv[1]));

	toEpoch(2016, 3, 31, 23, 59, 1);

	return 0;

}
