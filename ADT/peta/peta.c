#include <stdio.h>
#include <string.h>
#include "peta.h"
#include "../graph/graph.h"
#include "../mesinkata/mesinkata.h"

boolean EndKata;
Kata CKata;
char CC;
boolean EOP;
Graph GraphPeta;

void MakePETA (char* filename, MATRIKS * P)
/* Mengisi matriks P dengan peta yang ada di filename
   I.S Matriks P bebas
   F.S Matriks P terisi dengan Peta yang ada di filename */
{
    FILE* cFile;
    int i, j;

    STARTFILE(filename);

    i = 0;
    j = 0;

    while(!EOP){
        ElmtMatriks(*P, i, j) = CC;
        ADV();
        if(CC == EOL){
            j = 0;
            i++;
            ADV();
        } else {
            j++;
        }
    }

    ADV();

    NBrsEff(*P) = ++i;
    NKolEff(*P) = j;
}


void TulisPETA (player Pl, Graph G)
/* I.S. Pl dan G terdefinisi */
/* F.S. Peta yang saat ini ditempati player diprint ke layar*/
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom. Gerbang dituliskan dengan <, v, >, ^*/

{
    // KAMUS
    int i, j;
    addressGraph CPeta = FirstGraph(G);

    // ALGORITMA
    while(ID(CPeta) != MapNum(Pl)) CPeta = NextGraph(CPeta);

    for (i = 0; i < NBrsEff(Peta(CPeta)); i++){
        for (j = 0; j <= NKolEff(Peta(CPeta)); j++){
            if (j == X(Pl) && i == Y(Pl)) printf("P"); //Posisi player
            else if(ElmtMatriks(Peta(CPeta), i, j) >= '1' && ElmtMatriks(Peta(CPeta), i, j) <= '4'){
                if(i == 0) printf("^");
                else if(j == 0) printf("<");
                else if(i == NBrsEff(Peta(CPeta))-1) printf("V");
                else if(j == NKolEff(Peta(CPeta))-1) printf(">");
            }
            else printf("%c", ElmtMatriks(Peta(CPeta), i, j)); //Print yang ada di peta
            if(j != NKolEff(Peta(CPeta))-1) printf(" ");
        }
        if(i != NBrsEff(Peta(CPeta))) printf("\n");
    }
}

int CharToInt (char X){
    if (X == '1') return 1;
    else if (X == '2') return 2;
    else if (X == '3') return 3;
    else if (X == '4') return 4;
}

char IntToChar (int X){
    if (X == 1) return '1';
    else if (X == 2) return '2';
    else if (X == 3) return '3';
    else if (X == 4) return '4';
}

void MovePeta(player *P, Graph G, int NewMapID){
/* Memindahkan player dari satu arena ke arena yang lain
   I.S. Player berada di arena yang sesuai dengan MapNum(P)
   F.S. Player berada di arena dengan ID NewMapID
*/
    addressGraph NewPeta = FirstGraph(G);

    while(ID(NewPeta) != NewMapID) NewPeta = NextGraph(NewPeta);
    SearchMatriks(Peta(NewPeta), &Y(*P), &X(*P), IntToChar(MapNum(*P)));
    if(X(*P) == 0) X(*P)++;
    if (Y(*P) == 0) Y(*P)++;
    if(X(*P) == NKolEff(Peta(NewPeta))-1) X(*P)--;
    if(Y(*P) == NBrsEff(Peta(NewPeta))-1) Y(*P)--;

    MapNum(*P) = NewMapID;
}

void w(player *P, Graph G){
/* Player bergerak ke "atas"
   I.S Player berada di point X,Y
   F.S Jika X,Y-1 kosong, player berada di point X,Y-1. Jika tidak kosong, player tetep berada di X,Y
*/
    int X = X(*P);
    int Y = Y(*P);
    addressGraph CPeta = FirstGraph(G);

    // ALGORITMA
    while(ID(CPeta) != MapNum(*P)) CPeta = NextGraph(CPeta);

    if(ElmtMatriks(Peta(CPeta), Y-1, X) == '-' || ElmtMatriks(Peta(CPeta), Y-1, X) == 'O' ) Y(*P)--;
    else if(ElmtMatriks(Peta(CPeta), Y-1, X) == '1') MovePeta(P, G, 1);
    else if(ElmtMatriks(Peta(CPeta), Y-1, X) == '2') MovePeta(P, G, 2);
    else if(ElmtMatriks(Peta(CPeta), Y-1, X) == '3') MovePeta(P, G, 3);
    else if(ElmtMatriks(Peta(CPeta), Y-1, X) == '4') MovePeta(P, G, 4);
}

