/**
 * @file main.c
 * @brief Point d'entrée du programme.
 *
 * @author Alexandre SBEGHEN
 * @date 2026-05-23
 */

#include <stdio.h>
#include "machine.h"

int main() {
    Memory* mem = memory_create();
    Register* reg = register_create();

    load_direct(reg, 3);
    store_to(reg, mem, 0);
    increment(reg);
    increment(reg);
    store_to(reg, mem, 1);
    load_from(reg, mem, 0);
    decrement(reg);
    store_to(reg, mem, 2);

    
    for (size_t i = 0; i < MACHINE_MEMORY_SIZE; ++i)
        printf(MACHINE_MEMORY_TYPE_STRF " ", mem->data[i]);
    printf("\n");


    memory_delete(&mem);
    register_delete(&reg);
    return 0;
}