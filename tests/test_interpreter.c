/**
 * @file test_interpreter.c
 * @brief Fichier de tests des fonctions de interpreter.c.
 * 
 * @author Alexandre SBEGHEN
 * @date 2026-06-à5
 */
#include <stdio.h>
#include "test.h"
#include "machine.h"
#include "interpreter.h"

/**
 * @brief Vérifie les choses suivantes :
 * 
 * - La création de la structure du programme
 * 
 * - Ses champs pointent vers des données existantes
 */
void test_program_create() {
    Program* prog = program_create(1000);

    // Test 1 : vérifier la création du prorgamme
    assert(prog != NULL, "Echec de création du programme");

    // Test 2 : vérifier que ses champs sont non nuls
    assert(prog->instructions != NULL, "Echec de création du champ instructions");
    assert(prog->data != NULL, "Echec de création du champ data");

    program_delete(&prog);
}


void test_program_interpret() {
    Memory* mem = memory_create();
    Register* reg = register_create();
    Program* prog = program_create(16);

    /* Programme test 1
        main:
            LOAD #1;
            STORE @0;
            HALT;
    */
    prog->instructions[0][0] = 1;
    prog->instructions[0][1] = 1;
    prog->instructions[1][0] = 3;
    prog->instructions[1][1] = 0;
    prog->instructions[2][0] = 8;
    program_interpret(prog, mem, reg);
    assert(mem->data[0] == 1, "Erreur du programme test 1");

    /* Programme test 2
        main:
            LOAD #-9;		# ]
            STORE @2;		# ] i = -9
        for:
            LOAD @0;		# ]
            INCR;			# ] ++a
            STORE @0;		# ]

            LOAD @2;		# ]
            INCR;			# ] ++i
            STORE @2;		# ]

            JZ for;			# si i <= 0 goto for
            
            HALT;
    
    prog->instructions[0][0] = 1;
    prog->instructions[0][1] = 1;
    prog->instructions[1][0] = 3;
    prog->instructions[1][1] = 3;
*/


    program_delete(&prog);
    register_delete(&reg);
    memory_delete(&mem);
}

int main() {
    test_program_create();
    test_program_interpret();

    printf(COL_GREEN __FILE__ " - Tous les tests pour 'interpreter.c' sont au vert." COL_RESET);
    return 0;
}