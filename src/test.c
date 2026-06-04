/**
 * @file test.c
 * @brief Implémentation de la fonction d'assertion.
 * 
 * @author Alexandre SBEGHEN
 * @date 2026-05-24
 */

#include <stdio.h>
#include <stdlib.h>
#include "test.h"

void assert(int expression, char* fail_message) {
    if (!expression) {
        fprintf(stderr, COL_RED "ERREUR : " __FILE__ " - %s" COL_RESET, fail_message);
        exit(1);
    }
}