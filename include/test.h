/**
 * @file test.h
 * @brief Définit les constantes de print en couleur
 * et de la fonction d'assertion.
 * 
 * @author Alexandre
 * @date 2026-05-24
 */

#define COL_RESET "\033[0m"
#define COL_RED "\033[91m"
#define COL_GREEN "\033[92m"

void assert(const int expression, const char* fail_message);