void a(player *P, Graph G){
/* Player bergerak ke "kiri"
   I.S Player berada di point X,Y
   F.S Jika X-1,Y kosong, player berada di point X-1,Y. Jika tidak kosong, player tetep berada di X,Y
*/

    int X = X(*P);
    int Y = Y(*P);

    addressGraph CPeta = FirstGraph(G);

    // ALGORITMA
    while(ID(CPeta) != MapNum(*P)) CPeta = NextGraph(CPeta);

    if(ElmtMatriks(Peta(CPeta), Y, X-1) == '-' || ElmtMatriks(Peta(CPeta), Y, X-1) == 'O') X(*P)--;
    else if(ElmtMatriks(Peta(CPeta), Y, X-1) == '1') MovePeta(P, G, 1);
    else if(ElmtMatriks(Peta(CPeta), Y, X-1) == '2') MovePeta(P, G, 2);
    else if(ElmtMatriks(Peta(CPeta), Y, X-1) == '3') MovePeta(P, G, 3);
    else if(ElmtMatriks(Peta(CPeta), Y, X-1) == '4') MovePeta(P, G, 4);
}

void s(player *P, Graph G){
/* Player bergerak ke "bawah"
   I.S Player berada di point X,Y
   F.S Jika X,Y+1 kosong, player berada di point X,Y+1. Jika tidak kosong, player tetep berada di X,Y
*/

    int X = X(*P);
    int Y = Y(*P);

    addressGraph CPeta = FirstGraph(G);

    // ALGORITMA
    while(ID(CPeta) != MapNum(*P)) CPeta = NextGraph(CPeta);

    if(ElmtMatriks(Peta(CPeta), Y+1, X) == '-' || ElmtMatriks(Peta(CPeta), Y+1, X) == 'O') Y(*P)++;
    else if(ElmtMatriks(Peta(CPeta), Y+1, X) == '1') MovePeta(P, G, 1);
    else if(ElmtMatriks(Peta(CPeta), Y+1, X) == '2') MovePeta(P, G, 2);
    else if(ElmtMatriks(Peta(CPeta), Y+1, X) == '3') MovePeta(P, G, 3);
    else if(ElmtMatriks(Peta(CPeta), Y+1, X) == '4') MovePeta(P, G, 4);
}

void d(player *P, Graph G){
/* Player bergerak ke "kanan"
   I.S Player berada di point X,Y
   F.S Jika X+1,Y kosong, player berada di point X+1,Y. Jika tidak kosong, player tetep berada di X,Y
*/
    int X = X(*P);
    int Y = Y(*P);

    addressGraph CPeta = FirstGraph(G);

    // ALGORITMA
    while(ID(CPeta) != MapNum(*P)) CPeta = NextGraph(CPeta);

    if(ElmtMatriks(Peta(CPeta), Y, X+1) == '-' || ElmtMatriks(Peta(CPeta), Y, X+1) == 'O') X(*P)++;
    else if(ElmtMatriks(Peta(CPeta), Y, X+1) == '1') MovePeta(P, G, 1);
    else if(ElmtMatriks(Peta(CPeta), Y, X+1) == '2') MovePeta(P, G, 2);
    else if(ElmtMatriks(Peta(CPeta), Y, X+1) == '3') MovePeta(P, G, 3);
    else if(ElmtMatriks(Peta(CPeta), Y, X+1) == '4') MovePeta(P, G, 4);
}

void loadPeta(){
/* Me-load seluruh peta arena yang ada
   I.S Matriks Peta1, Peta2, Peta3, Peta4 bebas
   F.S Matriks Peta1, Peta2, Peta3, Peta4 berisi peta yang ada di file-file peta
*/
    FILE *cFile;
    char* filename;
    char str[MAXCHAR];
    int i;

    // start of peta 1
    
    MakePETA("Files/Peta/Peta_1.txt", &Peta1);

    // end of peta 1

    // start of peta 2

    MakePETA("Files/Peta/Peta_2.txt", &Peta2);

    // end of peta 2

    // start of peta 3

    MakePETA("Files/Peta/Peta_3.txt", &Peta3);

    // end of peta 3

    // start of peta 4

    MakePETA("Files/Peta/Peta_4.txt", &Peta4);

    // end of peta 4
}

void AddWToPeta(){
/* Menambahkan Wahana ke peta
   I.S Player berada di point X,Y
   F.S point X,Y pada peta menjadi W. Player pindah ke kanan/kiri/atas/bawah point sebelumnya yang kosong.
*/
    addressGraph CPeta = FirstGraph(GraphPeta);
    while(ID(CPeta) != MapNum(Player)) CPeta = NextGraph(CPeta);

    ElmtMatriks(Peta(CPeta), Y(Player), X(Player)) = 'W';

    if(ElmtMatriks(Peta(CPeta), Y(Player)+1, X(Player)) == '-') Y(Player)++;
    else if(ElmtMatriks(Peta(CPeta), Y(Player)-1, X(Player)) == '-') Y(Player)--;
    else if(ElmtMatriks(Peta(CPeta), Y(Player), X(Player) + 1) == '-') X(Player)++;
    else if(ElmtMatriks(Peta(CPeta), Y(Player), X(Player) - 1) == '-') X(Player)--;
}