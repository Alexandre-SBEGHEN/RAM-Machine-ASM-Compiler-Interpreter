# Assembly compiler & interpreter for RAM Machine

## Contexte

Durant mon premier TP d'assembleur, notre professeur nous a introduit à un langage assembleur rudimentaire avant de nous faire réaliser des exercices pratiques. Le problème : il nous était impossible d'exécuter notre code pour vérifier son exactitude. J'ai donc décidé de créer un programme capable de lire et d'exécuter du code écrit dans cet assembleur.

J'en ai également profité pour l'implémenter entièrement en C, afin de consolider mes compétences dans ce langage et d'apprendre la manipulation de fichiers.

## Machine Ram

C'est une machine équivalente à une machine de Turing, et issue du modèle de Von Neumann. Elle est munie d’une mémoire infinie, d’un registre unique, et d’une unité arithmétique et logique capable d’incrémenter ou décrémenter un entier, ou de le comparer à zéro.

<p align="center">
    <img src="assets/machine_ram_schema.png" alt="Schéma de la machine RAM" width="350">
</p>

Cette machine est équipée du jeu d'instructions suivant :

| Instruction | Description |
|-|-|
| `LOAD #<valeur numérique>` | Chargement direct du registre |
| `LOAD @<adresse mémoire>` | Chargement du registre depuis la mémoire |
| `STORE @<adresse mémoire>` | Rangement du registre vers la mémoire |
| `INCR` | Incrémentation du registre |
| `DECR` | Décrémentation du registre |
| `JUMP <étiquette>` | Saut inconditionnel à l'étiquette |
| `JZ <étiquette>` | Saut à l'étiquette si (registre ≤ 0) |
| `HALT` | Arrêt du programme |

## Programme compilé

Une fois compilé, le programme est représenté sous la forme d'un tableau de N lignes et 2 colonnes. La première colonne contient l'instruction à exécuter, et la seconde son opérande éventuel. Chaque valeur un entier signé sur 32 bits. Si l'instruction ne prend pas d'opérande, la seconde colonne est ignorée.

Le tableau suivant récapitule les instructions du jeu d'instructions de la machine RAM, avec pour chacune son code hexadécimal, la présence ou non d'un opérande, et son équivalent assembleur correspondant.

| Instruction (hex) | Opérande ? | Equivalent en assembleur |
|-|-|-|
| `0x00000000` | non | Ne rien faire |
| `0x00000001` | oui | `LOAD #?` |
| `0x00000002` | oui | `LOAD @?` |
| `0x00000003` | oui | `STORE @?` |
| `0x00000004` | non | `INCR` |
| `0x00000005` | non | `DECR` |
| `0x00000006` | oui | `JUMP ?` |
| `0x00000007` | oui | `JZ ?` |
| `0x00000008` | non | `HALT` |

## Progression

- [x] Machine RAM (mémoire + registre)
- [x] Instructions de base (load, store, increment, decrement)
- [ ] Compilateur
- [ ] Interpréteur
- [ ] Gestion des étiquettes (compilation)
- [ ] Prise en charge des sauts (interpréteur)
- [ ] Interface utilisateur
