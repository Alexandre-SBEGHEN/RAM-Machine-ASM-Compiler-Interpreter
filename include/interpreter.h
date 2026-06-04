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

#endif