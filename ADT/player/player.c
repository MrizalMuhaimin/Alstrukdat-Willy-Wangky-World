#include "player.h"
#include <stdio.h>
#include <string.h>

boolean EndKata;
Kata CKata;
JAM JamBuka;
JAM JamTutup;
player Player;

void CreatePlayer(player *P){
    CopyKata(CKata, &(NamaPlayer(*P)));
    X(*P) = 1;
    Y(*P) = 1;
    MapNum(*P) = 1;
    Money(*P) = 5000; // Biar leluasa ngetes2
    CJam(*P) = MakeJAM(21,0);
    Day(*P) = 1;
    MakeEmptyDin(&Tab(*P),20);
    // Inisialisasi Resources
    //Tab TabResources;
    //MakeEmptyDin(&TabResources,20);
}

void TulisPlayer(){
    printf("           ");printf("Player Name: ");
    PrintKata(NamaPlayer(Player));
    printf("\n");
    printf("           ");printf("Money: %d\n", Money(Player));
}

