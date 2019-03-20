#include "memoryManagement.h"
#include "booleans.h"
#include "timer.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>

int canAllocate(struct MMU *mmu, int id, int base, int offset, int maxOffset)
{
    struct MMU *tmp = mmu;

    while (tmp->next)
    {

        if (tmp->base == base)
        {
            return MEMORY_ALREADY_ALLOCATED_ERROR;
        }
        else if (offset > maxOffset)
        {
            return CANNOT_ALLOCATE_MEMORY_AMOUNT_ERROR;
        }

        tmp = tmp->next;
    }

    if (tmp->base == base)
    {
        return MEMORY_ALREADY_ALLOCATED_ERROR;
    }
    else if (offset > maxOffset)
    {
        return CANNOT_ALLOCATE_MEMORY_AMOUNT_ERROR;
    }

    return 0;
}

int canAccess(struct MMU *mmu, int id, int base, int offset)
{

    struct MMU *tmp = mmu;

    while (tmp->next)
    {
        if (tmp->base == base)
        {
            if (tmp->id != id)
            {
                return WRONG_MEMORY_ACCESS_ID_ERROR;
            }
            else if (tmp->offset < offset)
            {
                return MEMORY_ACCESS_OUTSIDE_BOUNDS_ERROR;
            }

            return 0;
        }
    }

    if (tmp->base == base)
    {
        if (tmp->id != id)
        {
            return WRONG_MEMORY_ACCESS_ID_ERROR;
        }
        else if (tmp->offset < offset)
        {
            return MEMORY_ACCESS_OUTSIDE_BOUNDS_ERROR;
        }
        return 0;
    }

    return CANNOT_ACCESS_MEMORY_ERROR;
}

int allocate(struct MMU *mmu, int id, int base, int offset, int maxOffset)
{
    int error;
    struct MMU *tmp = mmu;

    error = canAllocate(mmu, id, base, offset, maxOffset);

    if (error)
    {
        return error;
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

    return 0;
}

int access(struct MMU *mmu, int id, int base, int offset)
{
    int error;

    error = canAccess(mmu, id, base, offset);

    if (error)
    {
        return error;
    }

    return 0;
}

void stripMemoryValues(int associatedValue, int *values)
{
    values[0] = associatedValue / 1000000;
    values[1] = (associatedValue / 1000) - (values[0] * 1000);
    values[2] = associatedValue - ((values[0] * 1000000) + (values[1] * 1000));
}