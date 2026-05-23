/**
 * @file machine.h
 * @brief Interface de la machine RAM.
 * 
 * Déclare les constantes, les structures,
 * les alias, et les fonctions pour initialiser,
 * manipuler, et détruire une machine RAM. 
 * 
 * @author Alexandre SBEGHEN
 * @date 2026-05-23
 */

#ifndef MACHINE_H
#define MACHINE_H

// ------------------------------ CONSTANTES ------------------------------
#define MACHINE_MEMORY_TYPE long            /* Type de données inscrites dans les cases de la mémoire */
#define MACHINE_MEMORY_TYPE_STRF "%ld"      /* Formattage du type dans une string */
#define MACHINE_MEMORY_SIZE 128             /* Taille de la mémoire (i.e. nombre de cases) */
#define MACHINE_MEMORY_DEFAULT_VALUE 0      /* Valeur par défaut des cases de la mémoire lors de sa création */
#define MACHINE_REGISTER_DEFAULT_VALUE 0    /* Valeur par défaut du registre lors de sa création */

// ------------------------------ ALIAS ------------------------------

typedef struct RegisterS Register;  /* Alias du type struct `RegisterS` */
typedef struct MemoryS Memory;      /* Alias du type struct `MemoryS` */

// ------------------------------ STRUCTS ------------------------------

/**
 * @brief Registre de la machine. Ne peut contenir qu'une valeur de type `MACHINE_MEMORY_TYPE`.
 */
struct RegisterS {
    MACHINE_MEMORY_TYPE val; /* Valeur du registre */
};

/**
 * @brief Mémoire de la machine. Peut contenir `MACHINE_MEMORY_SIZE` valeurs de type `MACHINE_MEMORY_TYPE`.
 */
struct MemoryS {
    MACHINE_MEMORY_TYPE* data; /* Cases de la mémoire */
};

// ------------------------------ FONCTIONS ------------------------------

/**
 * @brief Crée dynamiquement un struct `Memory` pour la mémoire de la machine. Initialise toutes les cases à `MACHINE_MEMORY_DEFAULT_VALUE`.
 * 
 * @return L'adresse du struct de la mémoire.
 */
Memory* memory_create();

/**
 * @brief Crée dynamiquement un struct `Register` pour le registre de la machine. Initialise sa valeur à `MACHINE_REGISTER_DEFAULT_VALUE`.
 * 
 * @return L'adresse du struct du registre.
 */
Register* register_create();

/**
 * @brief Chargement direct du registre
 * 
 * @param reg L'adresse du registre
 * @param val La valeur à charger
 */
void load_direct(Register* reg, MACHINE_MEMORY_TYPE val);

/**
 * @brief Chargement du registre depuis la mémoire
 * 
 * @param reg L'adresse du registre
 * @param mem L'adresse de la mémoire
 * @param val L'index de la case mémoire
 */
void load_from(Register* reg, Memory* mem, unsigned index);

/**
 * @brief Rangement du registre vers la mémoire
 * 
 * @param reg L'adresse du registre
 * @param mem L'adresse de la mémoire
 * @param val L'index de la case mémoire
 */
void store_to(Register* reg, Memory* mem, unsigned index);

/**
 * @brief Incrémentation du registre
 * 
 * @param reg L'adresse du registre
 */
void increment(Register* reg);

/**
 * @brief Décrémentation du registre
 * 
 * @param reg L'adresse du registre
 */
void decrement(Register* reg);

/**
 * @brief Libère la mémoire allouée par la création du struct `Memory`. A exécuter en fin de programme.
 * 
 * @param mem L'adresse du pointeur du struct de la mémoire
 */
void memory_delete(Memory** mem);

/**
 * @brief Libère la mémoire allouée par la création du struct `Register`. A exécuter en fin de programme.
 * 
 * @param reg L'adresse du pointeur struct du registre
 */
void register_delete(Register** reg);

#endif