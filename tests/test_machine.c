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

/**
 * @brief Vérifie que le registre charge bien les bonnes valeurs qui sont dans la mémoire.
 */
void test_load_from() {
    Memory* mem = memory_create();
    Register* reg = register_create();

    // Message d'erreur
    const char* msg = "Erreur du chargement du registre depuis la mémoire";

    // Initialisation arbitraire des données de la mémoire
    mem->data[0] = 0;
    mem->data[1] = 1;
    mem->data[2] = 3;
    mem->data[5] = -1;
    mem->data[6] = -67;

    load_from(reg, mem, 0);
    assert(reg->val == 0, msg);
    load_from(reg, mem, 1);
    assert(reg->val == 1, msg);
    load_from(reg, mem, 2);
    assert(reg->val == 3, msg);
    load_from(reg, mem, 5);
    assert(reg->val == -1, msg);
    load_from(reg, mem, 6);
    assert(reg->val == -67, msg);

    register_delete(&reg);
    memory_delete(&mem);
}

/**
 * @brief Vérifie que les valeurs sauvegardées dans la mémoire soient les bonnes
 */
void test_store_to() {
    Memory* mem = memory_create();
    Register* reg = register_create();

    // Message d'erreur
    const char* msg = "Erreur du rangement du registre vers la mémoire";

    reg->val = 0;
    store_to(reg, mem, 0);
    reg->val = 1;
    store_to(reg, mem, 1);
    reg->val = 3;
    store_to(reg, mem, 2);
    reg->val = 2;
    store_to(reg, mem, 3);
    reg->val = -1;
    store_to(reg, mem, 4);
    reg->val = -67;
    store_to(reg, mem, 5);

    assert(mem->data[0] == 0, msg);
    assert(mem->data[1] == 1, msg);
    assert(mem->data[2] == 3, msg);
    assert(mem->data[3] == 2, msg);
    assert(mem->data[4] == -1, msg);
    assert(mem->data[5] == -67, msg);

    register_delete(&reg);
    memory_delete(&mem);
}

int main() {
    test_memory_create();
    test_register_create();
    test_load_direct();
    test_load_from();
    test_store_to();

    printf(COL_GREEN __FILE__ " - Tous les tests sont au vert." COL_RESET);
    return 0;
}