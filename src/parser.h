#ifndef DS4TEST_PARSER_H
#define DS4TEST_PARSER_H
#define MAX_COMMAND_LENGTH 7
#define MAX_VALUE_LENGTH 7
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
const char* l_command = "light";
const char* lm_command = "lmotor";
const char* hm_command = "hmotor";

enum test_command_type{
    light_bar = 0,
    heavy_motor = 1,
    light_motor = 2,
    invalid_command = -1
};

struct parsed_pair{
    enum test_command_type command;
    union value_type {
        int rgb[3];
        int motor_value;
    } value;
};
struct parsed_pair parse_input(char* input, int input_length) {
    char command[MAX_COMMAND_LENGTH] = {'\0'};
    char value[MAX_VALUE_LENGTH] = {'\0'};
    char *space = strchr(input,' ');
    struct parsed_pair command_value_pair;

    if(space == NULL) {
        printf("Invalid command.");
        command_value_pair.command = invalid_command;
    }
    else {
        int i = 0, j = 0;
        while(input[i] != *space) {
            command[i] = input[i];
            i++;
        }
        i++;
        while(input[i] != '\0' && input[i] != '\n' && i < input_length) {
            value[j] = input[i];
            j++;
            i++;
        }
        if(strcmp(command,l_command) == 0) {
            command_value_pair.command = light_bar;
            sscanf(value,"%02x%02x%02x",&command_value_pair.value.rgb[0],&command_value_pair.value.rgb[1],&command_value_pair.value.rgb[2]);
        }
        else {
            long motor_value = strtol(value,NULL,10);
            if(motor_value < 0 || motor_value > 255) {
                motor_value = 0;
            }
            command_value_pair.value.motor_value = motor_value;
            if(strcmp(command,lm_command) == 0) {
                command_value_pair.command = light_motor;
            }
            else if(strcmp(command,hm_command) ==0) {
                command_value_pair.command = heavy_motor;
            }
            else {
                command_value_pair.command = invalid_command;
            }
        }
    }
    return command_value_pair;
}

void create_buffer(unsigned char* buffer, int buffer_length, struct parsed_pair* pp) {
    if(buffer_length != 32) {
        printf("Handle buffer length hoss.!\n");
    }
    for(int i = 0; i < buffer_length ; i++) {
        buffer[i] = 0;
    }
    buffer[0] = 0x5;
    buffer[1] = 0x3F;
    if(pp->command == heavy_motor) {
        buffer[5] = pp->value.motor_value;
    }
    else if(pp->command == light_motor) {
        buffer[4] = pp->value.motor_value;
    }
    else if(pp->command == light_bar) {
        buffer[6] = pp->value.rgb[0];
        buffer[7] = pp->value.rgb[1];
        buffer[8] = pp->value.rgb[2];
    }
}

#endif //DS4TEST_PARSER_H
