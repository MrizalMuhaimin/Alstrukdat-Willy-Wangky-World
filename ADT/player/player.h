#ifndef PLAYER_H
#define PLAYER_H

#include "../point/point.h"
#include "../jam/jam.h"
#include "../mesinkar/mesinkar.h"
#include "../mesinkata/mesinkata.h"
#include "../arraydinmap/arraydinmap.h"

#define MaxLength 20

typedef struct {
    Kata Name;
    POINT Position;
    int MapNum;
    JAM CJam;
    int Money;
    int Day;
    Tab TabBahan; //hem di struct atau bikin empty aja pas di awal ?
} player;


extern player Player;

#define NamaPlayer(P) (P).Name
#define Position(P) (P).Position
#define X(P) Absis((P).Position)
#define Y(P) Ordinat((P).Position)
#define MapNum(P) (P).MapNum
#define Money(P) (P).Money
#define CJam(P) (P).CJam
#define Day(P) (P).Day
#define Tab(P) (P).TabBahan 
// hem di struct atau bikin empty aja ya,,

JAM JamBuka;
JAM JamTutup;

void CreatePlayer(player *P);

void TulisPlayer();

#endif