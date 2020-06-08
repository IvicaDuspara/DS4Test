#ifndef DS4TEST_PARSER_H
#define DS4TEST_PARSER_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
enum test_command_type{
    light_bar = 0,
    heavy_motor = 1,
    light_motor = 2,
};

struct parsed_pair{
    enum test_command_type command;
    union value_type {
        int rgb[3];
        int motor_value;
    } value;
};

struct parsed_pair parse_input(char* input, int input_length) {
    char command[6] = {'\0','\0','\0','\0','\0','\0'};
    char value[6] = {'\0','\0','\0','\0','\0','\0'};
    int i = 0;
    while(input[i] != ' ' && i < input_length) {
        command[i] = input[i];
        i++;
    }
    i++;
    while(input[i] != '\0' && i < input_length) {
        printf("i: %d\n", i);
        value[i] = input[i] + 48;
        i++;
    }
    printf("2: %s\n",value);
    struct parsed_pair tc;
    if(strcmp(command,"light") == 0) {
        tc.command = light_bar;
    }
    else if(strcmp(command,"hmotor") == 0) {
        tc.command = heavy_motor;
    }
    else if(strcmp(command,"lmotor") == 0) {
        tc.command = light_motor;
    }
    if(tc.command == light_bar) {
        int red = 0, green = 0, blue = 0;
        printf("%s\n",value);
        sscanf(value,"%02x%02x%02x",&red,&green,&blue);
        printf("%02x %02x %02x\n",red,green,blue);
        tc.value.rgb[0] = red;
        tc.value.rgb[1] = green;
        tc.value.rgb[2] = blue;
    }
    else{
        for(int i = 0; i < 3; i++) {
            input[6 - i - 1] = input[i];
        }
        input[0] = 0;
        input[1] = 0;
        input[2] = 0;
        sscanf(input,"%03d",&tc.value.motor_value);
        if(tc.command == light_motor || tc.command == heavy_motor && (tc.value.motor_value < 0 || tc.value.motor_value > 0)) {
            tc.value.motor_value = 0;
        }
    }
    return tc;
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
