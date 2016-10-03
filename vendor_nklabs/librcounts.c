#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define  LOG_TAG  "rcnt"
#include <cutils/log.h>
#include <cutils/sockets.h>
#include <hardware/rcnt.h>

#define   RCNT_DEBUG   1

#if RCNT_DEBUG
#  define D(...)   ALOGD(__VA_ARGS__)
#else
#  define D(...)   ((void)0)
#endif

int fd = 0;

uint32_t rcnt__read(void)
{
    D("RCNT_DEBUG - read()for bytes called");

    FILE *fd;
    char buffer [] = {0,0,0,0};

    fd = fopen("/dev/pcnt8", "r");

    fgets(buffer, 4, (FILE*)fd);

    uint32_t regValue =  ( (buffer[3] << 24) | (buffer[2] << 16) | ( buffer[1] << 8) | ( buffer[0] << 0 ) );

    fclose(fd);

    return regValue;
}


// int opersyshw__write(char* buffer, int length)
// {
//     D("OPERSYS HW - write()for %d bytes called", length);

//     return write(fd, buffer, length);
// }

// int rcnt__test(int value)
// {
//     return value;
// }

// #define CMD_BASE             (0xFAD1001)
// #define CMD_ZERO_CONTENT     (CMD_BASE + 1)
// #define CMD_IS_THERE_CONTENT (CMD_BASE + 2)

// void opersyshw__zero_content(void)
// {
//     ioctl(fd, CMD_ZERO_CONTENT, 0);
// }

// int opersyshw__is_there_content(void)
// {
//     return ioctl(fd, CMD_IS_THERE_CONTENT, 0);
// }

static int open_rcnt(const struct hw_module_t* module, char const* name, struct hw_device_t** device)
{
    struct rcnt_device_t *dev = malloc(sizeof(struct rcnt_device_t));
    memset(dev, 0, sizeof(*dev));

    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = 0;
    dev->common.module = (struct hw_module_t*)module;
    dev->read = rcnt__read;
    // dev->write = opersyshw__write;
    // dev->test = opersyshw__test;
    // dev->zero_content = opersyshw__zero_content;

    //fd = open( "/dev/pcnt8", O_RDWR);
    *device = (struct hw_device_t*) dev;

    D("RCNT_DEBUG has been initialized");
    name; //warning...

    return 0;
}

static struct hw_module_methods_t rcnt_module_methods = {
    .open = open_rcnt
};

struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .version_major = 1,
    .version_minor = 0,
    .id = RCNT_HARDWARE_MODULE_ID,
    .name = "Pulse Count HW Module",
    .author = "nklabs",
    .methods = &rcnt_module_methods,
};
