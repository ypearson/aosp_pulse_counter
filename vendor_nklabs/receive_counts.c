#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dlfcn.h>

int main(void)
{
    void *handle;
    uint32_t (*rcnt)();
    const char *error;

    handle = dlopen ("/system/lib64/hw/rcnt.qcom.so", RTLD_LAZY);
    if (!handle)
    {
        fputs (dlerror(), stderr);
        exit(1);
    }

    rcnt = dlsym(handle, "rcnt__read");
	error = dlerror();

    if (error != NULL)
    {
        fputs(error, stderr);
        exit(1);
    }

    printf ("rcnt = %lu\n", (long unsigned int)(*rcnt)());
    dlclose(handle);

    return 0;
}