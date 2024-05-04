#include <stdlib.h>
#include <stdio.h>
#include "converter.h"

int main(int argc, char **argv)
{
        char input_file[120] = "txt/giris.dat";
        char output_file[120] = "txt/cikis.dat";

        if (argc != 3) {
                printf("usage: %s <input file path> <output file path>\n", argv[0]);
                printf("default input and output files is being used (data/giris.dat & data/cikis.dat)\n");
        } else {
                strcpy(input_file, argv[1]);
                strcpy(output_file, argv[2]);
        }

        convert_file(input_file, output_file);

        return 0;
}