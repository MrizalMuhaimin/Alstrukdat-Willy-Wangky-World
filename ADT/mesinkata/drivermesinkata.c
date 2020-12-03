#include "mesinkata.h"
#include <stdio.h>

boolean EndKata;
Kata CKata;
char CC;
boolean EOP;

int main(){
    STARTFILE("../../Files/Wahana/wahana.txt");
    while(!EOP){
        SalinKataFile();
        PrintKata(CKata); printf(" ");
        if(CC == EOL){ //urus EOL tergantung kebutuhan masing2
            ADV();
            printf("\n");
        }
    }
    return 0;
}

// gcc mesinkata.c drivermesinkata.c ../mesinkar/mesinkar.c -o test