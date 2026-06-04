/**
 * @file interpreter.c
 * @brief Implémentation de l'interpréteur.
 * 
 * @author Alexandre SBEGHEN
 * @date 2026-06-04
 */

#include "interpreter.h"
#include "machine.h"
#include <stdlib.h>

// Création dynamique du programme compilé
Program* program_create(const size_t number_of_instructions) {
    Program* prog;

    if ((prog = malloc(sizeof(Program))) == NULL)
        return NULL;
    
    // Création dynamique du tableau d'adresses
    if ((prog->instructions = malloc(number_of_instructions * sizeof(long*))) == NULL) {
        free(prog);
        return NULL;
    }

    // Création dynamique des données de la matrice
    if ((prog->data = calloc(number_of_instructions * 2, sizeof(long))) == NULL) {
        free(prog->instructions);
        free(prog);
        return NULL;
    }

    // Faire pointer chaque adresse de `instructions` vers sa ligne correspondante dans `data`
    for (size_t i = 0; i < number_of_instructions; i++) {
        prog->instructions[i] = prog->data + i * 2;
    }

    return prog;
}

// Libération de la mémoire allouée pour Program et ses champs 
void program_delete(Program** prog) {
    if (prog == NULL || *prog == NULL) return;

    // Libère les champs de prog et le met à NULL via le double pointeur
    free((*prog)->data);
    free((*prog)->instructions);
    free(*prog);

    (*prog) = NULL;
}