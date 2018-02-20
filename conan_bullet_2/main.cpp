#include <BulletCollision/NarrowPhaseCollision/btManifoldPoint.h>
#include <BulletCollision/NarrowPhaseCollision/btPersistentManifold.h>

#include <cstdio>

bool contactProcessedCallback(btManifoldPoint &, void *, void *) {
    return false;
}

int main() {
    gContactProcessedCallback = contactProcessedCallback;
    puts("success!\n");
    return 0;
}
