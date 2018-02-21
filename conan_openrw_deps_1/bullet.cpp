#include <BulletCollision/NarrowPhaseCollision/btManifoldPoint.h>
#include <BulletCollision/NarrowPhaseCollision/btPersistentManifold.h>

#include <cstdio>

bool contactProcessedCallback(btManifoldPoint &, void *, void *) {
    return false;
}


int do_bullet(int argc, char **argv) {
    gContactProcessedCallback = contactProcessedCallback;
    return 0;
}
