/**
 * @file machine.c
 * @brief Implémentation de la machine RAM.
 * 
 * @author Alexandre SBEGHEN
 * @date 2026-05-23
 */

#include "machine.h"
#include <stdlib.h>


Memory* memory_create() {
    Memory* mem;

    if ((mem = malloc(sizeof(Memory))) == NULL)
        return NULL;
    
    //Initialisation du tableau à 0 avec calloc
    if ((mem->data = calloc(MACHINE_MEMORY_SIZE, sizeof(MACHINE_MEMORY_TYPE))) == NULL) {
        free(mem);
        return NULL;
    }

    //Si valeur par défaut != 0 calloc ne suffit pas
    if (MACHINE_MEMORY_DEFAULT_VALUE != 0)
        for (size_t i = 0; i < MACHINE_MEMORY_SIZE; ++i)
            mem->data[i] = MACHINE_MEMORY_DEFAULT_VALUE;

    return mem;
}

Register* register_create() {
    Register* reg;

    if ((reg = malloc(sizeof(Register))) == NULL)
        return NULL;

    reg->val = MACHINE_REGISTER_DEFAULT_VALUE;
    
    return reg;
}

void memory_delete(Memory** mem) {
    //Libère data puis mem, et met *mem à NULL via le double pointeur
    free((*mem)->data);
    free(*mem);

    (*mem) = NULL;
}

void register_delete(Register** reg) {
    //Libère *reg puis le met à NULL via le double pointeur
    free(*reg);

    (*reg) = NULL;
}