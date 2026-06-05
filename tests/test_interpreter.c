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

/***
 * @brief Exécute quelques programmes simples et vérifie les valeurs dans la mémoire.
 * 
 * - Le premier programme enregistre la valeur 0 dans A (stocké dans la case 0).
 * 
 * - Le deuxième programme ajoute 10 à A.
 * 
 * - Le troisième programme calcule la valeur absolue de A.
 * 
 * Pour chaque programme, quelques sous-cas sont testés également
 * pour être sûr qu'il ne s'agit pas d'une réussite par chance.
 */
void test_program_interpret() {
    Memory* mem = memory_create();
    Register* reg = register_create();
    Program* prog = program_create(16);

    /* Programme test 1 (a = 0)
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

    /* Programme test 2 (a += 10)
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
    */
    prog->instructions[0][0] = 1;
    prog->instructions[0][1] = -9;
    prog->instructions[1][0] = 3;
    prog->instructions[1][1] = 2;
    prog->instructions[2][0] = 2;
    prog->instructions[2][1] = 0;
    prog->instructions[3][0] = 4;
    prog->instructions[4][0] = 3;
    prog->instructions[4][1] = 0;
    prog->instructions[5][0] = 2;
    prog->instructions[5][1] = 2;
    prog->instructions[6][0] = 4;
    prog->instructions[7][0] = 3;
    prog->instructions[7][1] = 2;
    prog->instructions[8][0] = 7;
    prog->instructions[8][1] = 2;
    prog->instructions[9][0] = 8;
    mem->data[0] = 7;
    program_interpret(prog, mem, reg);
    assert(mem->data[0] == 17, "Erreur du programme test 2");
    mem->data[0] = 0;
    program_interpret(prog, mem, reg);
    assert(mem->data[0] == 10, "Erreur du programme test 2");
    mem->data[0] = -5;
    program_interpret(prog, mem, reg);
    assert(mem->data[0] == 5, "Erreur du programme test 2");
    
    /* Programme test 3 (valeur absolue)
        main:
            LOAD @0;	# ]
            INCR;		# ] i = a+1
            STORE @1;	# ]
            
            LOAD @0;	# ]
            INCR;		# ] r = a+1

            JZ absolute;	# si (a+1 <= 0) <=> (a <= -1) goto absolute
            JUMP end;	# sinon pas besoin et fin

        absolute:
            LOAD @0;	# ]
            INCR;		# ]
            INCR;		# ] a += 2
            STORE @0;	# ]

            LOAD @1;	# ]
            INCR;		# ] ++i
            STORE @1;	# ]

            JZ absolute;	# si i <= 0 goto recommencer

        end:
            HALT;
    */
    prog->instructions[0][0] = 2;
    prog->instructions[0][1] = 0;
    prog->instructions[1][0] = 4;
    prog->instructions[2][0] = 3;
    prog->instructions[2][1] = 1;
    prog->instructions[3][0] = 2;
    prog->instructions[3][1] = 0;
    prog->instructions[4][0] = 4;
    prog->instructions[5][0] = 7;
    prog->instructions[5][1] = 7; //goto absolute
    prog->instructions[6][0] = 6;
    prog->instructions[6][1] = 15; //goto end
    prog->instructions[7][0] = 2;
    prog->instructions[7][1] = 0;
    prog->instructions[8][0] = 4;
    prog->instructions[9][0] = 4;
    prog->instructions[10][0] = 3;
    prog->instructions[10][1] = 0;
    prog->instructions[11][0] = 2;
    prog->instructions[11][1] = 1;
    prog->instructions[12][0] = 4;
    prog->instructions[13][0] = 3;
    prog->instructions[13][1] = 1;
    prog->instructions[14][0] = 7;
    prog->instructions[14][1] = 7;
    prog->instructions[15][0] = 8;
    mem->data[0] = 0;
    program_interpret(prog, mem, reg);
    assert(mem->data[0] == 0, "Erreur du programme test 3");
    mem->data[0] = 5;
    program_interpret(prog, mem, reg);
    assert(mem->data[0] == 5, "Erreur du programme test 3");
    mem->data[0] = -1;
    program_interpret(prog, mem, reg);
    assert(mem->data[0] == 1, "Erreur du programme test 3");
    mem->data[0] = -67;
    program_interpret(prog, mem, reg);
    assert(mem->data[0] == 67, "Erreur du programme test 3");

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