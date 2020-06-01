#ifndef POWERSET_H_
#define POWERSET_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "helpers.h"
#include "dictionary.h"

typedef struct int_char_ptr
{
	char ***table;
	int *count;
	;
}
int_char_ptr;

char ***init_table(int size);
int *init_int_array(int size);
int_char_ptr *getPowerSet(char *set, int set_size);


#endif /* POWERSET_H_ */
