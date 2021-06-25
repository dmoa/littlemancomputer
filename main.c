// @ NOTE
// DAT only implementable when lmc is not line by line executed.

// @ TODO
// ADD
// SUB
// BRA
// BRZ
// BRP

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
int isinstruction(char* a, const char* b) { return a[0] == b[0] && a[1] == b[1] && a[2] == b[2]; }

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

    while (! isinstruction(input, "HLT")) {

        fgets(input, MAX_INPUT, stdin);
        // Removing \n from input string
        int input_len = strlen(input);
        input[--input_len] = '\0';


        int space_index = -1;
        for (int i = 0; i < input_len; i++) {
            if (input[i] == ' ') {
                space_index = i;
                break;
            }
        }

        // If no space was found, it's an instruction with no parameters
        if (space_index == -1) {

            // INPUT

            if (isinstruction(input, "INP")) {
                printf("$: ");
                fgets(input, MAX_INPUT, stdin);
                int input_len = strlen(input);
                input[--input_len] = '\0';

                lmc.accumulator = atoi(input);
            }

            // OUTPUT

            else if (isinstruction(input, "OUT")) {
                printf("%i\n", lmc.accumulator);
            }
        }
        // Otherwise, it's a function with parameters
        else {

            // ADD
            if (isinstruction(input, "ADD")) {
                int address = atoi(& input[4]);
                lmc.accumulator += lmc.memory[address];
            }

            // SUB
            if (isinstruction(input, "SUB")) {
                int address = atoi(& input[4]);
                lmc.accumulator -= lmc.memory[address];
            }

            // LOAD

            if (isinstruction(input, "LDA")) {
                int address = atoi(& input[4]);
                lmc.accumulator = lmc.memory[address];
            }

            // STORE

            else if (isinstruction(input, "STA")) {
                int address = atoi(& input[4]);
                lmc.memory[address] = lmc.accumulator;
            }
        }

    }

    return 0;
}