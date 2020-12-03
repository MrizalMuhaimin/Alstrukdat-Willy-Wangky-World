// driverbuy.c

#include "prepare.h"
#include <stdio.h>
int main(){
	CommmandBuyArray();
	UndoBuy ();
	PrintInfoStack(stackExecute); 
	
}
// rubah data STARTKATAFILE("Files/material.txt"); menjadi STARTKATAFILE("../../Files/material.txt"); pada BacaIsiMaterial di "../arraydinmap/arraydinmap.c"
//
/*
gcc -o driverbuy driverbuy.c prepare.c  ../listlinier/listlinier.c ../jam/jam.c ../mesinkar/mesinkar.c ../mesinkata/mesinkata.c ../point/point.c ../wahana/wahana.c ../stack/stackt.c  ../player/player.c ../arraydinmap/arraydinmap.c ../graph/graph.c ../peta/peta.c ../matriks/matriks.c -o test
*/