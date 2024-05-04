#ifndef _CONVERTER_
#define _CONVERTER_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "fields.h"
#include "dllist.h"
#include "utility.h"

/*
 * Reads the input file, converts it to the desired format 
 * and writes it to the output file.
 */
void convert_file(char *input_file, char *output_file);

#endif