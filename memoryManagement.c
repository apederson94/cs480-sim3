#include "memoryManagement.h"
#include "booleans.h"
#include "timer.h"

bool canAllocate(struct MMU *mmu, int id, int base, int offset, int maxOffset)
{
    struct MMU *tmp = mmu;

    while (tmp->next)
    {

        if (tmp->base == base)
        {
            return FALSE; //TODO: CREATE A SEGFAULT ERROR CODE FOR THIS
        }
        else if (offset > maxOffset)
        {
            return FALSE; //TODO: CREATE AN ERROR CODE FOR THIS
        }

        tmp = tmp->next;
    }

    if (tmp->base == base)
    {
        return FALSE; //TODO: CREATE A SEGFAULT ERROR CODE FOR THIS
    }
    else if (offset > maxOffset)
    {
        return FALSE; //TODO: CREATE AN ERROR CODE FOR THIS
    }

    return TRUE;
}

bool canAccess(struct MMU *mmu, int id, int base, int offset)
{

    struct MMU *tmp = mmu;

    while (tmp->next)
    {
        if (tmp->base == base)
        {
            if (tmp->id != id)
            {
                return FALSE; //TODO: CREATE AND ERROR CODE FOR THIS
            }
            else if (tmp->offset < offset)
            {
                return FALSE; //TODO: CREATE AN ERROR CODE FOR THIS
            }

            return TRUE;
        }
    }

    return FALSE;
}

int allocate(struct MMU *mmu, int id, int base, int offset, int maxOffset)
{
    struct MMU *tmp = mmu;

    if (!canAllocate(mmu, id, base, offset, maxOffset))
    {
        return 0; //TODO: NEW ERROR CODE HERE FOR NOT BEING ABLE TO ALLOCATE MEMORY. SEGFAULT
    }

    while (tmp->next)
    {
        tmp = tmp->next;
    }

    if (tmp->id != FIRST)
    {
        tmp->next = (struct MMU *)calloc(1, sizeof(struct MMU *));
        tmp = tmp->next;
    }

    tmp->id = id;
    tmp->base = base;
    tmp->offset = offset;
}

int access(struct MMU *mmu, int id, int base, int offset)
{
    if (!canAccess(mmu, id, base, offset))
    {
        return 0; //TODO: NEW ERROR CODE HERE FOR NOT BEING ABLE TO ACCESS MEMORY. SEGFAULT
    }

    return 0;
}