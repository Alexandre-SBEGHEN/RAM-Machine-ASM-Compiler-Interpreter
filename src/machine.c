/**
 * @file machine.c
 * @brief Implémentation de la machine RAM.
 * 
 * @author Alexandre SBEGHEN
 * @date 2026-05-23
 */

#include "machine.h"
#include <stdlib.h>
#include <stdint.h>

// Création dynamique de la mémoire
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

// Création dynamique du registre
Register* register_create() {
    Register* reg;

    if ((reg = malloc(sizeof(Register))) == NULL)
        return NULL;

    reg->val = MACHINE_REGISTER_DEFAULT_VALUE;
    
    return reg;
}

// Chargment direct du registre
void load_direct(Register* reg, const MACHINE_MEMORY_TYPE val) {
    reg->val = val;
}

// Chargement du registre depuis la mémoire
void load_from(Register* reg, Memory* mem, const MACHINE_MEMORY_TYPE index) {
    reg->val = mem->data[index];
}

// Sauvegarde du registre vers la mémoire
void store_to(Register* reg, Memory* mem, const MACHINE_MEMORY_TYPE index) {
    mem->data[index] = reg->val;
}

// Incrémentation du registre
void increment(Register* reg) {
    ++reg->val;
}

// Décrémentation du registre
void decrement(Register* reg) {
    --reg->val;
}

// Libération de la mémoire allouée pour Memory et ses champs 
void memory_delete(Memory** mem) {
    if (mem == NULL || *mem == NULL) return;

    //Libère data puis mem, et met *mem à NULL via le double pointeur
    if ((*mem)->data != NULL)
        free((*mem)->data);
    free(*mem);

    (*mem) = NULL;
}

// Libération de la mémoire allouée pour Register et ses champs 
void register_delete(Register** reg) {
    if (reg == NULL || *reg == NULL) return;

    //Libère *reg puis le met à NULL via le double pointeur
    free(*reg);

    (*reg) = NULL;
}