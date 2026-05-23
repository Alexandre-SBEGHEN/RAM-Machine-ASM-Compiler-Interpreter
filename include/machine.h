#ifndef MACHINE_H
#define MACHINE_H

#define MACHINE_MEMORY_TYPE int
#define MACHINE_MEMORY_SIZE 128

/**
 * @brief Chargement direct du registre
 * 
 * @param reg L'adresse du registre
 * @param val La valeur à charger
 */
void load_direct(MACHINE_MEMORY_TYPE* reg, MACHINE_MEMORY_TYPE val);

/**
 * @brief Chargement du registre vers la mémoire
 * 
 * @param reg L'adresse du registre
 * @param val L'index de la case mémoire
 */
void load_from(MACHINE_MEMORY_TYPE* reg, unsigned index);

/**
 * @brief Rangement du registre depuis la mémoire
 * 
 * @param reg L'adresse du registre
 * @param val L'index de la case mémoire
 */
void store_to(MACHINE_MEMORY_TYPE* reg, unsigned index);

/**
 * @brief Incrémentation du registre
 * 
 * @param reg L'adresse du registre
 */
void increment(MACHINE_MEMORY_TYPE* reg);

/**
 * @brief Décrémentation du registre
 * 
 * @param reg L'adresse du registre
 */
void decrement(MACHINE_MEMORY_TYPE* reg);

/**
 * @brief Saut inconditionnel à l’étiquette (nombre)
 * 
 * @param index Indice associé à l'étiquette
 */
void jump(unsigned index);

/**
 * @brief Saut à l'étiquette (nombre) si (registre ≤ 0)
 * 
 * @param reg L'adresse du registre
 * @param index Indice associé à l'étiquette
 */
void jumpzero(MACHINE_MEMORY_TYPE* reg, unsigned index);

/**
 * @brief Arrêt du programme
 */
void halt();


#endif