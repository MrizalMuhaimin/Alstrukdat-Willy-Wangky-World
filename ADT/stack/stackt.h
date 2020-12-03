/* File : stackt.h */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */
#ifndef stackt_H
#define stackt_H

#include "../boolean/boolean.h"
#include "../jam/jam.h"
#include "../wahana/wahana.h"
#include "../point/point.h"
#include "../mesinkata/mesinkata.h"
#include "../player/player.h"
//#include "../maplist/maplist.h"
#include "../peta/peta.h"
#include "../graph/graph.h"

#define Nil -1
#define MaxElS 100
/* Nil adalah stack dengan elemen kosong . */

typedef int addressStack;   /* indeks tabel */

/* Belom fix */
player Pemain;
typedef struct {
  Kata commandStack;
  int durasi; // Waktu yang dibutuhkan untuk melakukan satu aksi (+)
  POINT PointWahana; // Point tempat aksi tsb dilakukan
  int MapNumAksi; // No Peta tempat aksi tsb dilakukan
  Kata NamaBahan; // Nama bahan yang digunakan
  int JumlahBahan; // Jumlah bahan yang dibutuhkan (+)
  int uang; // Uang yang dibutuhkan untuk melakukan satu aksi
  addressWahanaS addrPrevWahana; // address wahana sebelum upgrade
} aksi;

/* Contoh deklarasi variabel bertype stack dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
typedef struct { 
  aksi T[MaxElS]; /* tabel penyimpan elemen */
  addressStack TOP;  /* alamat TOP: elemen puncak */
} Stack;

extern Stack stackExecute;
/* Definisi stack S kosong : S.TOP = Nil */
/* Elemen yang dipakai menyimpan nilai Stack T[0]..T[MaxElS-1] */
/* Jika S adalah Stack maka akses elemen : */
   /* S.T[(S.TOP)] untuk mengakses elemen TOP */
   /* S.TOP adalah alamat elemen TOP */

/* Definisi akses dengan Selektor : Set dan Get */
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmpty (Stack *S);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxElS */
/* jadi indeksnya antara 0.. MaxElS */
/* Ciri stack kosong : TOP bernilai Nil */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStack (Stack S);
/* Mengirim true jika Stack kosong: lihat definisi di atas */
boolean IsFullStack (Stack S);
/* Mengirim true jika tabel penampung nilai elemen stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, aksi X);
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, aksi* X);
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

void CopyStack (Stack Sin, Stack *Sout);
/* Membuat salinan Sin */
/* I.S. Sin terdefinisi, Sout sembarang */
/* F.S. Sout berisi salinan Sin yang identik */

void InverseStack (Stack S);
/* Prosedur untuk membalik urutan elemen stack S */

void PrintStack (Stack S); /* Prosedur buat membantu aja ini */

int SumDurasiStack (Stack S);
/* Me-return total waktu yang akan dibutuhkan untuk semua aksi */

int SumUangStack (Stack S);
/* Me-return total uang yang akan dibutuhkan untuk semua aksi */

int NbElmtStack (Stack S);
/* Me-return total aksi yang akan dilakukan (atau NbElmt dari stack) */

void UpgradeStack(addressWahanaS prevWahana, addressWahanaS nextWahana);
/* Prosedur  elemen stack jika wahana berhasil di upgrade */

void PrintInfoStack (Stack S);
/* Prosedur untuk print total aksi yang dilakukan beserta durasi total aksi */

boolean UangCukup (player *P, int harga);
/* Fungsi yang mengecek apakah uang pemain cukup */

boolean BahanCukup (player *P, Kata NamaBahan, int JumlahBahan);
/* Fungsi yang mengecek apakah bahan yang dimiliki pemain cukup */

boolean SemuaCukup (player *P, Kata NamaBahan, int JumlahBahan, int BiayaUpgrade);
/* Fungsi yang mengecek apakah uang dan bahan yang dimiliki pemain cukup */

void PrintUpgraded(addressWahanaS prevWahana, addressWahanaS nextWahana);
/* Prosedur untuk print hasil aksi upgrade pada wahana */

void PushE(Stack * S, aksi X);

#endif
