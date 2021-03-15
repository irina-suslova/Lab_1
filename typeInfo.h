#ifndef TYPEINFO_H
#define TYPEINFO_H

#include <stdio.h>

struct TypeInfo {
    size_t elementSize;

    void* zero;
    void* one;
    void* (*minus)(void*);

    void* (*sum)(void*, void*);
    void* (*mul)(void*, void*);

    void* (*random)();
    void* (*show)(void*);
};

#endif // TYPEINFO_H
