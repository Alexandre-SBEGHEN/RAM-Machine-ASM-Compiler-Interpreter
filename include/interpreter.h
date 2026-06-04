/**
 * @file interpreter.h
 * @brief Interpréteur du code compilé
 * 
 * Déclare les structures, les alias,
 * et les fonctions de l'interpréteur.
 * 
 * @author Alexandre SBEGHEN
 * @date 2026-06-04
 */

#ifndef INTERPRETER_H
#define INTERPRETER_H

// ------------------------------ IMPORTS ------------------------------
#include "machine.h"

// ------------------------------ ALIAS ------------------------------

typedef struct ProgramS Program;  /* Alias du type struct `ProgramS` */

// ------------------------------ STRUCTS ------------------------------

/**
 * @brief Programme compilé.
 * 
 * C'est une matrice qui continent N lignes et 2 colonnes.
 * 
 * La première colonne est l'instruction à exécuter, 
 * et la seconde colonne est l'argument de l'instruction.
 */
struct ProgramS {
    MACHINE_MEMORY_TYPE** instructions;
};

// ------------------------------ FONCTIONS ------------------------------

/**
 * @brief Crée un programme vide avec un certain nombre d'instructions.
 * 
 * @param number_of_instructions Nombre d'instructions que contiendra le programme.
 * 
 * @return L'adresse de la structure du programme.
 */
Program* program_create(const long number_of_instructions);

/**
 * @brief Interprète un programme compilé en amont.
 * 
 * @param prog Le programme compilé qui est une structure `Program`.
 */
void program_interpret(const Program* prog);

/**
 * @brief Libère la mémoire allouée par la création du struct `Program`. A exécuter en fin de programme.
 * 
 * @param prog L'adresse du pointeur struct du programme.
 */
void program_delete(Program** prog);

#endif