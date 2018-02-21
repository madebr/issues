#include <al.h>
#include <alc.h>

#include <cstdio>

int do_openal(int argc, char **argv) {
    ALCdevice *alDevice = alcOpenDevice(NULL);
    if (!alDevice) {
        puts("Could not find OpenAL device!\n");
        return 1;
    }

    ALCcontext *alContext = alcCreateContext(alDevice, NULL);
    if (!alContext) {
        puts("Could not create OpenAL context\n");
        return 1;
    }

    if (!alcMakeContextCurrent(alContext)) {
        puts("Unable to make OpenAL context current!\n");
        return 1;
    }

    if (alContext) {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(alContext);
    }

    if (alDevice) alcCloseDevice(alDevice);
    return 0;
}
