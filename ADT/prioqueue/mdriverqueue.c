#include "../listlinier/listlinier.h"
#include "../listplayer/listplayer.h"
#include "../mesinkata/mesinkata.h"
#include "../wahana/wahana.h"
#include "../player/player.h"
#include <stdio.h>

int main() {
    /* KAMUS */
    /* Inisialisasi variabel yang digunakan */
    player P;
    PrioQueue Q;
    listPlayer LP;
    ListWahanaD LW;
    TreeWahanaS T;

    /* ALGORITMA */
    MakeTree();
    CreateEmptyQueue(&Q, 5);
    CreateEmptyLP(&LP);
    RandomizeQueue(&Q, LW);

    printf("Enter your name: ");
    STARTKATA();
    printf("\n");
    CreatePlayer(&P);

    STARTKATA();
    do {
        buildWahana(Position(P), &LW);
        STARTKATA();
    } while (IsKataSama('exit'));

    STARTKATA();
    do {
        if (IsKataSama('serve')){
            ADV();
            Serve(&P,CKata,&Q,&LP,LW);
        }
    } while (IsKataSama('exit'));



    return 0;
}