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

    printf("Valeurs des cases de la mémoire :\n");
    for (size_t i = 0; i < MACHINE_MEMORY_SIZE; ++i)
        printf(MACHINE_MEMORY_TYPE_STRF " ", mem->data[i]);
    printf("\nLa valeur du registre vaut " MACHINE_MEMORY_TYPE_STRF "\n", reg->val);

    memory_delete(&mem);
    register_delete(&reg);
    return 0;
}