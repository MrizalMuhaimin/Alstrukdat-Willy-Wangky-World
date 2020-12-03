/* File mdriverlistlinier.c */

#include "listlinier.h"
#include "../mesinkata/mesinkata.h"
#include <stdio.h>

int main() {
    /* KAMUS */
    List L;

    /* ALGORITMA */
    CreateEmptyList(&L);

    STARTKATA();
    while (IsKataSama("exit")) {
        InsVLast(&L, CKata);
        STARTKATA();        
    }
    PrintInfo(L);

    return 0;
}