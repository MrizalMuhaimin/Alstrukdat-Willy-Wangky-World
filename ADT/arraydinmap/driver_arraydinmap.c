#include "../boolean/boolean.h"
#include <stdio.h>
#include "arraydinmap.h"

int main() {
    Tab T;
    keyType k;
    valType v;
    MakeEmptyDin(&T,20);
    BacaIsi(&T);
    TulisIsiTab(T);
    printf("\n");
    Kata input;
    // Masukin input
    printf("HALO");
    //STARTKATA();
    input.TabKata[0]='b';
    input.TabKata[1]='a';
    input.TabKata[2]='b';
    input.TabKata[3]='i';
    input.TabKata[4]='\n';

    //printf("HI");
    //CopyKata(CKata,&input); 
    printf("GATAU AH GBS NGETESS masa kata input gkbisa diprint wtf");
    printf("he");
    PrintKata(input);

    if (SearchB(T,input,5)) {
        printf("YAY\n");
    }
    else {
        printf("Nay\n");
    }
/* 
    printf("Baca isi\n");
    BacaIsiMaterial(&T);
    printf("Tulis isi\n");
    TulisIsiTabMaterial(T);
    DelLastEl(&T,&k,&v);
    TulisIsiTabMaterial(T);
*/
    return 0;
}
// gcc arraydinmap.c driver_arraydinmap.c ../mesinkata/mesinkata.c ../mesinkar/mesinkar.c -o driverarraydinmap