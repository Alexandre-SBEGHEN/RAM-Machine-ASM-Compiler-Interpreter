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

    // Test
    load_direct(reg, 3);
    store_to(reg, mem, 0);
    increment(reg);
    increment(reg);
    store_to(reg, mem, 1);
    load_from(reg, mem, 0);
    decrement(reg);
    store_to(reg, mem, 2);

    // Sortie : afficher la mémoire
    printf("----- Mémoire -----\n");
    for (size_t i = 0; i < MACHINE_MEMORY_SIZE; ++i)
        printf("%lu :\t" MACHINE_MEMORY_TYPE_STRF "\n", i, mem->data[i]);
    printf("-------------------\n");

    // Libération de la mémoire allouée par Memory et Register
    memory_delete(&mem);
    register_delete(&reg);
    return 0;
}