//
//  NIM         : 13519192
//  NAMA        : Gayuh Tri Rahutami
//  Tanggal     : 2 September 2020
//  Topik       : ADT Point
//  Deskripsi   : Definisi ABSTRACT DATA TYPE POINT
//
#include <stdio.h>
#include <math.h>
#include "point.h"

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT (int X, int Y){
    POINT P;
    Absis(P) = X;
    Ordinat(P) = Y;
    
    return P;
}

boolean IsEqPOINT (POINT X, POINT P){
    return (Absis(X)==Absis(P) && Ordinat(X)==Ordinat(P));
}
/* Membentuk sebuah POINT dari komponen-komponennya */

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */
void BacaPOINT (POINT * P){
    int x,y;

    scanf("%d %d", &x, &y);
    
    Absis(*P) = x;
    Ordinat(*P) = y;
}
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk
   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2
   akan membentuk POINT <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */

void TulisPOINT (POINT P){
    printf("(%d,%d)", Absis(P), Ordinat(P));
}
/* Nilai P ditulis ke layar dengan format "(X,Y)"
   tanpa spasi, enter, atau karakter lain di depan, belakang,
   atau di antaranya
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */

/* *** Kelompok operasi relasional terhadap POINT *** */

/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin (POINT P){
    return (Absis(P) == 0 && Ordinat(P) == 0);
}
/* Menghasilkan true jika P adalah titik origin */

boolean IsOnSbX (POINT P){
    return (Ordinat(P) == 0);
}
/* Menghasilkan true jika P terletak Pada sumbu X */

boolean IsOnSbY (POINT P){
    return (Absis(P) == 0);
}
/* Menghasilkan true jika P terletak pada sumbu Y */

int Kuadran (POINT P){
    if (Absis(P)==0 || Ordinat(P)==0) return -1;
    else if(Absis(P) > 0 && Ordinat(P) > 0) return 1;
    else if (Absis(P) < 0 && Ordinat (P) > 0 ) return 2;
    else if (Absis(P) < 0) return 3;
    else return 4;
}
/* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
/* Prekondisi : P bukan titik origin, */
/*              dan P tidak terletak di salah satu sumbu */

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
POINT NextX (POINT P){
    POINT newPoint; 
    Absis(newPoint) = Absis(P) + 1;
    Ordinat(newPoint) = Ordinat(P);

    return newPoint;
}
/* Mengirim salinan P dengan absis ditambah satu */

POINT NextY (POINT P){
    POINT newPoint; 
    Absis(newPoint) = Absis(P);
    Ordinat(newPoint) = Ordinat(P) + 1;

    return newPoint;
}
/* Mengirim salinan P dengan ordinat ditambah satu */

POINT PlusDelta (POINT P, int deltaX, int deltaY){
    POINT newPoint; 
    Absis(newPoint) = Absis(P) + deltaX;
    Ordinat(newPoint) = Ordinat(P) + deltaY;

    return newPoint;
}
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */

POINT MirrorOf (POINT P, boolean SbX){
    POINT newPoint;
    if (SbX){
        Absis(newPoint) = Absis(P);
        Ordinat(newPoint) = (-1) * Ordinat(P);
    } else {
        Absis(newPoint) = (-1) * Absis(P);
        Ordinat(newPoint) = Ordinat(P);
    }

    return newPoint;
}
/* Menghasilkan salinan P yang dicerminkan terhadap salah satu sumbu */
/* Jika SbX bernilai true, maka dicerminkan terhadap sumbu X */
/* Jika SbX bernilai false, maka dicerminkan terhadap sumbu Y */

float Jarak0 (POINT P){
    return sqrt(pow(Absis(P),2) + pow(Ordinat(P),2));
}
/* Menghitung jarak P ke (0,0) */

float Panjang (POINT P1, POINT P2){
    int deltaX = Absis(P1) - Absis(P2);
    int deltaY = Ordinat(P1) - Ordinat(P2);
    float deltaX2 = pow(deltaX,2)*1.0;
    float deltaY2 = pow(deltaY,2)*1.0;
    
    return sqrt( deltaX2 + deltaY2 );
}
/* Menghitung panjang garis yang dibentuk P1 dan P2 */
/* Perhatikanlah bahwa di sini spec fungsi kurang baik sebab menyangkut ADT Garis. */
/* Tuliskan spec fungsi yang lebih tepat. */

void Geser (POINT *P, int deltaX, int deltaY){
    Absis(*P) += deltaX;
    Ordinat(*P) += deltaY;
}
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */

void GeserKeSbX (POINT *P){
    Ordinat(*P) = 0;
}
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */

void GeserKeSbY (POINT *P){
    Absis(*P) = 0;
}
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */

void Mirror (POINT *P, boolean SbX){
    if (SbX){
        Ordinat(*P) *= (-1);
    } else {
        Absis(*P) *= (-1);
    }
}
/* I.S. P terdefinisi */
/* F.S. P dicerminkan tergantung nilai SbX atau SbY */
/* Jika SbX true maka dicerminkan terhadap sumbu X */
/* Jika SbX false maka dicerminkan terhadap sumbu Y */

void Putar (POINT *P, int Sudut){
    Sudut *= (-1);
    Sudut = (Sudut/180)* 3.1415926535;

    int tempX = cos(Sudut) * Absis(*P) + (-1) * sin(Sudut) * Ordinat(*P);
    int tempY = sin(Sudut) * Absis(*P) + cos(Sudut) * Ordinat(*P);

    Absis(*P) = tempX;
    Ordinat(*P) = tempY;
}
/* I.S. P terdefinisi */
/* F.S. P digeser sebesar Sudut derajat dengan sumbu titik (0,0) searah jarum jam*/

/* FUNGSI TAMBAHAn */

boolean IsSekitar (POINT P1, POINT P2) {
    return( (Absis(P1) == Absis(NextX(P2))) || (Ordinat(P1) == Ordinat(NextY(P2))) || (Absis(P2) == Absis(NextX(P1))) || (Ordinat(P2) == Ordinat(NextX(P1))));
}