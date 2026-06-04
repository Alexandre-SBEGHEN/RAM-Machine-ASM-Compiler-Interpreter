/**
 * @file test_machine.c
 * @brief Fichier de tests des fonctions de machine.c.
 * 
 * @author Alexandre SBEGHEN
 * @date 2026-05-24
 */
#include <stdio.h>
#include "test.h"
#include "machine.h"

 /**
  * @brief Vérifie les choses suivantes :
  * 
  * - La création de la mémoire
  * - La création du tableau des cases
  * - Les cases sont initialisées à `MACHINE_MEMORY_DEFAULT_VALUE`
  */
void test_memory_create() {
    Memory* mem = memory_create();

    // Test 1 : vérifier la création de la mémoire
    assert(mem != NULL, "Echec de création de la mémoire");

    // Test 2 : vérifier la création du tableau des cases
    assert(mem->data != NULL, "Echec de création du tableau des cases");

    // Test 3 : vérifier que les cases sont initialisées à la bonne valeur
    for (size_t i = 0; i < MACHINE_MEMORY_SIZE; ++i)
        assert(mem->data[i] == MACHINE_MEMORY_DEFAULT_VALUE, "Les cases de la mémoire ne sont pas correctement initialisées");

    memory_delete(&mem);
}

 /**
  * @brief Vérifie les choses suivantes :
  * 
  * - La création du registre
  * - Sa valeur est initialisée à `MACHINE_REGISTER_DEFAULT_VALUE`
  */
void test_register_create() {
    Register* reg = register_create();

    // Test 1 : vérifier la création du registre
    assert(reg != NULL, "Echec de création du registre");

    // Test 2 : vérifier sa valeur par défaut
    assert(reg->val == MACHINE_REGISTER_DEFAULT_VALUE, "La valeur par défaut du registre n'est pas la bonne");

    register_delete(&reg);
}

 /**
  * @brief Vérifie que les valeurs du registre après l'appel de `load_direct` soient correctes.
  */
void test_load_direct() {
    Register* reg = register_create();

    // Message d'erreur
    const char* msg = "Erreur du chargement direct du registre";

    // Valeurs positives
    load_direct(reg, 0);
    assert(reg->val == 0, msg);
    load_direct(reg, 1);
    assert(reg->val == 1, msg);
    load_direct(reg, 3);
    assert(reg->val == 3, msg);
    load_direct(reg, 2);
    assert(reg->val == 2, msg);

    //Valeurs négatives
    load_direct(reg, -1);
    assert(reg->val == -1, msg);
    load_direct(reg, -23);
    assert(reg->val == -23, msg);
    load_direct(reg, -32768);
    assert(reg->val == -32768, msg);
    load_direct(reg, -67);
    assert(reg->val == -67, msg);

    register_delete(&reg);
}

int main() {
    test_memory_create();
    test_register_create();
    test_load_direct();

    printf(COL_GREEN __FILE__ " - Tous les tests sont au vert." COL_RESET);
    return 0;
}