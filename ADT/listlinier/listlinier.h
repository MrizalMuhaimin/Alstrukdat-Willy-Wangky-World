/* File : listlinier.h */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi addressList dengan pointer */
/* infotypeList adalah integer */

#ifndef listlinier_H
#define listlinier_H

#include "../boolean/boolean.h"
#include "../mesinkata/mesinkata.h"
#include "../wahana/wahana.h"

#define NilList NULL

typedef Kata infotypeList;

typedef struct tElmtlist *addressList;
typedef struct tElmtlist {
	infotypeList InfoList;
	addressList next;
} ElmtList;

typedef struct {
	addressList First;
} List;

/* Definisi list : */
/* List kosong : First(L) = NilList */
/* Setiap elemen dengan addressList P dapat diacu InfoList(P), Next(P) */
/* Elemen terakhir list : jika addressnya Last, maka Next(Last)=NilList */

#define InfoList(P) (P)->InfoList
#define Next(P) (P)->next
#define First(L) ((L).First)

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyList (List L);
/* Mengirim true jika list kosong */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyList (List *L);
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */

/****************** Manajemen Memori ******************/
addressList Alokasi (infotypeList X);
/* Mengirimkan addressList hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressList tidak NilList, dan misalnya */
/* menghasilkan P, maka InfoList(P)=X, Next(P)=NilList */
/* Jika alokasi gagal, mengirimkan NilList */
void DealokasiList (addressList *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressList P */

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
addressList Search (List L, Kata X);
/* Mencari apakah ada elemen list dengan InfoList(P)= X */
/* Jika ada, mengirimkan addressList elemen tersebut. */
/* Jika tidak ada, mengirimkan NilList */

boolean SearchBool (List L, Kata X);

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, infotypeList X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVLast (List *L, infotypeList X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, infotypeList *X);
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai InfoList disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void DelVLast (List *L, infotypeList *X);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai InfoList disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, addressList P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-addressList P sebagai elemen pertama */
void InsertAfter (List *L, addressList P, addressList Prec);
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
void InsertLast (List *L, addressList P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, addressList *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void DelP (List *L, infotypeList X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan InfoList(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika ada lebih dari satu elemen list dengan InfoList bernilai X */
/* maka yang dihapus hanya elemen pertama dengan InfoList = X */
/* Jika tidak ada elemen list dengan InfoList(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
void DelLast (List *L, addressList *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
void DelAfter (List *L, addressList *Pdel, addressList Prec);
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
int NbElmt (List L);
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */

/*** Prekondisi untuk Min: List tidak kosong ***/
infotypeList Min (List L);
/* Mengirimkan nilai InfoList(P) yang minimum */

/*** Prekondisi untuk Max: List tidak kosong ***/
infotypeList Max (List L);
/* Mengirimkan nilai InfoList(P) yang maksimum */

boolean IsListSama (List L1, List L2);
/* Memeriksa apakah L1 dan L2 adalah list yang sama */

List RemoveDouble (List L);
/* Mengeluarkan elemen double di dalam L */
/* I.S. List L terdefinisi tidak kosong */
/* F.S. Isi list L unik */

/****************** PROSES TERHADAP LIST ******************/
void Konkat1 (List *L1, List *L2, List *L3);
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */

//boolean IsAllRusak(List L, ListWahanaD LW);
/* Memeriksa apakah semua wahana rusak */

#endif