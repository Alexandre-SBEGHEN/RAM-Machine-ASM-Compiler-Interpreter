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
#include <stdio.h>

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

// Exécution du programme compilé
void program_interpret(const Program* prog, Memory* mem, Register* reg) {
    size_t instruction_index = 0;

    // Boucle du programme
    while (1) {
        long inst = prog->instructions[instruction_index][0]; // Instruction actuelle
        long arg = prog->instructions[instruction_index][1];  // Argument / opérande actuel

        // Action à faire selon l'instruction
        switch (inst) {
            // Ne rien faire
            case 0: break;
            // LOAD #?
            case 1: load_direct(reg, arg); break;
            // LOAD @?
            case 2: load_from(reg, mem, arg); break;
            // STORE @?
            case 3: store_to(reg, mem, arg); break;
            // INCR
            case 4: increment(reg); break;
            // DECR
            case 5: decrement(reg); break;
            // JUMP ?
            case 6:
                if (arg < 0) return;
                instruction_index = arg;
                continue;
            // JZ ?
            case 7:
                if (arg < 0) return;
                if (reg->val <= 0) {
                    instruction_index = arg;
                    continue;
                }
                break;
            // HALT
            case 8: return;
            // Instruction inconnue (arrêt de l'interpréteur)
            default:
                return;
        }

        // Instruction suivante
        ++instruction_index;
    }
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