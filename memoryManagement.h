#include "booleans.h"

#ifndef MEMORY_MANAGEMENT
#define MEMORY_MANAGEMENT

//holds all memory management information
struct MMU
{
    int id;
    int base;
    int offset;
    struct MMU *next;
};

//denotes whether mmu is first or not
enum
{
    FIRST = -10
};

//checks to see if memory can be allocated
bool canAllocate(struct MMU *mmu, int id, int base, int offset, int maxOffset);

//checks to see if process can access memory
bool canAccess(struct MMU *mmu, int id, int base);

//allocates memory to a process
int allocate(struct MMU *mmu, int id, int base, int offset);

//accesses memory from a process
int access(struct MMU *mmu, int id, int base, int offset);

#endif