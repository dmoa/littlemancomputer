#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 3 letter input + space + max 5 length number
#define MAX_INPUT 9

// LMC allows only 3 digits, but that's weird to implement as it isn't a nice round number of bits,
// so we're just saying it's 8 bits.
typedef unsigned char NUM_BITS;
#define NUM_MEMORY 100

int strequal(char* a, const char* b) { return strcmp(a, b) == 0; }

struct LMC {
    NUM_BITS memory [NUM_MEMORY];
    NUM_BITS program_counter;
    NUM_BITS instruction_registor;
    NUM_BITS address_register;
    NUM_BITS accumulator;
} typedef LMC;

int main() {

    char input [MAX_INPUT];

    LMC lmc;

    while (! strequal(input, "HLT")) {

        fgets(input, MAX_INPUT, stdin);
        // Removing \n from input string
        int input_len = strlen(input);
        input[--input_len] = '\0';


        int space_index = -1;
        for (int i = 0; i < input_len; i++) {
            if (input[space_index] == ' ') {
                space_index = i;
                break;
            }
        }

        // If no space was found, it's an instruction with no parameters
        if (space_index == -1) {

            // LOAD
            if (strequal(input, "LDA")) {

                printf("$: ");
                fgets(input, MAX_INPUT, stdin);
                int input_len = strlen(input);
                input[--input_len] = '\0';

                lmc.accumulator = atoi(input);
            }
            // OUTPUT
            else if (strequal(input, "OUT")) {
                printf("%i\n", lmc.accumulator);
            }
        }
        // Otherwise, it's a function with parameters
        else {

        }

    }

    return 0;
}