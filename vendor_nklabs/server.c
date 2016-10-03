/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    FILE *fd;
    char buffer [] = {0,0,0,0};

    fd = fopen("/dev/pcnt8", "r");

    fgets(buffer, 4, (FILE*)fd);

    uint32_t regValue =  ( (buffer[3] << 24) | (buffer[2] << 16) | ( buffer[1] << 8) | ( buffer[0] << 0 ) );

    printf("pulses = %lu\n", (long unsigned int)regValue);

    fclose(fd);

    return 0;
}
