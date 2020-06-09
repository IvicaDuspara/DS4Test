#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "parser.h"
int main () {
   unsigned char buffer[32] = {'\0'};
   struct parsed_pair pp;
   char my_buffer[32];
   fgets(my_buffer,32,stdin);
   pp = parse_input(my_buffer,32);
   create_buffer(buffer,32,&pp);
   int _fd = open("/dev/hidraw1",O_RDWR | O_NONBLOCK);
   if(_fd == -1) {
       printf("Could not open device.");
       exit(-1);
   }
   write(_fd,buffer,sizeof(buffer));
    return 0;
}

