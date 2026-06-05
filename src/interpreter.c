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
    if ((prog->instructions = malloc(number_of_instructions * sizeof(MACHINE_MEMORY_TYPE*))) == NULL) {
        free(prog);
        return NULL;
    }

    // Création dynamique des données de la matrice
    if ((prog->data = calloc(number_of_instructions * 2, sizeof(MACHINE_MEMORY_TYPE))) == NULL) {
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

// Création d'une structure Program à partir d'un .bin
Program* bin_to_program(FILE* file) {
    if (file == NULL) return NULL;

    //Vérifier que le fichier contient des blocs de 8 octets (paire instruction / opérande)
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    if (file_size % 8 != 0) return NULL;

    // Le nombre d'instructions est la taille du fichier / 8
    long number_of_instructions = file_size / 8;
    Program* prog = program_create(number_of_instructions);
    if (prog == NULL) return NULL;

    // Encodage des instructions
    for (long i = 0; i < number_of_instructions; ++i) {
        // On place chaque "partie" (octet) du nombre dans un buffer
        unsigned char instbytes[4], argbytes[4];
        if (fread(instbytes, 1, 4, file) != 4 || fread(argbytes, 1, 4, file) != 4) {
            program_delete(&prog);
            return NULL;
        }
        
        // On concatène les parties pour obtenir le grand nombre (4 octets)
        MACHINE_MEMORY_TYPE inst = (MACHINE_MEMORY_TYPE)(
            (MACHINE_MEMORY_TYPE)instbytes[0] << 24 |
            (MACHINE_MEMORY_TYPE)instbytes[1] << 16 |
            (MACHINE_MEMORY_TYPE)instbytes[2] << 8  |
            (MACHINE_MEMORY_TYPE)instbytes[3]
        );
        MACHINE_MEMORY_TYPE arg = (MACHINE_MEMORY_TYPE)(
            (MACHINE_MEMORY_TYPE)argbytes[0] << 24 |
            (MACHINE_MEMORY_TYPE)argbytes[1] << 16 |
            (MACHINE_MEMORY_TYPE)argbytes[2] << 8  |
            (MACHINE_MEMORY_TYPE)argbytes[3]
        );

        // On encode inst et arg dans le programme
        prog->instructions[i][0] = inst;
        prog->instructions[i][1] = arg;
    }

    return prog;
}

// Exécution du programme compilé
void program_interpret(const Program* prog, Memory* mem, Register* reg) {
    size_t instruction_index = 0;

    // Boucle du programme
    while (1) {
        MACHINE_MEMORY_TYPE inst = prog->instructions[instruction_index][0]; // Instruction actuelle
        MACHINE_MEMORY_TYPE arg = prog->instructions[instruction_index][1];  // Argument / opérande actuel

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
    if ((*prog)->data != NULL)
        free((*prog)->data);
    if ((*prog)->instructions != NULL)
        free((*prog)->instructions);
    free(*prog);

    (*prog) = NULL;
}