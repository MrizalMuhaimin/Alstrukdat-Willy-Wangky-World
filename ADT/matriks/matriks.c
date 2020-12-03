// /* ********** Definisi TYPE MATRIKS dengan indeks dan elemen integer ********** */

// #ifndef MATRIKS_H
// #define MATRIKS_H

#include <stdio.h>
#include "matriks.h"
#include <string.h>

MATRIKS Peta1;
MATRIKS Peta2;
MATRIKS Peta3;
MATRIKS Peta4;
/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M)
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
{
    // ALGORITMA
    NBrsEff(*M) = NB;
    NKolEff(*M) = NK;
}
/* *** Selektor *** */
// #define NBrsEff(M) (M).NBrsEff
// #define NKolEff(M) (M).NKolEff
// #define ElmtMatriks(M,i,j) (M).Mem[(i)][(j)]

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j)
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
{
    // ALGORITMA
    return (i>=BrsMin && i<=BrsMax && j>=KolMin && j<=KolMax);
}

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terkecil M */
{
    // ALGORITMA
    return BrsMin;
}
indeks GetFirstIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terkecil M */
{
    // ALGORITMA
    return KolMin;
}
indeks GetLastIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terbesar M */
{
    // ALGORITMA
    return BrsMin + NBrsEff(M) - 1;
}
indeks GetLastIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terbesar M */
{
    // ALGORITMA
    return KolMin + NKolEff(M) - 1;
}
boolean IsIdxEff (MATRIKS M, indeks i, indeks j)
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
{
    // ALGORITMA
    return(i >= GetFirstIdxBrs(M) && i <= GetLastIdxBrs(M) && j >= GetFirstIdxKol(M) && j <= GetLastIdxKol(M));
}
ElType GetElmtDiagonal (MATRIKS M, indeks i)
/* Mengirimkan elemen M(i,i) */
{
    // ALGORITMA
    return ElmtMatriks(M, i, i);
}

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl)
/* Melakukan assignment MHsl  MIn */
{
    // KAMUS
    int i,j;

    // ALGORITMA
    NBrsEff(*MHsl) = NBrsEff(MIn);
    NKolEff(*MHsl) = NKolEff(MIn);

    for (i=GetFirstIdxBrs(MIn); i<=GetLastIdxBrs(MIn); i++){
        for (j=GetFirstIdxKol(MIn); j<=GetLastIdxKol(MIn); j++){
            ElmtMatriks(*MHsl, i, j) = ElmtMatriks(MIn, i, j);
        }
    }
}
/* ********** KELOMPOK BACA/TULIS ********** */ 
void BacaMATRIKS (MATRIKS * M, int NB, int NK)
/* I.S. IsIdxValid(NB,NK) */ 
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
{
    // KAMUS
    int i, j;

    // ALGORITMA
    MakeMATRIKS(NB, NK, M);
    
    for (i = GetFirstIdxBrs(*M); i <= GetLastIdxBrs(*M); i++){
        for (j = GetFirstIdxKol(*M); j <=GetLastIdxKol(*M); j++){
            scanf("%d", &ElmtMatriks(*M, i, j));
        }
    }
}
void TulisMATRIKS (MATRIKS M)
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
{
    // KAMUS
    int i, j;
    
    // ALGORITMA
    for (i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++){
        printf("           ");
        for (j = GetFirstIdxKol(M); j <=GetLastIdxKol(M); j++){
            if (j == X(Player) && i == Y(Player)){
                printf("\033[1;31m");
                printf("P");
                printf("\033[0m");
                printf("\033[0;34m");
            } //Posisi player
            else if(ElmtMatriks(M, i, j) >= '1' && ElmtMatriks(M, i, j) <= '4'){
                if(i == 0) printf("^");
                else if(j == 0) printf("<");
                else if(i == NBrsEff(M)-1) printf("V");
                else if(j == NKolEff(M)-1) printf(">");
            }
            else printf("%c", ElmtMatriks(M, i, j)); //Print yang ada di peta
            if(j != NKolEff(M)-1) printf(" ");
        }
        if(i != GetLastIdxBrs(M)) printf("\n");
    }

    printf("\n");
}

/* ********** Operasi lain ********** */
int NBElmt (MATRIKS M)
/* Mengirimkan banyaknya elemen M */
{
    // ALGORITMA
    return NKolEff(M) * NBrsEff(M);
}
/* Operasi berbasis baris dan per kolom */
void SearchMatriks(MATRIKS M, int * i, int * j, ElType X){
/*
Mencari Elemen matriks yang memiliki nilai X
Jika tidak ada i dan j akan bernilai -1
*/
    *i = 0;

    while(*i <= GetLastIdxBrs(M) && ElmtMatriks(M, *i, *j) != X){
        *j = 0;
        while(*j <= GetLastIdxKol(M) && ElmtMatriks(M, *i, *j) != X){
            (*j)++;
        }
        if(ElmtMatriks(M, *i, *j) != X) (*i)++;
    }

    if(*i > GetLastIdxBrs(M) || *j > GetLastIdxKol(M)){
        *i = -1;
        *j = -1;
    }

}